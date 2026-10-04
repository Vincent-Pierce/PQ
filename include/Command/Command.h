#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: October 5rd 2026
* Description	: Command Pattern Implementation 
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/

/* Class defs **********************************************************************************************/

template <typename T>
class Command
{
public:
    virtual ~Command() = default;
    virtual bool execute() = 0;
    virtual bool undo() = 0;
};