#include "userprog/syscall.h"
#include <stdio.h>
#include <stdlib.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "devices/shutdown.h"
#include "userprog/pagedir.h"

#ifndef SUCCESS 
#define SUCCESS 1
#define FAILURE -1
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static void syscall_handler (struct intr_frame *);
void halt (void);
void exit (int *status);
//pid_t exec(const char *cmd_line);
void exec(const char *cmd_line);
int wait(int pid);
bool create(const char *file, unsigned initial_size);
bool remove(const char *file);
int open(const char *file);
int filesize(int fd);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void seek(int fd, unsigned position);
unsigned tell(int fd);
void close(int fd);
void check_ptr(int ptr);
void terminate_process(void);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
//  printf ("system call!\n");
  int type, status;
  int  rc=SUCCESS;
  int arg1, arg2, arg3;
  int *esp = (int *)(f->esp);
  type = *esp;
  arg1 = *++esp;
  arg2 = *++esp;
  arg3 = *++esp;
  //esp -= 4;
 switch (type) {
    case SYS_HALT:{ halt(); 
		    break;
		  }
    case SYS_EXIT:{ exit(&arg1); //arg1 set by exit
		    f->eax = arg1;
		    break;
		  }
    case SYS_EXEC:{ check_ptr(arg1);
		    exec((const char *)arg1); 
  		    break;
		  }
    case SYS_WAIT:{ wait((int)arg1);
		    break;
		  }
    case SYS_CREATE:
		  { check_ptr(arg1);
		    create((const char *)arg1, (unsigned)arg2);
   		    break;
		  }
    case SYS_REMOVE:
		  { check_ptr(arg1);
		    remove((const char *)arg1);
		    break;
   		  }
    case SYS_OPEN:{ check_ptr(arg1);
		    open((const char *)arg1);
		    break; 		
	          }
    case SYS_FILESIZE:
		  { filesize((int)arg1);
		    break;
		  }
    case SYS_READ:{ check_ptr(arg2);
		    read((int)arg1, (void *)arg2, (unsigned)arg3);
		    break;
		  }
    case SYS_WRITE:
		  { check_ptr(arg2);
		    write((int)arg1, (const void *)arg2, (unsigned)arg3);
		    break;
		  }
    case SYS_SEEK:{ seek((int)arg1, (unsigned)arg2);
		    break;
		  } 
    case SYS_TELL:{ tell((int)arg1);
		    break;
		  }
    case SYS_CLOSE:
		  { close((int)arg1);
		    break;
		  } 
  }
  thread_exit ();
}

void halt (void)
{
  shutdown_power_off();
}

void exit (int *status)
{
 //process_exit(); //From process.c and thread.c
  struct thread *cur = thread_current();
  uint32_t *pd;
  pd = cur->pagedir;
  *status = 0; // success
  if (pd != NULL) {
    cur->pagedir = NULL;
    pagedir_activate (NULL);
    pagedir_destroy (pd);
  } 
  else {
    *status=-1; //pd NULL already
  }
  list_remove (&thread_current()->allelem);
  thread_current()->status = THREAD_DYING;

  // TODO: print exit(%d)\n", ...); process_name and return code
  // TODO: Release all locks acquired by current thread
  // TODO: Release all file descriptors held by current thread 
}

void exec (const char *cmd_line)
{
}

int wait (int pid)
{
  return 0;
}

bool create (const char *file, unsigned initial_size)
{
  return 0;
}

bool remove (const char *file)
{
  return 0;
}

int open (const char *file)
{
  return 0;
}

int filesize (int fd)
{
  return 0;
}

int read (int fd, void *buffer, unsigned size)
{
  return 0;
}

int write (int fd, const void *buffer, unsigned size)
{
  
  return 0;
}

void seek (int fd, unsigned position)
{
}

unsigned tell (int fd)
{
  return 0;
}

void close (int fd)
{
}

void check_ptr(int ptr)
{
  struct thread *t;
  t = thread_current();
  if( !ptr && is_user_vaddr((const void *)ptr) && 
       pagedir_get_page(t->pagedir, (const void *)ptr) ){
     return;
  } 
  else {
     terminate_process();
  }
}

void terminate_process(void)
{
   return;  //Same as exit - terminate the process and free its resources
}

