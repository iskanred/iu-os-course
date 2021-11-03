#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

#define KEYBOARD_EVENTS_HISTORY_BUFFER 20 // stores history of no more than 20 keyboard events
#define RELEASED 0
#define PRESSED 1
#define REPEATED 2

typedef struct input_event input_event;

/** Returns index of the previous key press(or repeat or release) event */
int getPrevEventIdx(int eventIdx) {
	return (KEYBOARD_EVENTS_HISTORY_BUFFER + (eventIdx - 1)) % KEYBOARD_EVENTS_HISTORY_BUFFER;
}

bool is_PE_shortcut(input_event events[KEYBOARD_EVENTS_HISTORY_BUFFER], int curEventIdx) {
	if (curEventIdx < 0 || curEventIdx >= KEYBOARD_EVENTS_HISTORY_BUFFER)
		return false;

	input_event *curEvent = &events[curEventIdx];

	int prev1Idx = getPrevEventIdx(curEventIdx);
	input_event *pPrev1Event = &events[prev1Idx];

	if ((int) curEvent->code == KEY_E && // if current is 'e'
		(pPrev1Event->value == PRESSED || pPrev1Event->value == REPEATED) && // if prev1 is pressed or repeated
		(int) pPrev1Event->code == KEY_P) // if prev1 is 'p'
	{
		return true;
	}

	return false;
}

bool is_CAP_shortcut(input_event events[KEYBOARD_EVENTS_HISTORY_BUFFER], int curEventIdx) {
	if (curEventIdx < 0 || curEventIdx >= KEYBOARD_EVENTS_HISTORY_BUFFER)
		return false;

	input_event *curEvent = &events[curEventIdx];

	int prev1Idx = getPrevEventIdx(curEventIdx);
	input_event *pPrev1Event = &events[prev1Idx];

	int prev2Idx = getPrevEventIdx(prev1Idx);
	input_event *pPrev2Event = &events[prev2Idx];

	if ((int) curEvent->code == KEY_P && // if current is 'p'
		(pPrev1Event->value == PRESSED || pPrev1Event->value == REPEATED) && // if prev1 is pressed or repeated
		(int) pPrev1Event->code == KEY_A && // if prev1 is 'a'
		(pPrev2Event->value == PRESSED || pPrev2Event->value == REPEATED) && // if prev2 is pressed or repeated
		(int) pPrev2Event->code == KEY_C) // if prev2 is 'c'
	{
		return true;
	}

	return false;
}

bool is_ILY_shortcut(input_event events[KEYBOARD_EVENTS_HISTORY_BUFFER], int curEventIdx) {
	if (curEventIdx < 0 || curEventIdx >= KEYBOARD_EVENTS_HISTORY_BUFFER)
		return false;

	input_event *curEvent = &events[curEventIdx];

	int prev1Idx = getPrevEventIdx(curEventIdx);
	input_event *pPrev1Event = &events[prev1Idx];

	int prev2Idx = getPrevEventIdx(prev1Idx);
	input_event *pPrev2Event = &events[prev2Idx];

	if ((int) curEvent->code == KEY_Y && // if current is 'y'
		(pPrev1Event->value == PRESSED || pPrev1Event->value == REPEATED) && // if prev1 is pressed or repeated
		(int) pPrev1Event->code == KEY_L && // if prev1 is 'l'
		(pPrev2Event->value == PRESSED || pPrev2Event->value == REPEATED) && // if prev2 is pressed or repeated
		(int) pPrev2Event->code == KEY_I) // if prev2 is 'i'
	{
		return true;
	}

	return false;
}



int main() {
	const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
	int fd = open(dev, O_RDONLY); // file desctiptor

	if (fd == -1) {
		printf("File with keyboard input events cannot be open\n");
		return EXIT_FAILURE;
	}

	printf("Available shortcuts: P+E, C+A+P, I+L+Y\n");
	
	input_event events[KEYBOARD_EVENTS_HISTORY_BUFFER]; // actual key press(or repeat or release) events
	int eventIdx = 0;

	input_event tmpEvent; // temp event to read in
	ssize_t n;

	while(1) {
        n = read(fd, &tmpEvent, sizeof tmpEvent); // num of bytes that are read successfully

        if (n == (ssize_t) - 1) {
            if (errno == EINTR) continue; // actually no error
            else break;
        } 
        else if (n != sizeof tmpEvent) {
            errno = EIO;
            break;
        }
	
		// check type of event and its value (RELEASED or PRESSED)
		// there is no need to consider repeated events since one press of any time period is enough for shortcut
		if (tmpEvent.type == EV_KEY && (tmpEvent.value == RELEASED || tmpEvent.value == PRESSED)) {
			events[eventIdx] = tmpEvent;
			
			if (is_PE_shortcut(events, eventIdx))
				printf("\nI passed the Exam!\n");
			else if (is_CAP_shortcut(events, eventIdx))
				printf("\nGet some cappuccino!\n");
			else if (is_ILY_shortcut(events, eventIdx))
				printf("\nI love you!\n");
			
			// if index == size of buffer => make index 0
			// (emulation of FIFO structure)
			if (++eventIdx == KEYBOARD_EVENTS_HISTORY_BUFFER)
				eventIdx = 0;
		}
	}

	fflush(stdout);
	return EXIT_FAILURE;
}
