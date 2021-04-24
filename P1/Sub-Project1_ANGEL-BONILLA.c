#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define array_size 9
//our global unsorted array to be sorted
int unsorted_arr[array_size] = {1, 7, 35, 5, 1 ,4, 7, 9, 24}; 
int sorted_arr[array_size]; //where sorted digits will be stored

struct countingSort_params{
	int start;//starting index
	int end;//end index
};

struct countingSort_params thread_params[3];//array of params to prevent change to start/end
					     //before thread is finished making local copy
					     
//This function takes in a void pointer to a struct containing the start and end index of an array
//The function then uses those indexes to dictate what part of the array we will apply
//counting sort on
void * countingSort(void * params){
	//creates a local copy of the start/end variables in our params
	struct countingSort_params *_params = params;
	int start = _params->start;
	int end = _params->end;
	
	int range = 100;//highest digit that can be sorted
	
	int count[range + 1];//create an array to count each integer
	memset(count, 0, sizeof(count));//set each count to 0
	
	for(int i = 0; unsorted_arr[i]; i++)//count each integer
		count[unsorted_arr[i]]++;
					
	for(int i = 1; i <= range; i++)//count[i] has the actual position of the integer
		count[i] += count[i - 1];//in the sorted array
		
	for(int i = 0; unsorted_arr[i]; i++){
		sorted_arr[count[unsorted_arr[i]] - 1] = unsorted_arr[i];//place the integer
		count[unsorted_arr[i]]--;// in the respective spot in the sorted array
	}
	
	pthread_exit (NULL);
}
//This function creates 3 sorting threads, divides the array into 3 paritions, and then
// calls a countingSort function for each partition using a sorting thread
void multithread_sort(){
	pthread_t sorting_thread[3];//our 3 sorting threads
	int array_partition_size = array_size/3;//divides size of array by 3 to determine
						// how much space each thread will work on
	int partition_position = 0;//our partition starts at 0
	
	for(int i = 0; i < 3; i++){
		struct countingSort_params params = thread_params[i];//access one version of param
		params.start = partition_position;//assign our starting position
		params.end = partition_position + array_partition_size;//assign end position
		partition_position += array_partition_size;//move start position up for our next loop
		//apply counting sort using sorting thread and pass param
		pthread_create(&sorting_thread[i],NULL,countingSort,&params);
	}
	for(int i = 0; i < 3; i++){
		pthread_join(sorting_thread[i],NULL);//join our threads
	}
}

int main(){

	printf("List of integers to be sorted:\n");
	for(int i = 0; i < array_size; i++)
		printf("%d ", unsorted_arr[i]);
		
	multithread_sort();

	printf("\nList of integers after multithreaded sort:\n");
	for(int i = 0; i < array_size; i++)
		printf("%d ", sorted_arr[i]);
      
	printf("\n");

}
