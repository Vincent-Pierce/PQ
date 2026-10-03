#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 3rd 2026
* Description	: Strategy Pattern Implementation 
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/

/* Class defs **********************************************************************************************/

template <typename T>
class MaxStrategy : public Strategy<Student>
{
public:
    MaxStrategy() = default;
    virtual ~MaxStrategy() = default;
    bool higherPriority(const Student& a, const Student& b) const override
    {
        return a.computePriority() > b.computePriority();
    }

};