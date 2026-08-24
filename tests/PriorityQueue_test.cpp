#include <gtest/gtest.h>

#include "Priority Queue.h"

TEST(Student, Constructor)
{
    Student* s1 = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    EXPECT_EQ("Amy", s1->getName());
    EXPECT_EQ(0, s1->getRedID());
    EXPECT_EQ("amy@gmail.com", s1->getEmail());
    EXPECT_EQ(4.0, s1->getGPA());
    EXPECT_EQ(10, s1->getUnitsTaken());
    EXPECT_FLOAT_EQ(8.2, s1->getPriority());
}

TEST(Student, ConstructorNegativeValues)
{
    Student* s1 = new Student("Amy", 0, "amy@gmail.com", -1.0, -1);
    EXPECT_EQ("Amy", s1->getName());
    EXPECT_EQ(0, s1->getRedID());
    EXPECT_EQ("amy@gmail.com", s1->getEmail());
    EXPECT_FLOAT_EQ(0.0, s1->getGPA());
    EXPECT_EQ(0, s1->getUnitsTaken());
    EXPECT_FLOAT_EQ(0.0, s1->getPriority());
}

TEST(Student, ConstructorExceedingValues)
{
    Student* s1 = new Student("Amy", 0, "amy@gmail.com", 5.0, 151);
    EXPECT_EQ("Amy", s1->getName());
    EXPECT_EQ(0, s1->getRedID());
    EXPECT_EQ("amy@gmail.com", s1->getEmail());
    EXPECT_EQ(4.0, s1->getGPA());
    EXPECT_EQ(150, s1->getUnitsTaken());
    EXPECT_FLOAT_EQ(106.2, s1->getPriority());
}

TEST(PriorityQueue, peek)
{
    Student* s1 = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    PriorityQueue* pq = new PriorityQueue();
    pq->insert(s1);

    EXPECT_EQ(pq->peek(), s1);
}

TEST(PriorityQueue, insert)
{
    Student* s1       = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student* s2		  = new Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student* s3		  = new Student("Charlie", 0, "charlie@gmail.com", 4.0, 100); //highest prio
    PriorityQueue* pq = new PriorityQueue();
    pq->insert(s1);
    pq->insert(s2);
    pq->insert(s3);

    EXPECT_EQ(pq->peek(), s3);
}

TEST(PriorityQueue, pop_one)
{
    Student* s1       = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    PriorityQueue* pq = new PriorityQueue();
    pq->insert(s1);

    
    EXPECT_EQ(pq->pop(), s1);
}

TEST(PriorityQueue, print)
{
    Student* s1       = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    Student* s2       = new Student("Bob", 0, "bob@gmail.com", 3.0, 0);
    Student* s3       = new Student("Charlie", 0, "charlie@gmail.com", 4.0, 100);
    Student* s4       = new Student("David", 0, "david@gmail.com", 4.0, 90);
    PriorityQueue* pq = new PriorityQueue();

    pq->insert(s1);
    pq->insert(s2);
    pq->insert(s3);
    pq->insert(s4);
    pq->print();
}
TEST(PriorityQueue, pop_reheapifies_root)
{
    Student* s1       = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    Student* s2       = new Student("Bob", 0, "bob@gmail.com", 3.0, 0);
    Student* s3       = new Student("Charlie", 0, "charlie@gmail.com", 4.0, 100);
    Student* s4       = new Student("David", 0, "david@gmail.com", 4.0, 90);
    PriorityQueue* pq = new PriorityQueue();

    pq->insert(s1);
    pq->insert(s2);
    pq->insert(s3);
    pq->insert(s4);

    EXPECT_EQ(pq->pop(), s3);
    EXPECT_EQ(pq->peek(), s4);
}

TEST(PriorityQueue, tie_breaker)
{
    Student* s1       = new Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student* s2		  = new Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student* s3		  = new Student("Charlie", 0, "charlie@gmail.com", 4.0, 100); //highest prio
    Student* s4       = new Student("David", 0, "david@gmail.com", 4.0, 100); //same prio as Charlie
    
    PriorityQueue* pq = new PriorityQueue();
    pq->insert(s1);
    pq->insert(s2);
    pq->insert(s3);
    pq->insert(s4);

    
    EXPECT_EQ(pq->pop(), s3);
    EXPECT_EQ(pq->pop(), s4);
    EXPECT_EQ(pq->pop(), s1);
    EXPECT_EQ(pq->pop(), s2);

}