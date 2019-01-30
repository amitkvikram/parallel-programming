#include<bits/stdc++.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdlib.h>

#ifndef O_CREAT
# define O_CREAT 0100
#endif

using namespace std;

/*	sem_trywait:
 * Return -1 if semaphore is locked
 * otherwise locks the semaphore
*/

char sem_name[] = "/sem_file";

int main(){
	//Open semaphore with initial value set to 1.
	sem_t *sem_mtx = sem_open(sem_name, O_CREAT, 0666, 1);
	
	int status = sem_trywait(sem_mtx);
	if(status == -1){
		cout<<"Can not lock semaphore"<<endl;
	}
	else{
		cout<<"Successfully locked semaphore"<<endl;
	}
	
	return 0;	
}
	
