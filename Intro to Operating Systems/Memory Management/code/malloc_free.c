#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 20000 // Size of memory in bytes

typedef struct block
{
    size_t size;        // Size of the block
    int free;           // Flag indicating if the block is free (1) or allocated (0)
    struct block *next; // Pointer to the next block in the memory
} metadata;

char memory[MEMORY_SIZE];                // Array representing the memory space
metadata *freeList = (metadata *)memory; // Starting point of the memory (free list)

// Initialize the free list
void initialize()
{
    freeList->size = MEMORY_SIZE - sizeof(metadata);
    freeList->free = 1;
    freeList->next = NULL;
}

// Split a block into two parts after allocating memory
void split(metadata *fitting_slot, size_t size)
{
    // Creating a new block to utilize the remaining memory after allocation
    metadata *new = (metadata *)((void *)fitting_slot + size + sizeof(metadata));
    new->size = (fitting_slot->size) - size - sizeof(metadata);
    new->free = 1;
    new->next = fitting_slot->next;

    // Adjusting the original block after splitting
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;
}

// Merge consecutive free blocks in memory
void merge()
{
    metadata *curr, *prev;
    curr = freeList;
    while ((curr->next) != NULL)
    {
        if ((curr->free) && (curr->next->free))
        {
            // Merge current and next block when both are free
            curr->size += (curr->next->size) + sizeof(metadata);
            curr->next = curr->next->next;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Memory allocation function
void *MyMalloc(size_t noOfBytes)
{
    metadata *curr, *prev;
    void *result;

    // If memory is not initialized, set up the free list
    if (!(freeList->size))
    {
        initialize();
        printf("Memory initialized\n");
    }

    curr = freeList;
    // Traverse the free list to find a suitable block for allocation
    while ((((curr->size) < noOfBytes) || ((curr->free) == 0)) && (curr->next != NULL))
    {
        prev = curr;
        curr = curr->next;
        printf("One block checked\n");
    }

    // Allocate memory in the fitting block or split it if large enough
    if ((curr->size) == noOfBytes)
    {
        curr->free = 0;
        result = (void *)(++curr);
        printf("Exact fitting block allocated\n");
        return result;
    }
    else if ((curr->size) > (noOfBytes + sizeof(metadata)))
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
}

// Memory deallocation function
void MyFree(void *ptr)
{
    // Check if the provided pointer is within the valid range of memory
    if (((void *)memory <= ptr) && (ptr <= (void *)(memory + MEMORY_SIZE)))
    {
        metadata *curr = ptr;
        --curr;
        curr->free = 1;
        merge();
        printf("Memory freed successfully\n");
    }
    else
    {
        printf("Please provide a valid allocated pointer\n");
    }
}

// Main function for testing memory allocation and deallocation
int main()
{
    // Memory allocation and deallocation test cases
    int *p = (int *)MyMalloc(100 * sizeof(int));
    char *q = (char *)MyMalloc(250 * sizeof(char));
    int *r = (int *)MyMalloc(1000 * sizeof(int));

    MyFree(p);

    char *w = (char *)MyMalloc(700);

    MyFree(r);

    int *k = (int *)MyMalloc(500 * sizeof(int));
    printf("Allocation and deallocation is done successfully! \n");
    return 0;
}
