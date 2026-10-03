#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: August 19th 2026
* Description	: Priority Queue Implementation
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/
#include "Student.h"
#include <vector>
#include <cstdio>

/* Class defs **********************************************************************************************/
#include "Queue.h"
class PriorityQueue : public Queue<Student>
{
public:
	PriorityQueue() = default;

	~PriorityQueue() = default;

	// Copy Constructor
	PriorityQueue Copy(PriorityQueue const& other)
	{
		pq = other.pq;
		return *this;
	}

	// Copy Assignment Operator
	PriorityQueue& operator=(PriorityQueue const& other)
	{
		if (this != &other)
		{
			pq = other.pq;
		}
		return *this;
	}

	// Adds student to priority queue. 
	void enqueue(const Student& student)
	{
		pq.push_back(student);			// insertion pushes to back of pq, then finds the correct position with bubble up
		int index = pq.size() - 1;
		bubbleUp(index);
	}

	// Removes highest priority student from queue. False if empty
	bool dequeue(void)
	{
		if (!pq.size())
			return false;

		bubbleDown();

		return true;
	}

	// Returns pointer to highest priority student, or nullptr if empty
	const Student* front(void) const
	{
		if(pq.empty())
			return nullptr;
		else
			return &pq[0];
	}

	bool isEmpty(void) const override 
	{
		return pq.empty();
	}

	size_t size(void) const override
	{
		return pq.size();
	}

	// Stub method to satisfy Collection interface. Not implemented for PriorityQueue.
	std::string toString(void) const override
	{
		throw std::logic_error("toString() not implemented for PriorityQueue");
	}

	// Stub method to satisfy Collection interface. Not implemented for PriorityQueue.
	std::vector<Student> toArray(void) const override
	{
		throw std::logic_error("toArray() not implemented for PriorityQueue");
	}


    // Print all students in PRIORITY ORDER by draining a copy of the heap
    void print(void) const
    {
        if (this->isEmpty())
            return;
 
        // Work on a copy so we don't disturb the real queue
		PriorityQueue copy = *this;

        // std::vector<Student> heap = pq;
 
        // Heapify (max-heap) from middle down to root
        for (int i = (copy.size() / 2) - 1; i >= 0; --i)
        {
            int index = i;
            while (true)
            {
                int leftIndex  = 2 * index + 1;
                int rightIndex = 2 * index + 2;
 
                if (leftIndex >= (copy.size()))
                    break;
 
                int largestIndex = index;
                if (leftIndex < (copy.size()) &&
                    getPriority(copy.pq[leftIndex]) > getPriority(copy.pq[largestIndex]))
                {
                    largestIndex = leftIndex;
                }
                if (rightIndex < (copy.size()) &&
                    getPriority(copy.pq[rightIndex]) > getPriority(copy.pq[largestIndex]))
                {
                    largestIndex = rightIndex;
                }
                if (largestIndex == index)
                    break;
 
                std::swap(copy.pq[index], copy.pq[largestIndex]);
                index = largestIndex;
            }
        }
 
        // Repeatedly remove max and print
        while (!copy.isEmpty())
        {
            const Student& front = copy.pq[0];
            std::printf("Name:\t%s\tRedID:\t%llu\tPriority:\t%f\n",
                front.getName().c_str(),
                static_cast<unsigned long long>(front.getRedID()),
                getPriority(front));
 
            copy.pq[0] = copy.pq.back();
            copy.pq.pop_back();
 
            int index = 0;
            while (true)
            {
                int leftIndex  = 2 * index + 1;
                int rightIndex = 2 * index + 2;
 
                if (leftIndex >= (copy.size()))
                    break;
 
                int largestIndex = index;
                if (leftIndex < (copy.size()) &&
                    getPriority(copy.pq[leftIndex]) > getPriority(copy.pq[largestIndex]))
                {
                    largestIndex = leftIndex;
                }
                if (rightIndex < (copy.size()) &&
                    getPriority(copy.pq[rightIndex]) > getPriority(copy.pq[largestIndex]))
                {
                    largestIndex = rightIndex;
                }
                if (largestIndex == index)
                    break;
 
                std::swap(copy.pq[index], copy.pq[largestIndex]);
                index = largestIndex;
            }
        }
	}

private:
	std::vector<Student> pq; // Store students by value 

	// Calculates the priority of a student as 70% units taken and 30% GPA,
	// normalized so both components are in the range [0,1]
	static float getPriority(Student student)
	{
		float normalizedUnits = student.getUnitsTaken() / 150.0f;
		float normalizedGPA   = student.getGPA() / 4.0f;
		return (0.7f * normalizedUnits) + (0.3f * normalizedGPA);
	}

	// Finds the correct index for a given node within pq after insertion to back
	void bubbleUp(int index)
	{
		while(index > 0)
		{
			int parentIndex = (index - 1) / 2;
			if(getPriority(pq[index]) > getPriority(pq[parentIndex]))
			{
				// Swap
				Student temp = pq[index];
				pq[index] = pq[parentIndex];
				pq[parentIndex] = temp;
				
				index = parentIndex;
			}
			else
				break; // Heap property satisfied
		}
	}

	// Restores the heap property after removing the root element
	void bubbleDown()
	{
		// Move last element to front
		pq[0] = pq[pq.size() - 1];
		pq.pop_back();
		if (pq.size() == 0)
			return;

		int index = 0;
		while (true)
		{
			int leftIndex  = (index * 2) + 1;
			int rightIndex = (index * 2) + 2;

			if (leftIndex >= pq.size())
				break; // no children

			int largestIndex = index;

			if (leftIndex < pq.size() && getPriority(pq[leftIndex]) > getPriority(pq[largestIndex]))
			{
				largestIndex = leftIndex;
			}

			if (rightIndex < pq.size())
			{
				if (getPriority(pq[rightIndex]) > getPriority(pq[largestIndex]))
				{
					largestIndex = rightIndex;
				}
			}

			if (largestIndex == index)
				break;
			
			// Swap
			Student temp = pq[index];
			pq[index] = pq[largestIndex];
			pq[largestIndex] = temp;

			index = largestIndex;
		}
	}
};