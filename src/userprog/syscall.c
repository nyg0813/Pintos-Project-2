#include "userprog/syscall.h"
#include <stdio.h>
#include <stdlib.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

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

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  int syscall_type, status;
  int arg1, arg2, arg3;
  char **esp = f->esp;
  *esp += sizeof(int);
  memcpy(&syscall_type, *esp, sizeof(int));
 
  *esp += sizeof(int);
  memcpy(&arg1, *esp, sizeof(int));
  
  *esp += sizeof(int);
  memcpy(&arg2, *esp, sizeof(int));
  
  *esp += sizeof(int);
  memcpy(&arg3, *esp, sizeof(int));

  *esp -= (sizeof(int) *3); //Restore SP
	
  switch (syscall_type) {
    case SYS_HALT:{ halt(); 
		    break;
		  }
    case SYS_EXIT:{ exit((int *)arg1); 
		    break;
		  }
    case SYS_EXEC:{ exec((const char *)arg1); 
		    break;
		  }
    case SYS_WAIT:{ wait((int)arg1);
		    break;
		  }
    case SYS_CREATE:
		  { create((const char *)arg1, (unsigned)arg2);
   		    break;
		  }
    case SYS_REMOVE:
		  { remove((const char *)arg1);
		    break;
   		  }
    case SYS_OPEN:{ open((const char *)arg1);
		    break; 		
	          }
    case SYS_FILESIZE:
		  { filesize((int)arg1);
		    break;
		  }
    case SYS_READ:{ read((int)arg1, (void *)arg2, (unsigned)arg3);
		    break;
		  }
    case SYS_WRITE:
		  { write((int)arg1, (const void *)arg2, (unsigned)arg3);
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
}

void exit (int *status)
{
}

void exec(const char *cmd_line)
{
}

int wait(int pid)
{
  return 0;
}

bool create(const char *file, unsigned initial_size)
{
  return 0;
}

bool remove(const char *file)
{
  return 0;
}

int open(const char *file)
{
  return 0;
}

int filesize(int fd)
{
  return 0;
}

int read(int fd, void *buffer, unsigned size)
{
  return 0;
}

int write(int fd, const void *buffer, unsigned size)
{
  return 0;
}

void seek(int fd, unsigned position)
{
}

unsigned tell(int fd)
{
  return 0;
}

void close(int fd)
{
}

