#include <gtest/gtest.h>
#include <memory>
#include "Command/EnqueueCommand.h"
#include "Command/DequeueCommand.h"
#include "Priority Queue.h"
#include "Strategy/MinStrategy.h"
#include "Iterator/PriorityQueueIterator.h"

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

TEST(PriorityQueue, toArray)
{
    Student s1 = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    Student s2 = Student("Bob", 0, "bob@gmail.com", 3.0, 0);
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(s1);
    pq.enqueue(s2);

    EXPECT_THROW(pq.toArray(), std::logic_error);
}

TEST(PriorityQueue, toString)
{
    Student s1 = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
    Student s2 = Student("Bob", 0, "bob@gmail.com", 3.0, 0);
    PriorityQueue pq = PriorityQueue();
    pq.enqueue(s1);
    pq.enqueue(s2);

    EXPECT_THROW(pq.toString(), std::logic_error);
}

TEST(EnqueueCommand, undoRemovesEnqueuedStudentWithoutRemovingFront)
{
    PriorityQueue pq;
    Student highPriority("Charlie", 1, "charlie@gmail.com", 4.0f, 100.0f);
    Student lowPriority("Bob", 2, "bob@gmail.com", 3.0f, 0.0f);
    pq.enqueue(highPriority);

    EnqueueCommand command(pq, lowPriority);
    command.execute();
    ASSERT_EQ(pq.size(), 2);
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getName(), "Charlie");

    command.undo();

    ASSERT_EQ(pq.size(), 1);
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getName(), "Charlie");
}

TEST(PriorityQueue, removeRestoresHeapAfterRemovingNonRootStudent)
{
    PriorityQueue pq;
    Student root("Root", 1, "root@example.com", 0.0f, 150.0f);
    Student left("Left", 2, "left@example.com", 0.0f, 75.0f);
    Student right("Right", 3, "right@example.com", 0.0f, 135.0f);
    Student removed("Removed", 4, "removed@example.com", 0.0f, 30.0f);
    Student last("Last", 5, "last@example.com", 0.0f, 127.5f);
    Student nextRight("NextRight", 6, "next-right@example.com", 0.0f, 120.0f);
    Student lastRight("LastRight", 7, "last-right@example.com", 0.0f, 130.0f);

    for (const Student& student : {root, left, right, removed, last, nextRight, lastRight})
        pq.enqueue(student);

    ASSERT_TRUE(pq.remove(removed));
    EXPECT_FALSE(pq.remove(removed));

    const uint64_t expectedOrder[] = {1, 3, 7, 5, 6, 2};
    for (uint64_t redId : expectedOrder)
    {
        ASSERT_NE(pq.front(), nullptr);
        EXPECT_EQ(pq.front()->getRedID(), redId);
        EXPECT_TRUE(pq.dequeue());
    }
    EXPECT_TRUE(pq.isEmpty());
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

TEST(PriorityQueue, dequeue)
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

TEST(PriorityQueue, EnqueueCommand)
{
    // Max strategy means highest priority element is at the front
    PriorityQueue pq = PriorityQueue(); 
    Student s1  = Student("Amy", 0, "amy@gmail.com", 4.0, 10);
	Student s2  = Student("Bob", 0, "bob@gmail.com", 3.0, 0);
	Student s3  = Student("Charlie", 0, "charlie@gmail.com", 4.0, 100); //highest prio
    Student s4  = Student("David", 0, "david@gmail.com", 4.0, 150); //same prio as Charlie
    EnqueueCommand cmd1(pq, s2);
    EnqueueCommand cmd2(pq, s1);
    EnqueueCommand cmd3(pq, s3);
    EnqueueCommand cmd4(pq, s4);

    cmd1.execute();
    EXPECT_EQ(pq.front()->getName(), "Bob"); 
    cmd2.execute();
    EXPECT_EQ(pq.front()->getName(), "Amy"); 
    cmd3.execute();
    EXPECT_EQ(pq.front()->getName(), "Charlie"); 
    cmd4.execute();
    EXPECT_EQ(pq.front()->getName(), "David"); 
    cmd4.undo();
    EXPECT_EQ(pq.front()->getName(), "Charlie"); 
    cmd3.undo();
    EXPECT_EQ(pq.front()->getName(), "Amy"); 
    cmd2.undo();
    EXPECT_EQ(pq.front()->getName(), "Bob"); 
    cmd1.undo();
    EXPECT_EQ(pq.front(), nullptr);
}

TEST(PriorityQueue, DequeueCommand)
{
    PriorityQueue pq = PriorityQueue();
    DequeueCommand cmd1(pq);
    DequeueCommand cmd2(pq);
    DequeueCommand cmd3(pq);
    DequeueCommand cmd4(pq);
    Student s1 = Student("Test", 0, "test@gmail.com", 4.0, 100);
    Student s2 = Student("Test", 0, "test@gmail.com", 4.0, 100);
    Student s3 = Student("Test", 0, "test@gmail.com", 4.0, 100);
    Student s4 = Student("Test", 0, "test@gmail.com", 4.0, 100);
    EXPECT_EQ(cmd1.execute(), false);
    pq.enqueue(s1);
    pq.enqueue(s2);
    pq.enqueue(s3);
    pq.enqueue(s4);
    EXPECT_EQ(cmd1.execute(), true);
    EXPECT_EQ(cmd1.execute(), false);
    EXPECT_EQ(cmd2.execute(), true);
    EXPECT_EQ(cmd3.execute(), true);
    EXPECT_EQ(cmd4.execute(), true);
    EXPECT_EQ(cmd4.execute(), false);
}

TEST(PriorityQueue, DequeueCommandUndoRestoresRemovedStudentsInOrder)
{
    PriorityQueue pq;
    Student lowPriority("Low", 1, "low@example.com", 3.0f, 0.0f);
    Student middlePriority("Middle", 2, "middle@example.com", 3.5f, 50.0f);
    Student highPriority("High", 3, "high@example.com", 4.0f, 100.0f);
    pq.enqueue(lowPriority);
    pq.enqueue(middlePriority);
    pq.enqueue(highPriority);

    DequeueCommand first(pq);
    DequeueCommand second(pq);

    ASSERT_TRUE(first.execute());
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getRedID(), middlePriority.getRedID());
    ASSERT_TRUE(second.execute());
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getRedID(), lowPriority.getRedID());
    EXPECT_FALSE(second.execute());

    EXPECT_TRUE(second.undo());
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getRedID(), middlePriority.getRedID());
    EXPECT_FALSE(second.undo());
    EXPECT_TRUE(first.undo());
    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.front()->getRedID(), highPriority.getRedID());
    EXPECT_EQ(pq.size(), 3);
    EXPECT_FALSE(first.undo());
}

TEST(PriorityQueue, PriorityQueueIteratorTest)
{
    PriorityQueue pq;
    Student lowPriority("Bob", 1, "bob@example.com", 3.0f, 0.0f);
    Student middlePriority("Amy", 2, "amy@example.com", 4.0f, 10.0f);
    Student highPriority("Charlie", 3, "charlie@example.com", 4.0f, 100.0f);
    pq.enqueue(lowPriority);
    pq.enqueue(middlePriority);
    pq.enqueue(highPriority);

    PriorityQueueIterator it(pq);
    const Student* current = it.first();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getRedID(), highPriority.getRedID());
    EXPECT_EQ(it.current()->getRedID(), highPriority.getRedID());

    current = it.next();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getRedID(), middlePriority.getRedID());
    current = it.next();
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->getRedID(), lowPriority.getRedID());
    EXPECT_EQ(it.next(), nullptr);

    ASSERT_NE(pq.front(), nullptr);
    EXPECT_EQ(pq.size(), 3);
    EXPECT_EQ(pq.front()->getRedID(), highPriority.getRedID());
}

TEST(PriorityQueue, PriorityQueueIteratorEmptyTest)
{
    PriorityQueue pq;
    PriorityQueueIterator it(pq);
    EXPECT_EQ(it.first(), nullptr);
    EXPECT_EQ(it.current(), nullptr);
    EXPECT_EQ(it.next(), nullptr);
}

TEST(PriorityQueue, PriorityQueueIteratorIncrementTest)
{
    auto minStrategy = std::make_shared<MinStrategy<Student>>();
    PriorityQueue pq(minStrategy);
    Student highPriority("Charlie", 1, "charlie@example.com", 4.0f, 100.0f);
    Student lowPriority("Bob", 2, "bob@example.com", 3.0f, 0.0f);
    Student middlePriority("Amy", 3, "amy@example.com", 4.0f, 10.0f);
    pq.enqueue(highPriority);
    pq.enqueue(lowPriority);
    pq.enqueue(middlePriority);

    PriorityQueueIterator iterator(pq);
    const uint64_t expectedOrder[] = {
        lowPriority.getRedID(),
        middlePriority.getRedID(),
        highPriority.getRedID()
    };
    int index = 0;

    for (auto it = iterator; it != nullptr; it++)
    {
        ASSERT_LT(index, 3);
        ASSERT_NE(it.current(), nullptr);
        EXPECT_EQ(it.current()->getRedID(), expectedOrder[index]);
        ++index;
    }

    EXPECT_EQ(index, 3);
}
