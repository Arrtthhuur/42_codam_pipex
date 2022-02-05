# Pipex - 42 Codam project

This project is the discovery in detail and by programming of a UNIX
mechanism that you already know.

## Allowed functions

### access

Check user's permission for a file.

```bash
#include <unistd.h>

int access(const char *pathname, int mode);
```

Return:
- success: 0 (all requested permissions are granted, or mode is F_OK and file exists)
- error: -1, and errno set appropriately

### open

### unlink

Delete a name and possibly the file it refers to.

```bash
#include <unistd.h>

int unlink(const char *pathname);
```

Return:
- success: 0
- error: -1, and errno set appropriately

### close

### read

### write

### malloc

### waitpid

Suspends execution of the calling process until a child specified by ***pid*** argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.

Value of ***pid***:
- smaller than -1 : wait for any child process whose process group ID is equal to | value | of ***pid***
- -1 : wait for any child process
- 0 : wait for any child process whose process group ID is equal to that of the calling process
- greater than 0 : wait for the child whose process ID is equal to the value of ***pid***

```bash
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```

Return:
- success: process ID of the child whose state has changed
- error: -1

### wait

Suspends execution of the calling process until one of its children terminates. The call wait(&status) is equivalent to:
waitpid(-1, &status, 0);

```bash
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);
```

Return:
- success: process ID of the terminated child
- error: -1

### free

### pipe

Creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. 

***pipefd[0]*** refers to the read end of the pipe.

***pipefd[1]*** refers to the write end of the pipe.  Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.

```bash
#include <unistd.h>

int pipe(int pipefd[2]);
```

Return:
- success: 0
- error: -1, errno set to indicate the error and pipefd is left unchanged

### dup, dup2

The dup() system call allocates a new file descriptor that refers to the same open file description as the descriptor ***oldfd***.

The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in ***newfd***.  In other words, the file descriptor ***newfd*** is adjusted so that it now refers to the same open file description as ***oldfd***.

```bash
#include <unistd.h>

int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

Return:
- success: the new file descriptor
- error: -1, errno set to indicate the error

### execve

Executes the program referred to by ***pathname***. 

***argv*** is an array of pointers to strings passed to the new program as its command-line arguments. 

***envp*** is an array of pointers to strings, conventionally of the form key=value, which are passed as the environment of the new program.

```bash
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);
```

Return:
- success: no return
- error: -1, errno set to indicate the error

### fork

Creates a new process by duplicating the calling process. The new process is referred to as the child process.  The calling process is referred to as the parent process.

```bash
#include <unistd.h>

pid_t fork(void);
```

Return:
- success: PID of child process is returned in the parent, 0 is returned in the child.
- error: -1 is returned in the parent, no child process is created and errno is set to indicate the error

### perror

Print a system error message.

```bash
#include <stdio.h>

void perror(const char *s);
```

### strerror

Return string describing error number.

```bash
#include <string.h>

char *strerror(int errnum);
```

### exit
