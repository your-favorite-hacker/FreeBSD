/* 	
	execWatch to the arms!
 	hooks syscall execve and logs every access to /var/log/messages
   	written somewhen between 2006-2009
	ported to freebsd 10.1 should work also on older releases
	by dash
*/
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/syscall.h>
#include <sys/syscallsubr.h>
#include <sys/sysproto.h>
#include <sys/syslog.h>
#include <sys/imgact.h>
#include <sys/linker.h>
#include <sys/libkern.h>

#define eVersion "0.1"

static int execve_hook(struct thread *td, void *syscall_args)
{
	
	struct execve_args *uap;	
	uap = (struct execve_args *)syscall_args;
	
        int error;
        struct image_args args;

        error = exec_copyin_args(&args, uap->fname, UIO_USERSPACE,
            uap->argv, uap->envv);

	log(LOG_DEBUG,"execWatch: fname: %s (%s) %d uid: %d\n",uap->fname,*uap->argv,args.argc,td->td_ucred->cr_uid);
        if (error == 0)
                error = kern_execve(td, &args, NULL);
        return (error);

		
}
struct eWatch_function_args {
	int op;
	};

static int eWatch_function(struct thread *td, void *syscall_args)
{
	return(0);
}
static struct sysent eWatch_function_sysent = {
        0,
        eWatch_function
};

static int offset = NO_SYSCALL;

static int load(struct module *module, int cmd, void *args)
{
        int error;
	error=0;


        switch(cmd) {
        case MOD_LOAD:
		uprintf("[+] Loaded execWatch %s\n",eVersion);
                uprintf("[+] Call at %d\n",offset);
                sysent[SYS_execve].sy_call = (sy_call_t *)execve_hook;
		
                break;

        case MOD_UNLOAD:

                sysent[SYS_execve].sy_call = (sy_call_t *)sys_execve;
		uprintf("[+] Unloaded execWatch %s\n",eVersion);
                uprintf("[+] Unload at %d\n",offset);
                break;
        default:
                error = EOPNOTSUPP;
                break;
        }

        return(error);
}

SYSCALL_MODULE(eWatch_function, &offset, &eWatch_function_sysent,load,NULL);
