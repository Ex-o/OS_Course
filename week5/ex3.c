#include <stdio.h>
#include <pthread.h>
#include <time.h>

const int MAX_CNT = 2;
int count = 0;
int buff[MAX_CNT];
int counter = 0;


pthread_mutex_t mutx;
pthread_cond_t consumerCondition;
pthread_cond_t producerCondition;
time_t start;

void * producer(void *){
	while (1) {
		//printf("Producer: %d\n", count);

		pthread_mutex_lock(&mutx);

		if (count == MAX_CNT){
			pthread_cond_wait(&producerCondition, &mutx);
		}

		buff[count] = 1;
		count++;
		time_t end = time(0);
		double seconds = (double)(end - start);

		if(seconds > counter * 60){
			printf("%d\n", counter);
			counter++;
		}

		if (count == 1){
			pthread_cond_signal(&consumerCondition);
			pthread_mutex_unlock(&mutx);
		}
	}
	pthread_exit(0);
}

void * consumer(void *){
	while (1) {
		//printf("Consumer: %d\n", count);

		pthread_mutex_lock(&mutx);
		if (count == 0){
			pthread_cond_wait(&consumerCondition, &mutx);
		}

		buff[count] = 0;
		count--;

		if (count == MAX_CNT - 1){
			pthread_cond_signal(&producerCondition);
			pthread_mutex_unlock(&mutx);
		}
	}
	pthread_exit(0);

}


int main(int argc, char const *argv[]){
	start = time(NULL);
	pthread_t pro, con;

	pthread_mutex_init(&mutx, 0);

	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);

	pthread_cond_init(&consumerCondition, 0);
	pthread_cond_init(&producerCondition, 0);

	pthread_join(pro, 0);
	pthread_join(con, 0);

	pthread_cond_destroy(&consumerCondition);
	pthread_cond_destroy(&producerCondition);

	pthread_mutex_destroy(&mutx);

	return 0;
}