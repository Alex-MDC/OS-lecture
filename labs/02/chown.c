
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <pwd.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {

int r;
uid_t owner;
struct passwd *pwd;

pwd = getpwnam(argv[2]);
	if(pwd == NULL){	
	       	fprintf(stderr, "error, user not found \n");
		}
owner = pwd->pw_uid;

r  = chown(argv[1], owner, -1);

if (r == -1) {
        fprintf(stderr, "chown failed \n");

        }
	else
	{
		fprintf(stderr,"owner successfully changed \n");
	}


return 0;
}


