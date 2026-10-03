
#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 3th 2026
* Description	: Collection Base-Class Implementation  
*
************************************************************************************************************/

/* Class defs **********************************************************************************************/

template <typename T>

class Collection
{
public:

    virtual ~Collection() = default;

    virtual void push(const T& item) = 0;
    virtual void pop(const T& item) = 0;
    virtual const T* peek() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;
    virtual std::string toString() const = 0;
    virtual std::vector<T> toArray() const = 0;
};