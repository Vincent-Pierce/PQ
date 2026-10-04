#include "Priority Queue.h"
#include "Command.h"

class DequeueCommand : public Command<Student>
{
    public:
        DequeueCommand(PriorityQueue& p_queue) 
        : p_queue(p_queue) {}

        ~DequeueCommand() override = default;

        bool execute() override
        {
            if(p_queue.isEmpty() || executed)
                return false;

            last_dequeued = *p_queue.front();
            p_queue.dequeue();
            executed = true;
            return true;
        }

        bool undo() override
        {
            if(!executed)
                return false;
            p_queue.enqueue(last_dequeued);
            executed = false;
            return true;
        }

    private:
        PriorityQueue& p_queue;
        Student last_dequeued;
        bool executed = false;

};