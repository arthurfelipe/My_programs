#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// sum computed by the background  thread
long long sum = 0;

// thread function that generate a sum of 0 to N
void* sum_runner(void* arg)
{
    long long *limit_ptr = (long long*)arg;
    long long limit = *limit_ptr;

    for(long long i = 0; i <= limit; i++)
    {
        sum += i;
    } 
    // sum is a global variable
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: %s <num>\n", argv[0]);
        exit(-1);
    }

    long long limit = atoll(argv[1]);

    // Thread ID
    pthread_t tid;

    // Create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, sum_runner, &limit);

    // Do other stuff here...

    // wait until thread is done
    pthread_join(tid, NULL);

    printf("Sum is %lld\n", sum);
}