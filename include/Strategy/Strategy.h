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
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual bool higherPriority(const T& a, const T& b) const = 0;

};