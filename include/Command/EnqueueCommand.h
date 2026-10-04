#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 5rd 2026
* Description	: Enqueue Command Pattern Implementation 
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/

/* Class defs **********************************************************************************************/
#include "Priority Queue.h"
#include "Command.h"
#include "Student.h"
#include <stdexcept>
#include <utility>
#include <vector>

class EnqueueCommand : public Command<Student>
{
public:
    explicit EnqueueCommand(PriorityQueue& queue, const Student& last_enqeued) 
    : p_queue(queue), last_enqeued(last_enqeued) {}

    bool execute() override
    {
        if(executed)
            return false;
        p_queue.enqueue(last_enqeued);
        executed = true;
        return true;
    }

    bool undo() override
    {
        if(!executed)
            return false;
        p_queue.remove(last_enqeued);
        executed = false;
        return true;
    }

private:
    PriorityQueue& p_queue;
    Student last_enqeued;
    bool executed = false;
};