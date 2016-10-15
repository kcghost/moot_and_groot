/* Copyright (C) 2016 Casey Fitzpatrick
 *
 * This file is part of moot_and_groot.
 * 
 * moot_and_groot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * moot_and_groot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with moot_and_groot.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

uid_t getfakeid(bool euid) {
	char* uid_func;
	const char* env_uid;
	char conf_program_name[255];
	int conf_uid;
	int conf_euid;

	if(euid) {
		uid_func = "geteuid";
	} else {
		uid_func = "getuid";
	}

	/* Default to the real value */
	uid_t (*real_getuid)(void);
	real_getuid = dlsym(RTLD_NEXT, uid_func);
	uid_t uid = (*real_getuid)();

	/* Check conf file */
	FILE* pFile = fopen(PREFIX_PATH"/etc/uid.conf","r");
	if(pFile != NULL) {
		while(fscanf(pFile,"%255s %d %d%*[^\n]%*c",conf_program_name,&conf_uid,&conf_euid) == 3) {
			if(strcmp(conf_program_name,program_invocation_short_name) == 0) {
				if(euid) {
					uid = conf_euid;
				} else {
					uid = conf_uid;
				}
			}
		}
	}

	/* Check env overrides */
	if(euid) {
		env_uid = getenv("LIBUID_EUID");
		if(env_uid != NULL) {
			uid = strtol(env_uid, NULL, 10);
		}
	} else {
		env_uid = getenv("LIBUID_UID");
		if(env_uid != NULL) {
			uid = strtol(env_uid, NULL, 10);
		}
	}

	if(getenv("LIBUID_VERBOSE") != NULL) {
		fprintf(stderr,"%-7s:%d:%s\n",uid_func,uid,program_invocation_short_name);
	}

	return uid;
}

uid_t getuid(void) {
	return getfakeid("getuid");
}

uid_t geteuid(void) {
	return getfakeid("geteuid");
}
