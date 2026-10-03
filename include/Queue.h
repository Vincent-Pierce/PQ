
#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 3th 2026
* Description	: Queue Class Implementation  
*
************************************************************************************************************/

/* Class defs **********************************************************************************************/
#include "Collection.h"
template <typename T>

class Queue : public Collection<T>
{
public:

    virtual ~Queue() = default;

    // Queue-specific methods
    virtual void enqueue(const T& item) = 0;
    virtual bool dequeue() = 0;
    virtual const T* front() const = 0;

    // Wrapper method to satisfy Collection
    void push(const T& item) final override
    {
        enqueue(item);
    } 

    // Wrapper method to satisfy Collection
    void pop(const T& item) final override
    {
        dequeue();
    }

    // Wrapper method to satisfy Collection
    const T* peek() const final override
    {
        return front();
    }

};