#include<pthread.h>
#include<bits/stdc++.h>
#include<sys/stat.h>
#include<unistd.h>

using namespace std;


pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //Mutex for terminal ownership

void *func1(void *){
	while(true){
		pthread_mutex_lock(&mtx);
		int i = 0;
		while( i< 100000000)
		i++;
		printf("thread1\n");
		pthread_mutex_unlock(&mtx);
	}
}

void *func2(void *){
	while(true){
		pthread_mutex_lock(&mtx);
		int i = 0; 
		while( i< 100000000)
		i++;
		printf("thread2\n");
		pthread_mutex_unlock(&mtx);
	}
}

int main(){
	pthread_t tid[2];
	
	int x = 1, y = 2;
	
	pthread_create( &tid[0], NULL, func1, NULL);
	pthread_create( &tid[1], NULL, func2, NULL);
	
	for(int i = 0; i < 2; i++){
		pthread_join(tid[i], NULL);
	}
}
