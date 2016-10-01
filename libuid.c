#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

uid_t getuid(void) {
	uid_t (*original_getuid)(void);
	original_getuid = dlsym(RTLD_NEXT, "getuid");
	uid_t orig_return = (*original_getuid)();

	fprintf(stderr,"getuid() :%d:%s\n",orig_return,program_invocation_short_name);

	return orig_return;
}

uid_t geteuid(void) {
	uid_t (*original_geteuid)(void);
	original_geteuid = dlsym(RTLD_NEXT, "geteuid");
	uid_t orig_return = (*original_geteuid)();

	fprintf(stderr,"geteuid():%d:%s\n",orig_return,program_invocation_short_name);

	return orig_return;
}
