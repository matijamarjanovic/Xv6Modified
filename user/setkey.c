#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

#define NULL ((void *)0)
#define INT_MAX 2147483646

void
usage(void)
{
	printf("\nUse this program to set file encryption key.\n");
	printf("After setting the key, you can use encr and decr with that key.\n");
	printf("Usage: setkey [OPTION]... [KEY]\n");
	printf("\nCommand line options:\n");
	printf("    -h, --help      Show help prompt\n");
	printf("    -s, --secret    Enter a hidden key via STDIN\n");
}

int
pintcheck(char *str){
	long long r = 0;
	if(*str == '-') return -1;
	while (*str != '\0') {
		if (*str >= '0' && *str <= '9')
			r = r * 10 + (*str++ - '0');
		else return -1;
		if(r > INT_MAX){
			return 2;
		}
	}
	return 1;
}

void
secret(int *k){
	int pic;
	char buf[200];
	
	printf("Enter the key: ");
	setecho(1);
	read(0, buf, sizeof(buf));
	setecho(0);
	
	for (int i = 0; i < 200; i++) {
		if (buf[i] == '\n') {
			buf[i] = '\0';
			break;
		}
	}
	
	if(buf[0] == '\0'){
		printf("setkey: key not entered\n");
		exit();
	} else if((pic = pintcheck(buf)) == 2){
		printf("setkey: key too big\n");
		exit();
	} else if(pic == -1){
		printf("setkey: key must be positive number\n");
		exit();
	}
	
	*k = atoi(buf);
}

int
main(int argc, char *argv[])
{
	int i, key = -1, n, sflag = 0, pic = 0;
	
	if(argc < 2){
		usage();
		exit();
	}

	for (i = 1; i < argc; i++) {
		if(strlen(argv[i]) > 10){
			printf("setkey: argument too big\n");
			exit();
		} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			usage();
			exit();
		} else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--secret") == 0){
			if(key != -1){
				printf("setkey: secret key must be given via STDIN\n");
				exit();
			}
			sflag = 1;
		} else if((pic = pintcheck(argv[i])) == 1){
			if(key != -1 || sflag){
				if(sflag) printf("setkey: secret key must be given via STDIN\n");
				else printf("setkey: only one key can be setted\n");
				exit();
			} else if((n = atoi(argv[i])) < 0){
				printf("setkey: key must be positive number\n");
				exit();
			}
			key = n;
		} else {
			if(pic == 2)
				printf("setkey: key too big\n");
			else if(pic == -1)
				printf("setkey: key must be positive number\n");
			exit();
		}
	}

	if(sflag) secret(&key);;
	setkey(key);

	exit();
}
