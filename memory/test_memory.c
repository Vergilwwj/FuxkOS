#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

static const char *memory_file_name = "/dev/my_memory_test_drv";
static const char write_buf[] = "You think you stand a chance ?";
static char read_buf[1024] = {0};

int main(int argc, char const *argv[])
{
	ssize_t write_size = 0, read_size = 0; 
	int fd = open(memory_file_name, O_RDWR);
	if (fd < 0) {
		printf("fd open failed\n");
		return -1;
	}

	write_size = write(fd, write_buf, sizeof(write_buf));
	if (write_size < 0) {
		printf("memory_test write failed\n");
		return -1;
	}

	read_size = read(fd, read_buf, sizeof(read_buf));
	if (read_size < 0) {
		printf("memory_test read failed\n");
		return -1;
	}

	printf("%s\n", read_buf);

	return 0;
}
