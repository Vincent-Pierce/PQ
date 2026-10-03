#include <gtest/gtest.h>
#include <memory>
#include "Priority Queue.h"
#include "Strategy/MinStrategy.h"

TEST(Student, Constructor)
{
    Student s1 = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    EXPECT_EQ("Amy", s1.getName());
    EXPECT_EQ(0, s1.getRedID());
    EXPECT_EQ("amy@gmail.com", s1.getEmail());
    EXPECT_EQ(4.0, s1.getGPA());
    EXPECT_EQ(10, s1.getUnitsTaken());
}

TEST(Student, ConstructorNegativeValues)
{
    EXPECT_THROW({ Student s1("Amy", 0, "amy@gmail.com", -1.0f, -1); }, std::invalid_argument);
}

TEST(Student, ConstructorExceedingValues)
{
    EXPECT_THROW({ Student s1("Amy", 0, "amy@gmail.com", 5.0f, 151); }, std::invalid_argument);
}

TEST(PriorityQueue, front)
{
    Student s1 = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(s1);

    EXPECT_EQ(pq.front()->getName(), "Amy");
}

TEST(PriorityQueue, enqueue)
{
    Student s1       = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student s2		  = Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student s3		  = Student("Charlie", 0, "charlie@gmail.com", 4.0, 100); //highest prio
    PriorityQueue pq = PriorityQueue();

    pq.enqueue(s1);
    pq.enqueue(s2);
    pq.enqueue(s3);

    EXPECT_EQ(pq.front()->getName(), "Charlie");
}

TEST(PriorityQueue, min_strategy_enqueue_and_dequeue)
{
    auto minStrategy = std::make_shared<MinStrategy<Student>>();
    PriorityQueue minQueue(minStrategy);
    PriorityQueue maxQueue;
    Student lowPriority("Bob", 0, "bob@gmail.com", 3.0f, 0.0f);
    Student middlePriority("Amy", 0, "amy@gmail.com", 4.0f, 10.0f);
    Student highPriority("Charlie", 0, "charlie@gmail.com", 4.0f, 100.0f);

    minQueue.enqueue(middlePriority);
    minQueue.enqueue(highPriority);
    minQueue.enqueue(lowPriority);
    maxQueue.enqueue(middlePriority);
    maxQueue.enqueue(highPriority);
    maxQueue.enqueue(lowPriority);

    ASSERT_NE(minQueue.front(), nullptr);
    EXPECT_EQ(minQueue.front()->getName(), "Bob");
    ASSERT_NE(maxQueue.front(), nullptr);
    EXPECT_EQ(maxQueue.front()->getName(), "Charlie");

    EXPECT_TRUE(minQueue.dequeue());
    ASSERT_NE(minQueue.front(), nullptr);
    EXPECT_EQ(minQueue.front()->getName(), "Amy");
    EXPECT_EQ(maxQueue.front()->getName(), "Charlie");
    EXPECT_TRUE(minQueue.dequeue());
    ASSERT_NE(minQueue.front(), nullptr);
    EXPECT_EQ(minQueue.front()->getName(), "Charlie");
}

TEST(PriorityQueue, dequeue_one)
{
    Student s1       = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(s1);

    
    EXPECT_EQ(pq.dequeue(), true);
    EXPECT_EQ(pq.front(), nullptr);
}

TEST(PriorityQueue, print_uses_max_strategy)
{
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(Student("Amy", 0, "amy@gmail.com", 4.0f, 10.0f));
    pq.enqueue(Student("Bob", 0, "bob@gmail.com", 3.0f, 0.0f));
    pq.enqueue(Student("Charlie", 0, "charlie@gmail.com", 4.0f, 100.0f));
    pq.enqueue(Student("David", 0, "david@gmail.com", 4.0f, 90.0f));

    testing::internal::CaptureStdout();
    pq.print();
    const std::string output = testing::internal::GetCapturedStdout();

    EXPECT_LT(output.find("Name:\tCharlie"), output.find("Name:\tDavid"));
    EXPECT_LT(output.find("Name:\tDavid"), output.find("Name:\tAmy"));
    EXPECT_LT(output.find("Name:\tAmy"), output.find("Name:\tBob"));
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getName(), "Charlie");
}

TEST(PriorityQueue, print_uses_min_strategy)
{
    auto minStrategy = std::make_shared<MinStrategy<Student>>();
    PriorityQueue pq(minStrategy);
    pq.enqueue(Student("Amy", 0, "amy@gmail.com", 4.0f, 10.0f));
    pq.enqueue(Student("Bob", 0, "bob@gmail.com", 3.0f, 0.0f));
    pq.enqueue(Student("Charlie", 0, "charlie@gmail.com", 4.0f, 100.0f));
    pq.enqueue(Student("David", 0, "david@gmail.com", 4.0f, 90.0f));

    testing::internal::CaptureStdout();
    pq.print();
    const std::string output = testing::internal::GetCapturedStdout();

    EXPECT_LT(output.find("Name:\tBob"), output.find("Name:\tAmy"));
    EXPECT_LT(output.find("Name:\tAmy"), output.find("Name:\tDavid"));
    EXPECT_LT(output.find("Name:\tDavid"), output.find("Name:\tCharlie"));
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getName(), "Bob");
}

TEST(PriorityQueue, tie_breaker)
{
    Student s1  = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student s2  = Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student s3  = Student("Charlie", 0, "charlie@gmail.com", 4.0, 100); //highest prio
    Student s4  = Student("David", 0, "david@gmail.com", 4.0, 100); //same prio as Charlie
    
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(s1);
    pq.enqueue(s2);
    pq.enqueue(s3);
    pq.enqueue(s4);

    EXPECT_EQ(pq.front()->getName(), "Charlie"); 
    EXPECT_EQ(pq.dequeue(), true);
    EXPECT_EQ(pq.front()->getName(), "David"); 
    EXPECT_EQ(pq.dequeue(), true);
    EXPECT_EQ(pq.front()->getName(), "Amy"); 
    EXPECT_EQ(pq.dequeue(), true);
    EXPECT_EQ(pq.front()->getName(), "Bob"); 
    EXPECT_EQ(pq.dequeue(), true);
    EXPECT_EQ(pq.front(), nullptr);
}

TEST(PriorityQueue, dequeue_empty)
{
    PriorityQueue pq = PriorityQueue();
    EXPECT_EQ(pq.dequeue(), false);
}

TEST(PriorityQueue, front_empty)
{
    PriorityQueue pq = PriorityQueue();
    EXPECT_EQ(pq.front(), nullptr);
}

TEST(PriorityQueue, StressTest)
{

    PriorityQueue pq = PriorityQueue();
    for (int i = 0; i < 10000; ++i)
    {
        Student s = Student("Student" + std::to_string(i), i, "student" + std::to_string(i) + "@gmail.com", static_cast<float>(i % 5), i % 150);
        pq.enqueue(s);
    }

    // Drain the priority queue and verify order
    Student const* current = pq.front();
    while((pq.dequeue()))
    {
        Student const* next = pq.front();
        if (next)
        {
            EXPECT_GE(current->computePriority(), next->computePriority());
        }
        current = next;
    }
}