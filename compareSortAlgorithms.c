#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//arr = {1,2,3,4,5,6,7,8,9,10,11}; size 9

//mid = 4;
//n1 = 4 - 0 + 1 = 5
//n2 = 9 - 4 = 5
int extraMemoryAllocated;


void merge(int arr[], int l, int mid, int r)
{
    int a = 0, b = 0;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int left[n1],right[n2];

    for (int i = 0; i < n1;i++){
        left[i] = arr[l + i];
    }

    for (int j = 0; j < n2;j++){
        right[j] = arr[mid + 1 + j];
    }

    int c = l;
    while(a < n1 && b < n2){
        if(left[a] <= right[b]){
            arr[c] = left[a];
            a++;
        }else{
            arr[c] = right[b];
            b++;
        }
        c++;
    }

    while(a < n1){
        arr[c] = left[a];
        a++;
        c++;
    }
    while(b < n2){
        arr[c] = right[b];
        b++;
        c++;
    }
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l < r){
        int mid = l + (r - l) / 2;


        mergeSort(pData,l,mid);
        mergeSort(pData,mid+1,r);

        merge(pData,l,mid,r);
    }

}



// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    for (int step = 1; step < n; step++) {
        int key = pData[step];
        int j = step - 1;
        while (key < pData[j] && j >= 0) {
           pData[j + 1] = pData[j];
            --j;
        }
        pData[j + 1] = key;
    }
}

void swap(int *x,int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    // loop to access each array element
    for (int step = 0; step < n - 1; step++) {

        // loop to compare array elements
        for (int i = 0; i < n - step - 1; i++) {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (pData[i] > pData[i + 1]) {

                // swapping occurs if elements
                // are not in the intended order

                swap(&pData[i],&pData[i+1]);

            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    for (int step = 0; step < n - 1; step++) {
        int min = step;
        for (int i = step + 1; i < n; i++) {


            if (pData[i] < pData[min])
                min = i;
        }
        swap(&pData[min], &pData[step]);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}
/*
void printArr(int arr[],int n){

    for (int i = 0; i < n;i++){
        printf("%d\n",arr[i]);
    }
}
*/
int main(void)
{

    /*
    int arr[] = {24,15,4,9,20,57,19,1102,4753,234,12,456,453,};

    int size = sizeof(arr) / sizeof (arr[0]);
    mergeSort(arr,0,size-1);
    //selectionSort(arr,12);
    //bubbleSort(arr,12);
    //insertionSort(arr,12);

    printArr(arr,12);
*/


	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"C:\\Users\\blueg\\CLionProjects\\assignment_4\\compareSortingAlgorithms\\input1.txt", "C:\\Users\\blueg\\CLionProjects\\assignment_4\\compareSortingAlgorithms\\input2.txt", "C:\\Users\\blueg\\CLionProjects\\assignment_4\\compareSortingAlgorithms\\input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}

}