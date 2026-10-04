#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: August 19th 2026
* Description	: Priority Queue Implementation
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/
#include "Student.h"
#include <algorithm>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <utility>

/* Class defs **********************************************************************************************/
#include "Queue.h"
#include "Strategy/Strategy.h"
#include "Strategy/MaxStrategy.h"
class PriorityQueue : public Queue<Student>
{
public:
	// Default to max-heap
	PriorityQueue() : PriorityQueue(std::make_shared<MaxStrategy<Student>>())
	{
	}

	explicit PriorityQueue(std::shared_ptr<const Strategy<Student>> strategy) : strategy(std::move(strategy))
	{
		if (!this->strategy)
			throw std::invalid_argument("PriorityQueue requires a strategy");
	}

	~PriorityQueue() = default;



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

		removeAt(0);

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

	// Removes the first matching student and restores the heap property.
	bool remove(const Student& student)
	{
		auto found = std::find(pq.begin(), pq.end(), student);
		if (found == pq.end())
			return false;

		removeAt(static_cast<int>(found - pq.begin()));
		return true;
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
		PriorityQueue copy = *this;
		while (!copy.isEmpty())
		{
			const Student& student = copy.pq[0];
			std::printf("Name:\t%s\tRedID:\t%llu\tPriority:\t%f\n",
				student.getName().c_str(),
				static_cast<unsigned long long>(student.getRedID()),
				student.computePriority());
			copy.dequeue();
		}
	}

private:
	std::vector<Student> pq; // Store students by value 
	std::shared_ptr<const Strategy<Student>> strategy;

	void removeAt(int index)
	{
		if (index != static_cast<int>(pq.size()) - 1)
			pq[index] = std::move(pq.back());
		pq.pop_back();

		if (index >= static_cast<int>(pq.size()))
			return;

		if (index > 0 && strategy->higherPriority(pq[index], pq[(index - 1) / 2]))
			bubbleUp(index);
		else
			bubbleDown(index);
	}

	// Finds the correct index for a given node within pq after insertion to back
	void bubbleUp(int index)
	{
		while(index > 0)
		{
			int parentIndex = (index - 1) / 2;
			if(strategy->higherPriority(pq[index], pq[parentIndex]))
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

	// Restores the heap property from the given node toward the leaves.
	void bubbleDown(int index)
	{
		while (true)
		{
			int leftIndex  = (index * 2) + 1;
			int rightIndex = (index * 2) + 2;

			if (leftIndex >= pq.size())
				break; // no children

			int highestPriorityIndex = index;

			if (leftIndex < pq.size() && strategy->higherPriority(pq[leftIndex], pq[highestPriorityIndex]))
			{
				highestPriorityIndex = leftIndex;
			}

			if (rightIndex < pq.size())
			{
				if (strategy->higherPriority(pq[rightIndex], pq[highestPriorityIndex]))
				{
					highestPriorityIndex = rightIndex;
				}
			}

			if (highestPriorityIndex == index)
				break;
			
			// Swap
			Student temp = pq[index];
			pq[index] = pq[highestPriorityIndex];
			pq[highestPriorityIndex] = temp;

			index = highestPriorityIndex;
		}
	}
};