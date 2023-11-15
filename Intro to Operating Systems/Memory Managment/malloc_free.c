#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 20000 // Size of memory in bytes


struct block{
 size_t size;
 int free;
 struct block *next; 
};

char memory[MEMORY_SIZE];
struct block *freeList=(void*)memory;

void initialize()
{
    freeList->size = 20000 - sizeof(struct block);
    freeList->free = 1;
    freeList->next = NULL;
}

void split(struct block *fitting_slot, size_t size)
{
    struct block *new = (void *)((void *)fitting_slot + size + sizeof(struct block));
    new->size = (fitting_slot->size) - size - sizeof(struct block);
    new->free = 1;
    new->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;
}

void merge()
{
    struct block *curr, *prev;
    curr = freeList;
    while ((curr->next) != NULL)
    {
        if ((curr->free) && (curr->next->free))
        {
            curr->size += (curr->next->size) + sizeof(struct block);
            curr->next = curr->next->next;
        }
        prev = curr;
        curr = curr->next;
    }
}

void *MyMalloc(size_t noOfBytes)
{
    struct block *curr, *prev;
    void *result;

    // add your code below this line

    if (!(freeList->size))
    {
        initialize();
        printf("Memory initialized\n");
    }
    curr = freeList;
    while ((((curr->size) < noOfBytes) || ((curr->free) == 0)) && (curr->next != NULL))
    {
        prev = curr;
        curr = curr->next;
        printf("One block checked\n");
    }
    if ((curr->size) == noOfBytes)
    {
        curr->free = 0;
        result = (void *)(++curr);
        printf("Exact fitting block allocated\n");
        return result;  
    }
    else if ((curr->size) > (noOfBytes + sizeof(struct block)))
    {
        split(curr, noOfBytes);
        result = (void *)(++curr);
        printf("Fitting block allocated with a split\n");
        return result;
    }
    else
    {
        result = NULL;
        printf("Sorry. No sufficient memory to allocate\n");
        return result;
    }

    // add your code above this line
}

void MyFree(void *ptr)
{

    // add your code below this line
    if (((void *)memory <= ptr) && (ptr <= (void *)(memory + 20000)))
    {
        struct block *curr = ptr;
        --curr;
        curr->free = 1;
        merge();
        printf("Memory freed successfully\n");
    }
    else
        printf("Please provide a valid allocated pointer\n");
    // add your code above this line
}

int main()
{

    int *p = (int *)MyMalloc(100 * sizeof(int));
    char *q = (char *)MyMalloc(250 * sizeof(char));
    int *r = (int *)MyMalloc(1000 * sizeof(int));

    MyFree(p);

    char *w = (char *)MyMalloc(700);

    MyFree(r);

    int *k = (int *)MyMalloc(500 * sizeof(int));
    printf("Allocation and deallocation is done successfully! \n");
}