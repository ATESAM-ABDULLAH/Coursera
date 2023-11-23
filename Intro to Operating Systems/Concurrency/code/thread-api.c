#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int a;
    int b;
} thread_args_t;

typedef struct
{
    int x;
    int y;
} func_args_t;

void *mythread(void *arg)
{
    func_args_t *rvals = malloc(sizeof(func_args_t));
    rvals->x = 1;
    rvals->y = 2;
    return (void *)rvals;
}

int main(int argc, char *argv[])
{
    pthread_t p;

    func_args_t *rvals;
    thread_args_t args = {10, 20};

    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **)&rvals);

    printf("returned %d %d\n", rvals->x, rvals->y);

    free(rvals);
    return 0;
}
