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

/* Class defs **********************************************************************************************/

class PriorityQueue
{
public:
	PriorityQueue() {};

	void insert(Student* student)
	{
		pq.push_back(student);			// insertion pushes to back of pq, then finds the correct position with bubble up
		int index = pq.size() - 1;
		bubbleUp(student, index);
	}

	Student* peek(void)
	{
		printf("PEEKING\nname:\t%s\t\tpriority:\t%f\n", pq[0]->getName().c_str(), pq[0]->getPriority());
		return pq[0];
	}

	Student* pop(void)
	{
		if (!pq.size())
			return nullptr;

		Student* retVal = pq[0];
		bubbleDown();

		return retVal;
	}

	void print(void) const
	{
		for (int i = 0; i < pq.size(); ++i)
		{
			printf("Name:\t%s\tRedID:\t%lu\tPriority:\t%f\n", pq[i]->getName().c_str(), pq[i]->getRedID(), pq[i]->getPriority());
		}
	}

private:
	std::vector<Student*> pq;

	// Returns the parent node for given index in pq
	Student* getParent(int index)
	{
		return pq[(index-1) / 2];
	}

	// Returns the left child node for given index in pq
	Student* getLeftChild(int index)
	{
		if (pq.size() <= (index * 2) + 1)
			return nullptr;
		return pq[(index * 2) + 1];
	}

	// Returns the right child node for given index in pq
	Student* getRightChild(int index)
	{
		if (pq.size() <= (index * 2) + 2)
			return nullptr;
		return pq[(index * 2) + 2];
	}

	// Swaps two given student pointers
	void swap(Student*& a, Student*& b)
	{
		Student* temp = a;
		a = b;
		b = temp;
	}

	// Finds the correct index for a given node within pq after insertion to back
	void bubbleUp(Student* curr, int curr_index)
	{
		Student* parent = getParent(curr_index);
		while (curr_index > 0 && curr->getPriority() > parent->getPriority())
		{
			Student* temp = curr;
			pq[curr_index] = parent;
			curr_index = (curr_index - 1) / 2;  // update curr index for next loop to be parent index
			pq[curr_index] = temp;

			parent = getParent(curr_index);
		}
	}

	// Finds the correct index for
	void bubbleDown()
	{
		// Move last element to front
		pq[0] = pq[pq.size() - 1];

		pq.pop_back();
		if(pq.size() == 0)
			return;
		// swap with min child
		Student* curr = pq[0];
		int index = 0;
		while (index < pq.size())
		{
			Student* left = getLeftChild(index);
			Student* right = getRightChild(index);
			if (left != nullptr && left->getPriority() > curr->getPriority())
			{
				swap(pq[index], pq[(index * 2) + 1]);
			}
			else if (right != nullptr && right->getPriority() > curr->getPriority())
			{
				swap(pq[index], pq[(index * 2) + 2]);
			}
			else if (left != nullptr && right != nullptr && left->getPriority() == right->getPriority())
			{
				// tie breaker, if left and right are equal, pop the one that was inserted first (left)
				swap(pq[index], pq[(index * 2) + 1]);
			}
			else
				break;
			
			++index;

		}
	}
};