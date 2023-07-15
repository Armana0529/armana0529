#include <stdio.h>

void bubbleSort(int arr1[], int number, int swaps[]){
    int i, j, temp;


    for (i = 0; i < number ; i++){
        for(j = 0; j< number - i - 1; j++){
            if (arr1[j]> arr1[j + 1]){
                temp = arr1[j];
                arr1[j] = arr1[j +1];
                arr1[j + 1] = temp;

                swaps[i]++;
                
            }
        }
   
    }
}


int main() {
    int arr1[]= {97,16,45,63,13,22,7,58,72};
    int number = sizeof(arr1) / sizeof(arr1[0]);
    int swaps[number];

    for (int i = 0; i < number; i++){
        swaps[i] = 0;
    }

    bubbleSort(arr1, number, swaps);

    for (int i = 0; i < number; i++){
        printf("%d ", swaps[i]);
    }
    return 0;
}

