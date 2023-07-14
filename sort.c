#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TABLE_SIZE 10000

int extraMemoryAllocated;

typedef struct HashTable
{
	int key;
	int value;
}HashTable;

void swap(int arr[], int i, int j)
{
	int temp =  arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2 *i +1;
	int right = 2 *i +2;
	
	if(left< n && arr[left]> arr[largest])
	largest = left;

	if(right < n && arr[right] > arr[largest])
	largest = right;

	if (largest != i)
	{
		swap(arr, i, largest);
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n, hashTable[])
{
	extraMemoryAllocated = sizeof(int) * n;

	for (int i = n/2 -1; i>= 0;i--)
	{
		heapify(arr, n, i);
	}
	for (int i = n -1; i>0; i--)
	{
		swap(arr, 0, i);
		heapify(arr, i, 0);
	}

}

void merge(int pData[], int l, int m, int r, HashTable hashTable[], int temp[])
{
	extraMemoryAllocated += sizeof(int) * (r - l + 1);

	int i, j, k;
	int n1 = m - l +1;
	int n2 = r - m;

	for (i = 0; i < n1; i++)
	{
		temp[i]=pData[l + i];
	}
	for (j = 0; j < n2; j++)
	{
		temp[n1 + j] = pData[m + 1 +j];
	}

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if(temp[i] <= temp[n1+j])
		{
			pData[k] = temp [i];
			i++;
		}
		else
		{
			pData[k] = temp[n1 + j];
			j++;
		}
		k++;
	} 
	while (i < n1)
	{
		pData[k] = temp[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		pData[k] = temp[n1+j];
		j++;
		k++;
	}
}

void mergeSort(int pData[], int l, int r, HashTable hashTable[], int temp[])
{
	if(l < r)
	{
		int m = l + (r-l)/2;

		mergeSort(pData, l, m, hashTable, temp);
		mergeSort(pData, m +1, r, hashTable, temp);
		merge(pData, l, m, r, hashTable, temp);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz, HashTable hashTable[])
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		int hashKey = pData[i] % TABLE_SIZE;
		printf("%d ",hashTable[hashKey].value);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		int hashkey = pData[i] % TABLE_SIZE;
		printf("%d ",hashTable[hashkey].value);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

		HashTable hashTable[TABLE_SIZE];
		for(int j = 0; j < TABLE_SIZE; ++j)
		{
			hashTable[j].key = -1;
			hashTable[j].value = -1;
		}
		
		for(int j = 0; j < dataSz; ++j)
		{
			int hashkey = pDataSrc[j] % TABLE_SIZE;
			hashTable[hashkey].key = pDataSrc[j];
			hashTable[hashkey].value = j;
		}

		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz, hashTable);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz, hashTable);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1, hashTable, pDataSrc);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz, hashTable);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}