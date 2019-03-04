#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	int result;
    int bufSize = 41;
	char buf[bufSize];
    char *input;
	fd = open("/dev/encrypt", O_RDWR);

	if (fd == -1) {
		perror("Unable to open device");
		exit(1);
	}
	for(int i = 1; i < argc; i++)
	{
		input = argv[i];
		result = write(fd, argv[i], strlen(input));
		if (result != strlen(input)) {
			perror("problem writing to device");
			printf("result = %d\n", result);
		}
		if(!strstr(input, "KEY:"))
		{
		read(fd, buf, strlen(input));
		puts(buf);
		}
		memset(buf, 0, 41);
	}
	close(fd);
    return 0;
}
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <fcntl.h>

// int main(int argc, char **argv)
// {
// 	int fd;
// 	int result;
//     int bufSize = 41;
// 	char buf[bufSize];
// 	size_t size;
// 	fd = open("/dev/encrypt", O_RDWR);

// 	if (fd == -1) {
// 		perror("Unable to open device");
// 		exit(1);
// 	}
// 	for(int i = 1; i < argc; i++)
// 	{
// 		char *input = argv[i];
// 		// for(int j = 0; j < bufSize; j++)
// 		// {
// 		// 	buf[j] = input[j];
// 		// }
// 		// buf[bufSize-1] = 0;

// 		result = write(fd, input, strlen(input));
// 		if (result != strlen(input) || (result != 40 && strlen(input) > 40)) {
// 			perror("problem writing to device");
// 			printf("result = %d\n", result);
// 		}
// 		if(!strstr(input, "KEY:"))
// 		{
// 		size = sizeof(input) > 40 ? 40 : sizeof(input);
// 		read(fd, buf, size);
// 		puts(buf);
// 		}
// 	}
// 	close(fd);
//     return 0;
// }