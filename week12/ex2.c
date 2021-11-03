#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

typedef struct input_event input_event;

static const char *const eventValNames[3] = {
	"RELEASED",
    "PRESSED ",
    "REPEATED"
};

int main() {
	const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
	int fd = open(dev, O_RDONLY); // file desctiptor

	if (fd == -1) {
		printf("File with keyboard input events cannot be open\n");
		return EXIT_FAILURE;
	}

	input_event event;
	ssize_t n;

	while (1) {
        n = read(fd, &event, sizeof event); // num of bytes that are read successfully

		if (n == (ssize_t) - 1) {
            if (errno == EINTR) // actually no error
                continue;
            else
                break;
        } 
        else if (n != sizeof event) {
            errno = EIO;
            break;
        }

		// check type of event and range on value type (RELEASED, PRESSED, REPEATED)
		if (event.type == EV_KEY && event.value >= 0 && event.value <= 2)
			printf("\n%s 0x%04X (%d)\n", eventValNames[event.value], (int)event.code, (int)event.code);
	}
	
	fflush(stdout);
	return EXIT_FAILURE;
}
