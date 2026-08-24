#pragma once
/* **********************************************************************************************************
* Author		: Vincent Pierce
* Created		: August 19th 2026
* Description	: Student Class definition
*
************************************************************************************************************/

/* Standard Libs *******************************************************************************************/
#include <string>
#include <stdint.h>
#include "math.h"


/* Class defs **********************************************************************************************/

class Student {
public:
	// The default constructor for Student. Priority is default -1 so that PriorityQueue can distinguish uninitialized students. Delete me later not meant for usage
	Student() : name(""), red_id(0), email(""), GPA(0.0), units_taken(0), priority(-1.0)
	{
	}

	// The parameterized constructor for Student using initializer list.
	Student(std::string name, uint64_t red_id, std::string email, float GPA, uint8_t units_taken) : name(name), red_id(red_id), email(email), GPA(GPA), units_taken(units_taken), priority(-1.0)
	{
		this->priority = (0.7 * units_taken) + (0.3*GPA);
		printf("My priority is %f\n", priority);
	}

	// Accessor Method for name
	std::string getName(void) const
	{
		return name;
	}

	// Accessor Method for red_id
	uint64_t getRedID(void) const
	{
		return red_id;
	}

	// Accessor Method for email
	std::string getEmail(void) const
	{
		return email;
	}

	// Accessor Method for GPA
	float getGPA(void) const
	{
		return GPA;
	}
	// Accessor Method for units_taken
	uint8_t getUnitsTaken(void) const
	{
		return units_taken;
	}

	// Accessor Method for priority
	float getPriority(void) const
	{
		return priority;
	}

private:
	std::string		name;
	uint64_t		red_id;
	std::string		email;
	float			GPA;
	uint8_t			units_taken;
	float			priority;			// Calculated as a fraction of GPA and units_taken
};