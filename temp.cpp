#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

typedef struct {
    int sum;
    int start;
    int end;
} Node;

int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void *cal_sum (void *args) {

    Node *node = ((Node *) args);
    for(int i = node->start; i < node->end; i++) {
        node->sum += a[i];
    }
    cout<<"Node : "<<node->sum;
    pthread_exit(&(node->sum));
}

int main () {

    int p = 4;
    int n = 10;
    int steps = n/p;
    pthread_t sum_threads[p];
    Node nodes[p];

    for (int i = 0; i < p; i++) {
        nodes[i].sum = 0;
        nodes[i].start = i*steps;
        if(i == p-1) {
            nodes[i].end = n;
        } else {
            nodes[i].end = (i+1)*steps;
        }
        pthread_create (&sum_threads[i], NULL, cal_sum, (void *) &nodes[i]);
    }
    Node** sum[p];
    for (int i = 0; i < p; i++) {
        pthread_join (sum_threads[i], NULL);
    }
    Node *x = &nodes[0];
    *sum[0] = x;
    int tot_sum = 0;
    // for(int i = 0; i < p; i++) {
    //     tot_sum += *(int *)*sum[0];
    // }
    cout<<"Total sum = "<<tot_sum<<endl;
    return 0;
}