#include <stdio.h>

void percolateDown(int* arr, int arrLen, int idx)
{
    size_t left = 2 * idx,
           right = 2 * idx + 1,
           largest = idx;

    if(left < arrLen && arr[left] > arr[largest])
        largest = left;

    if(right < arrLen && arr[right] > arr[largest])
        largest = right;

    if(largest != idx)
    {
        int tmp = arr[idx];
        arr[idx] = arr[largest];
        arr[largest] = tmp;

        percolateDown(arr, arrLen, largest);
    }
}

void heapify(int* arr, int arrLen)
{
    int i = arrLen / 2;
    for(int i = arrLen; i >= 0; --i)
        percolateDown(arr, arrLen, i);
}

int getFirst(int* arr, int* arrLen)
{
    int front = arr[0];

    arr[0] = arr[*arrLen - 1];
    *arrLen -= 1;

    percolateDown(arr, *arrLen, 0);
    return front;
}

long long maximumHappinessSum(int* happiness, int happinessSize, int k) 
{
    long long maxHappiness = 0;
    heapify(happiness, happinessSize);
    for(int i = 0; i < k; i++)
    {
        int currHappiness = getFirst(happiness, &happinessSize) - i;
        maxHappiness += currHappiness < 0 ? 0 : currHappiness;
    }
    return maxHappiness;
}

int main()
{
    {
        int arrHappiness[] = {1, 2, 3};
        long long maxHappiness = maximumHappinessSum(arrHappiness, 3, 2);
        printf("Res: %lld\n", maxHappiness);
    }

    {
        int arrHappiness[] = {1, 1, 1,1};
        long long maxHappiness = maximumHappinessSum(arrHappiness, 4, 2);
        printf("Res: %lld\n", maxHappiness);
    }
}