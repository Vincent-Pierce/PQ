#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 3rd 2026
* Description	: Strategy Pattern Implementation 
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/

/* Class defs **********************************************************************************************/
#include "Strategy.h"

template <typename T>
class MinStrategy : public Strategy<Student>
{
public:
    MinStrategy() = default;
    virtual ~MinStrategy() = default;
    bool higherPriority(const Student& a, const Student& b) const override
    {
        return a.computePriority() < b.computePriority();
    }
};