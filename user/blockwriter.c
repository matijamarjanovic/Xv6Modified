#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

#define NULL ((void *)0)
#define INT_MAX 2147483647

void
usage(void)
{
	printf("\nUse this program to create a big files filled with a-z characters.\n");
	printf("Default filename: long.txt\n");
	printf("Default number of blocks: 150\n");
	printf("Usage: blockwriter [OPTION]...\n");
	printf("\nCommand line options:\n");
	printf("    -h, --help         Show help prompt\n");
	printf("    -o, --output FILE  Set output filename\n");
	printf("    -b, --blocks N     Number of blocks to write\n");
}

int
pintcheck(char *str){
	long long r = 0;
	while (*str != '\0') {
		if (*str >= '0' && *str <= '9')
			r = r * 10 + (*str++ - '0');
		else return -1;
		if(r > INT_MAX)
			return -1;
	}
	return 1;
}

int
main(int argc, char *argv[])
{
	char buf[512], alphabet[] = "abcdefghijklmnopqrstuvwxyz", *name;
	int fd, i = 0, n = -1, curBlock = 0;

	name = malloc(14 * sizeof(char));
	name = NULL;

	for (i = 1; i < argc; i++) {
		if(strlen(argv[i]) > 10){
			printf("blockwriter: argument too big\n");
			exit();;
		} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			usage();
			exit();
		} else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-file") == 0) {
			if(name != NULL){
				printf("blockwriter: only one form of the -o/--output-file option can be used\n");
				exit();
			} else if (i + 1 < argc) {
				if (strlen(argv[i+1]) > 14) {
					printf("blockwriter: filename must be 14 characters or less\n");
					exit();
				}
				name = argv[i + 1];
				i++;
			} else {
				printf("blockwriter: option requires an argument -- 'o'\n");
				exit();
			}
		} else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--blocks") == 0) {
			if (n != -1) {
				printf("blockwriter: only one form of the -b/--blocks option can be used\n");
				exit();
			} else if (i + 1 >= argc){
				printf("blockwriter: option requires an argument N\n");
				exit();
			} else if ((pintcheck(argv[i + 1]) == -1) || ((n = atoi(argv[i + 1])) <= 0) || (n > 16523)) {
				printf("blockwriter: block count must be positive number of 16523 or less\n");
				exit();
			}
			i++;
		} else {
			printf("blockwriter: invalid option '%s'\n", argv[i]);
			exit();
		}
	}
	
	if(name == NULL) name = "long.txt";
	if(n == -1) n = 150;	

	unlink(name);
	
	for (int i = 0; i < 512; i++)
    	buf[i] = alphabet[i % (sizeof(alphabet) - 1)];

	fd = open(name, O_CREATE | O_WRONLY);
	if(fd < 0){
		printf("blockwriter: cannot open %s for writing\n", name);
		exit();
	}
	
	while(curBlock < n){
		printf("Writing block %d\n", curBlock);
		//memset(buf, curBlock%10+'0', sizeof(buf));
		int cc = write(fd, buf, sizeof(buf));
		if(cc <= 0)
			break;
		curBlock++;
	}

	close(fd);
	
	exit();
}

