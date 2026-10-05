#include "Iterator.h"
#include "Student.h"
#include "Priority Queue.h"
#include <cstddef>

class PriorityQueueIterator : public Iterator<Student>
{
    public:

        explicit PriorityQueueIterator(PriorityQueue pq) : pq(pq), pq_copy(pq) {}

        PriorityQueueIterator& operator++()
        {
            if(!pq_copy.isEmpty())
                pq_copy.dequeue();
            return *this;
        }

        void operator++(int)
        {
            ++(*this);
        }

        bool operator!=(std::nullptr_t) const
        {
            return current() != nullptr;
        }

        const Student* first() const override
        {
            if (pq.isEmpty())
                return nullptr;
            return pq.front();
        }

        const Student* next() override
        {
            if(!pq_copy.isEmpty())
            {
                pq_copy.dequeue();
                return pq_copy.front();
            }
            else
                return nullptr;
        }


        const Student* current() const override
        {
            if(pq_copy.isEmpty())
                return nullptr;
            return pq_copy.front();
        }

    private:
        PriorityQueue pq;
        PriorityQueue pq_copy;
};
