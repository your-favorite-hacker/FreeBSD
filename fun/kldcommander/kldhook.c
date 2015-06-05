/* 	
	kldcommander fun module, replace kernel entry and size
	tested on FreeBSD 9.3
	by dash

*/
#include <sys/types.h>
#include <sys/sysent.h>
#include <sys/syscall.h>
#include <sys/uio.h>
#include <sys/syscallsubr.h>
#include <sys/limits.h>
#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/pcpu.h>
#include <sys/proc.h>
#include <sys/syscallsubr.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <sys/sysproto.h>
#include <sys/linker.h>
#include <sys/cdefs.h>
#include <sys/libkern.h>

static int kldstat_hook(struct thread *td, struct kldstat_args *uap)
{
        struct kld_file_stat stat;
        int error, version;
	char newmod[32];
	long elite = 4919;
	bzero(newmod,sizeof(newmod));
	strncpy(newmod,"commander\x00",10);
        /*
         * Check the version of the user's structure.
         */
        if ((error = copyin(&uap->stat->version, &version, sizeof(version)))
            != 0)
                return (error);
        if (version != sizeof(struct kld_file_stat_1) &&
            version != sizeof(struct kld_file_stat))
                return (EINVAL);

        error = kern_kldstat(td, uap->fileid, &stat);
        if (error != 0)
                return (error);
	// lets replace some things :>
	if(strcmp(stat.name,"kernel")==0){
	bzero(stat.name,sizeof(stat.name));
	strncpy(stat.name,newmod,strlen(newmod));
	stat.size = elite;
	}
	return (copyout(&stat, uap->stat, version));
}
 
static int load_handler(module_t mod, int what, void *arg)
{
		int err = 0;

		switch(what)
		{
		case MOD_LOAD:
			sysent[SYS_kldstat].sy_call = (sy_call_t *)kldstat_hook;
			break;

		case MOD_UNLOAD:
			sysent[SYS_kldstat].sy_call = (sy_call_t *)sys_kldstat;
			break;

		default:
			err = EINVAL;
			break;
		}

		return(err);
}

// a struct that holds basic data on the module
static moduledata_t kldstat_mod =
{
		"stater",
		load_handler,
		NULL
};

DECLARE_MODULE(stater, kldstat_mod, SI_SUB_KLD, SI_ORDER_ANY); 
