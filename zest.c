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

// int main() {
// 	pthread_t thread;

// 	xindex = 0;
// 	// Initialize the array and mutexes
// 	memset(shared_array, '-', SIZE);
// 	pthread_mutex_init(&mtx, NULL);

// 	// Create one additional thread
// 	pthread_create(&thread, NULL, fill_array, NULL);
// usleep(1);
// 	// Main thread also loops through the array
// 	pthread_mutex_lock(&mtx);
// 	int main_i = xindex;
// 	pthread_mutex_unlock(&mtx);
// 	while (main_i < SIZE) {
// 		shared_array[main_i] = 'A';
// 		pthread_mutex_lock(&mtx);
// 		++xindex;
// 		main_i = xindex;
// 		pthread_mutex_unlock(&mtx);
// 	}

// 	pthread_join(thread, NULL);

// 	pthread_mutex_destroy(&mtx);
// 	printf("Resulting array: %s\n", shared_array);
// 	return 0;
// }
// void	swap_values(void *a, void *b, size_t size)
// {
// 	unsigned char	*p1;
// 	unsigned char	*p2;
// 	unsigned char	tmp;

// 	p1 = (unsigned char *)a;
// 	p2 = (unsigned char *)b;
// 	while (size != 0)
// 	{
// 		tmp = *p1;
// 		*p1 = *p2;
// 		*p2 = tmp;

// 		p1++; // Move to the next byte
// 		p2++; // Move to the next byte
// 		size--;
// 	}
// }

/**
 * @param[in] a Pointer to the first value to swap
 * @param[in] b Pointer to the second value to swap
 * @param[in] size Size of the data type in bytes, e.g. sizeof(int)
 */
void	swap_values(void *a, void *b, size_t size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	tmp;

	p1 = (unsigned char *)a;
	p2 = (unsigned char *)b;
	while (size != 0)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		++p1;
		++p2;
		--size;
	}
}

int main(void)
{
	int a = 5;
	int b = 10;

	swap_values(&a, &b, sizeof(int));
	printf("%d\t%d\n", a, b);
	return (0);
}