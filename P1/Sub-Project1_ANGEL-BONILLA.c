#include <pthread.h>

int main(){

    int arr[9] = {1, 4, 5, 6, 2, 3, 7, 9, 8};

    printf("List of integers to be sorted:\n");
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
        printf("%d ", arr[i]);

    printf("\nList of integers after multithreaded sort:\n");
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
        printf("%d ", arr[i]);

}

void multithread_sort(int arr[]){

}

void quickSort(){

}
