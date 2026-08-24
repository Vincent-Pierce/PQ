#include "../include/Priority Queue.h"


int main(char* argv[], int argc) {

	PriorityQueue* pq = new PriorityQueue();
	Student* s1		  = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student* s2		  = new Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student* s3		  = new Student("Charlie", 0, "charlie@gmail.com", 4.0, 100);

	pq->insert(s1);
	pq->insert(s2);
	pq->insert(s3);

	pq->peek();
	pq->pop();
	pq->peek();
	pq->pop();
	pq->peek();
	printf("done\n");

}