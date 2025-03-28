#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define SIZE 1000

char shared_array[SIZE];
pthread_mutex_t mtx;
int xindex ;

void* fill_array(void* arg) {
	puts("hiero");
	pthread_mutex_lock(&mtx);
	int main_i = xindex;
	pthread_mutex_unlock(&mtx);
	puts("xxxx");
	printf("%d\n", main_i);
	while (main_i < SIZE) {
		shared_array[main_i] = 'B';
		pthread_mutex_lock(&mtx);
		++xindex;
		main_i = xindex;
		pthread_mutex_unlock(&mtx);
	}
	return (NULL);
}

int main() {
	pthread_t thread;

	xindex = 0;
	// Initialize the array and mutexes
	memset(shared_array, '-', SIZE);
	pthread_mutex_init(&mtx, NULL);

	// Create one additional thread
	pthread_create(&thread, NULL, fill_array, NULL);
usleep(1);
	// Main thread also loops through the array
	pthread_mutex_lock(&mtx);
	int main_i = xindex;
	pthread_mutex_unlock(&mtx);
	while (main_i < SIZE) {
		shared_array[main_i] = 'A';
		pthread_mutex_lock(&mtx);
		++xindex;
		main_i = xindex;
		pthread_mutex_unlock(&mtx);
	}

	pthread_join(thread, NULL);

	pthread_mutex_destroy(&mtx);
	printf("Resulting array: %s\n", shared_array);
	return 0;
}