#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    double decimal;
    int frac[2];
} frac_heap_node;

void percolateDown(frac_heap_node* arr, int arrLen, int idx)
{
    size_t left = 2 * idx,
           right = 2 * idx + 1,
           largest = idx;

    if(left < arrLen && arr[left].decimal < arr[largest].decimal)
        largest = left;

    if(right < arrLen && arr[right].decimal < arr[largest].decimal)
        largest = right;

    if(largest != idx)
    {
        frac_heap_node tmp = arr[idx];
        arr[idx] = arr[largest];
        arr[largest] = tmp;

        percolateDown(arr, arrLen, largest);
    }
}

void heapify(frac_heap_node* arr, int arrLen)
{
    int i = arrLen / 2;
    for(int i = arrLen; i >= 0; --i)
        percolateDown(arr, arrLen, i);
}

frac_heap_node getFirst(frac_heap_node* arr, int* arrLen)
{
    frac_heap_node front = arr[0];

    arr[0] = arr[*arrLen - 1];
    *arrLen -= 1;

    percolateDown(arr, *arrLen, 0);
    return front;
}


int* kthSmallestPrimeFraction(int* arr, int arrSize, int k, int* returnSize) 
{
    
    *returnSize = 2;
    int* ret = (int*)malloc(sizeof(int) * 2);

    if(arrSize == 2)
    {
        ret[0] = arr[0];
        ret[1] = arr[1];
        return ret;
    }

    frac_heap_node heap[arrSize * arrSize];

    int currHeapIdx = 0;
    for(int i = 0; i < arrSize; i++)
        for(int j = i + 1; j < arrSize; j++)
        {
            frac_heap_node* curr = &heap[currHeapIdx++];
            curr->frac[0] = arr[i];
            curr->frac[1] = arr[j];
            curr->decimal = ((double)curr->frac[0]) / curr->frac[1];
        }

    heapify(heap, currHeapIdx);

    for(int i = 0; i < k - 1; i++)
    {
        getFirst(heap, &currHeapIdx);
    }

    frac_heap_node retNode = getFirst(heap, &currHeapIdx);

    ret[0] = retNode.frac[0];
    ret[1] = retNode.frac[1];
    return ret;
}



int main()
{
    {
        int arrHappiness[] = {1, 2, 3, 5};
        int retSize = 0;
        int* frac = kthSmallestPrimeFraction(arrHappiness, 4, 3, &retSize);
        printf("Res: [%d, %d]\n", frac[0], frac[1]);
        free(frac);
    }

        {
        int arrHappiness[] = {1, 7, 13};
        int retSize = 0;
        int* frac = kthSmallestPrimeFraction(arrHappiness, 3, 1, &retSize);
        printf("Res: [%d, %d]\n", frac[0], frac[1]);
        free(frac);
    }
}