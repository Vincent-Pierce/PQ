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

class PriorityQueue
{
public:
	PriorityQueue() = default;

	~PriorityQueue() = default;

	void insert(const Student& student)
	{
		pq.push_back(student);			// insertion pushes to back of pq, then finds the correct position with bubble up
		int index = pq.size() - 1;
		bubbleUp(index);
	}

	const Student* top(void) const
	{
		if(pq.empty())
			return nullptr;
		else
			return &pq[0];
	}

	bool pop(void)
	{
		if (!pq.size())
			return false;

		bubbleDown();

		return true;
	}

    // Print all students in PRIORITY ORDER by draining a copy of the heap
    void print(void) const
    {
        if (pq.empty())
            return;
 
        // Work on a copy so we don't disturb the real queue
        std::vector<Student> heap = pq;
 
        // Heapify (max-heap) from middle down to root
        for (int i = (heap.size() / 2) - 1; i >= 0; --i)
        {
            int index = i;
            while (true)
            {
                int leftIndex  = 2 * index + 1;
                int rightIndex = 2 * index + 2;
 
                if (leftIndex >= (heap.size()))
                    break;
 
                int largestIndex = index;
                if (leftIndex < (heap.size()) &&
                    getPriority(heap[leftIndex]) > getPriority(heap[largestIndex]))
                {
                    largestIndex = leftIndex;
                }
                if (rightIndex < (heap.size()) &&
                    getPriority(heap[rightIndex]) > getPriority(heap[largestIndex]))
                {
                    largestIndex = rightIndex;
                }
                if (largestIndex == index)
                    break;
 
                std::swap(heap[index], heap[largestIndex]);
                index = largestIndex;
            }
        }
 
        // Repeatedly remove max and print
        while (!heap.empty())
        {
            const Student& top = heap[0];
            std::printf("Name:\t%s\tRedID:\t%llu\tPriority:\t%f\n",
                top.getName().c_str(),
                static_cast<unsigned long long>(top.getRedID()),
                getPriority(top));
 
            heap[0] = heap.back();
            heap.pop_back();
 
            int index = 0;
            while (true)
            {
                int leftIndex  = 2 * index + 1;
                int rightIndex = 2 * index + 2;
 
                if (leftIndex >= (heap.size()))
                    break;
 
                int largestIndex = index;
                if (leftIndex < (heap.size()) &&
                    getPriority(heap[leftIndex]) > getPriority(heap[largestIndex]))
                {
                    largestIndex = leftIndex;
                }
                if (rightIndex < (heap.size()) &&
                    getPriority(heap[rightIndex]) > getPriority(heap[largestIndex]))
                {
                    largestIndex = rightIndex;
                }
                if (largestIndex == index)
                    break;
 
                std::swap(heap[index], heap[largestIndex]);
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