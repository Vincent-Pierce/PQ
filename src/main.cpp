#include "Priority Queue.h"

int main(int argc, char* argv[])
{

	PriorityQueue pq;
	Student s1("Amy", 0, "amy@gmail.com", 4.0f, 10);
	Student s2("Bob", 0, "bob@gmail.com", 3.0f, 0);
	Student s3("Charlie", 0, "charlie@gmail.com", 4.0f, 100);

	pq.insert(s1);
	pq.insert(s2);
	pq.insert(s3);

	pq.peek();
	pq.pop();
	pq.peek();
	pq.pop();
	pq.peek();
	printf("done\n");

	return 0;
}