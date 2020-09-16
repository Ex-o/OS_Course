#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * print_text(void * threadId){
    printf(" %d\n", (int) threadId);
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    const int MAX_THREADS = 5;
    pthread_t threads[MAX_THREADS];
    
    for(int i = 0; i < MAX_THREADS; i++) {
        printf("Thread [%d] created [MAIN]\n", i);
        int result = pthread_create(&threads[i], NULL, print_text, (void *)i);
        
        if (result != 0) {
            printf("Thread creation failed %d\n", result);
            exit(NULL);
        }
        
        //To fix order of execution:
        pthread_join(threads[i], NULL); 
    }
    return 0;
}