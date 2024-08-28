#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define NULL ((void *)0)

void
usage(void)
{
	printf("\nEncrypt a file using a provided key.\n");
	printf("Usage: encr [OPTION]... [FILE]\n");
    printf("\nCommand line options:\n");
    printf("    -h, --help          Show help prompt\n");
    printf("    -a, --encrypt-all   Encrypt all files in CWD with current key\n");
}

void
encrypt(char *name){
	int fd = open(name, O_RDWR), k;
	if(fd < 0){
		printf("encr: failed to encrypt, cannot open %s\n", name);
		return;
	}

	if((k = encr(fd)) == -1){
		printf("encr: failed to encrypt %s, key not set\n", name);
	}
	else if(k == -2){
		printf("encr: failed to encrypt %s, file is device\n", name);
	}
	else if(k == -3){
		printf("encr: failed to encrypt %s, file already encripted\n", name);
	}
	
	if(k == 0)
		printf("encr: sucessfully encrypted %s\n", name);

	close(fd);
}

void
encrall(char *path){
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	
	if((fd = open(path, 0)) < 0){
		printf("encr: cannot open %s\n", path);
		return;
	}
	if(fstat(fd, &st) < 0){
		printf("encr: cannot stat %s\n", path);
		close(fd);
		return;
	}
	if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
		printf("encr: path too long\n");
		close(fd);
		return;
	}
	strcpy(buf, path);
	p = buf+strlen(buf);
	*p++ = '/';
	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(de.inum == 0)
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0){
			printf("encr: cannot stat %s\n", buf);
			continue;
		}
	
		char *l;
		for(l=buf+strlen(buf); l >= buf && *l != '/'; l--)
			;
		l++;

		encrypt(l);
	}
}

int
main(int argc, char *argv[])
{	
	int i ;
	if(argc < 2){
		usage();
		exit();
	}

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			usage();
			exit();
		} else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--encrypt-all") == 0) {
			encrall(".");
			break;
		} else if(i+1 < argc){
			printf("Usage: decr [OPTION]... [FILE]\n");
			exit();
		} else if (strlen(argv[i]) > 14){
			printf("encr: filename must be 14 characters or less\n");
			exit();
		} else {
			encrypt(argv[i]);
		}
	}
	
	exit();
}
