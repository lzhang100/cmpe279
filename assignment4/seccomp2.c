#include <stdio.h>
#include <sys/prctl.h>
#include <seccomp.h>
#include <unistd.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int
main(int argc, char **argv)
{
	char * noargv[] = {NULL};

	scmp_filter_ctx ctx;

	printf("1. Init filter\n");

	ctx = seccomp_init( SCMP_ACT_LOG);

	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);

	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access), 0);

	seccomp_load(ctx);

	printf("2. Trying to exec a shell\n");

	//execvp("/bin/bash", noargv);
int fd = open("file.txt", O_RDONLY);

	printf("3. Shell executed\n");

	return 0;
}
