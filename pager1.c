#include<stdio.h>
#include<sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#
commentprakash
#define DEF_PAGER "/bin/more"
#define MAXLINE 255

void err_sys(const char* x){
	perror(x);
	exit(1);
}

/* default pager program */
int main(int argc, char *argv[])
{
int n;
int fd[2];
pid_t pid;
char *pager, *argv0;
char line[MAXLINE];
FILE *fp;
if (argc != 2)
{
	printf("usage: a.out <pathname> \n");
	exit(1);
}
if ((fp = fopen(argv[1], "r")) == NULL)
	err_sys(argv[1]);
if (pipe(fd) < 0)
        perror("pipe error");
if ((pid = fork()) < 0) {
	err_sys("fork error");
} else if (pid > 0) {
	close(fd[0]);
/* close read end */
/* parent */
/* parent copies argv[1] to pipe */
while (fgets(line, MAXLINE, fp) != NULL) {
	n = strlen(line);
if (write(fd[1], line, n) != n)
	err_sys("write error to pipe");
}
/*if (ferror(fp))
	err_sys("fgets error");*/
	close(fd[1]);
/* close write end of pipe for reader */
if (waitpid(pid, NULL, 0) < 0)
	err_sys("waitpid error");
	exit(0);
} else {
/* child */
	close(fd[1]);
/* close write end */
if (fd[0] != 0) {
if (dup2(fd[0], 0) != 0)
	err_sys("dup2 error to stdin");
	close(fd[0]);
/* don’t need this after dup2 */
}
/* get arguments for execl() */
if ((pager = getenv("PAGER")) == NULL)
	pager = DEF_PAGER;
if ((argv0 = strrchr(pager,'/')) != NULL)
	argv0++;
/* step past rightmost slash */
else
	argv0 = pager; /* no slash in pager */
	if (execl(pager, argv0, (char *)0) < 0)
	printf("execl error for %s", pager);
}
	exit(0);
}

=======
#include<stdio.h>
#include<sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#commentfddhfksdlfhjsdfshadf
#define DEF_PAGER "/bin/more"
#define MAXLINE 255
void err_sys(const char* x){
	perror(x);
	exit(1);
}

/* default pager program */
int main(int argc, char *argv[])
{
int n;
int fd[2];
pid_t pid;
char *pager, *argv0;
char line[MAXLINE];
FILE *fp;
if (argc != 2)
{
	printf("usage: a.out <pathname> \n");
	exit(1);
}
if ((fp = fopen(argv[1], "r")) == NULL)
	err_sys(argv[1]);
if (pipe(fd) < 0)
        perror("pipe error");
if ((pid = fork()) < 0) {
	err_sys("fork error");
} else if (pid > 0) {
	close(fd[0]);
/* close read end */
/* parent */
/* parent copies argv[1] to pipe */
while (fgets(line, MAXLINE, fp) != NULL) {
	n = strlen(line);
if (write(fd[1], line, n) != n)
	err_sys("write error to pipe");
}
/*if (ferror(fp))
	err_sys("fgets error");*/
	close(fd[1]);
/* close write end of pipe for reader */
if (waitpid(pid, NULL, 0) < 0)
	err_sys("waitpid error");
	exit(0);
} else {
/* child */
	close(fd[1]);
/* close write end */
if (fd[0] != 0) {
if (dup2(fd[0], 0) != 0)
	err_sys("dup2 error to stdin");
	close(fd[0]);
/* don’t need this after dup2 */
}
/* get arguments for execl() */
if ((pager = getenv("PAGER")) == NULL)
	pager = DEF_PAGER;
if ((argv0 = strrchr(pager,'/')) != NULL)
	argv0++;
/* step past rightmost slash */
else
	argv0 = pager; /* no slash in pager */
	if (execl(pager, argv0, (char *)0) < 0)
	printf("execl error for %s", pager);
}
	exit(0);
}
