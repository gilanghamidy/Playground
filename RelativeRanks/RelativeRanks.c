#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char** findRelativeRanks(int* score, int scoreSize, int* returnSize);


void mergeSortASM(int* score, uint16_t* indexRef, int begin, int end);

void mergeSort(int* score, uint16_t* indexRef, int begin, int end)
{
    if(begin == end)
        return;

    int mid = (end - begin) / 2;
    mergeSort(score, indexRef, begin, begin + mid);
    mergeSort(score, indexRef, begin + mid + 1, end);

    uint16_t temp[end - begin + 1];
    memset(&temp, 0, (end - begin + 1) * 2);
    for(int i = begin, j = begin + mid + 1, k = 0; k < end - begin + 1; k++)
    {
        if(i <= begin + mid && (j > end || score[indexRef[i]] <= score[indexRef[j]]))
            temp[k] = indexRef[i++];
        else
            temp[k] = indexRef[j++];
    }
    for(int i = 0; i < (end - begin + 1); i++)
        indexRef[begin + i] = temp[i];
}

char* stringRank(int rank)
{
    
    switch (rank) {
    case 1:
        return strdup("Gold Medal");    
    case 2:
        return strdup("Silver Medal");
    case 3:
        return strdup("Bronze Medal");
    default:
        {
            int len = snprintf(NULL, 0, "%d", rank);
            char* buf = malloc(len + 1);
            snprintf(buf, len + 1, "%d", rank);
            return buf;
        }
    }
}

char** findRelativeRanksC(int* score, int scoreSize, int* returnSize)
{
    uint16_t indexRef[scoreSize];
    for(int i = 0; i < scoreSize; i++)
        indexRef[i] = i;

    char** retArr = (char**)malloc(sizeof(char*) * scoreSize);
    *returnSize = scoreSize;

    mergeSortASM(score, indexRef, 0, scoreSize - 1);

    uint16_t rankTemp[scoreSize];

    for(int i = 0; i < scoreSize; i++)
        rankTemp[indexRef[scoreSize - i - 1]] = i + 1;
    
    for(int i = 0; i < scoreSize; i++)
        retArr[i] = stringRank(rankTemp[i]);
    
    return retArr;
}

int main()
{
    int scoreArr[] = {10, 3, 8, 9, 4};
    uint16_t scoreIdx[] = {0, 1, 2, 3, 4};

    uint16_t scoreIdx2[] = {0, 1, 2, 3, 4};

    int retSize = 0;
    char** res = findRelativeRanksC(scoreArr, 5, &retSize);

    char** res2 = findRelativeRanks(scoreArr, 5, &retSize);

}
