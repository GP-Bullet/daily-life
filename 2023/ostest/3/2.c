int buffer[M] = { 0 };
int in = 0, out = 0, count = 0;
sem_t empty_sem, full_sem;
pthread_mutex_t mutex;

void *producer(void *args) {
    int id = *(int *)args;
    while (true) {
        int item = produce(id);
        P(&empty_sem);
        pthread_mutex_lock(&mutex);
        insert_item(item);
        printf("Producer %d produced item %d\n", id, item);
        print_buffer();
        pthread_mutex_unlock(&mutex);
        V(&full_sem);
        sleep(1);
    }
}

void *consumer(void *args) {
    int id = *(int *)args;
    while (true) {
        P(&full_sem);
        pthread_mutex_lock(&mutex);
        int item = remove_item();
        printf("Consumer %d consumed item %d\n", id, item);
        print_buffer();
        pthread_mutex_unlock(&mutex);
        V(&empty_sem);
        sleep(1);
    }
}