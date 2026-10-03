
#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 3th 2026
* Description	: Queue Class Implementation  
*
************************************************************************************************************/

/* Class defs **********************************************************************************************/

template <typename T>

class Queue : public Collection<T>
{
public:

    virtual ~Queue() = default;

    virtual void enqueue(const T& item) = 0;
    virtual void dequeue() = 0;

    void push(const T& item) override
    {
        enqueue(item);
    } 

    void pop(const T& item) override
    {
        dequeue();
    }

    
};