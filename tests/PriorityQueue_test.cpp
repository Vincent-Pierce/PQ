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

TEST(Student, get)
{
    EXPECT_EQ(5 - 3, 2);
}