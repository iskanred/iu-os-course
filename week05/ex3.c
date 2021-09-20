#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int  produceItem();
void putItemIntoBuffer(int item);
int  removeItemFromBuffer();
void sleepProducer();
void wakeupProducer();
void sleepConsumer();
void wakeupConsumer();


/* SHARED RESOURCES */
int BUFFER[BUFFER_SIZE];
int itemCount = 0;

int sleepProducerFlag = 0;
int sleepConsumerFlag = 0;


void *producer(void *p) {
    while (1) {
        int item = produceItem();

        if (itemCount == BUFFER_SIZE) {
            sleepProducer();
        }

        putItemIntoBuffer(item);
        ++itemCount;

        printf("The element %d was PRODUCED at %d position\n", item, itemCount - 1);
        usleep(100000); // to make I/O work correctly: 0.1 sec

        if (itemCount == 1) {
            wakeupProducer();
        }
    }

    return NULL;
}

void *consumer(void *p) {
    while (1) {
        if (itemCount == 0) {
            sleepConsumer();
        }

        int item = removeItemFromBuffer();
        --itemCount;

        printf("The element %d was CONSUMED at %d position\n", item, itemCount);
        usleep(100000); // to make I/O work correctly: 0.1 sec

        if (itemCount == BUFFER_SIZE - 1) {
            wakeupConsumer();
        }
    }

    return NULL;
}



int main() {
    srand(time(NULL));

    pthread_t producerThreadId;
    pthread_t consumerThreadId;
    
    if (pthread_create(&producerThreadId, NULL, producer, NULL)) {
        printf("ERROR IN CREATING A PRODUCER THREAD!\n");
        pthread_exit(NULL);
        return EXIT_FAILURE;
    }

    if (pthread_create(&consumerThreadId, NULL, consumer, NULL)) {
        printf("ERROR IN CREATING A CONSUMER THREAD!\n");
        pthread_exit(NULL);
        return EXIT_FAILURE;
    }
    
    pthread_join(consumerThreadId, NULL);
    pthread_join(producerThreadId, NULL);
    
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}



/* ======<Functions implementation>====== */

int produceItem() {
    return rand() % 1000 + 1;
}


/* Buffer operations */

void putItemIntoBuffer(int item) {
    BUFFER[itemCount] = item;
}

// Remove item from buffer and return it
int removeItemFromBuffer() {
    int toRemove = BUFFER[itemCount - 1];
    BUFFER[itemCount - 1] = -1;

    return toRemove;
}


/* Sleep & wakeup functions */

void sleepProducer() {
    sleepProducerFlag = 1;
    while(sleepProducerFlag);
}

void wakeupProducer() {
    sleepProducerFlag = 0;
}

void sleepConsumer() {
    sleepConsumerFlag = 1;
    while(sleepConsumerFlag);
}

void wakeupConsumer() {
    sleepConsumerFlag = 0;
}
