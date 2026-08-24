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
	// The default constructor for Student. 
	Student() : name(""), red_id(0), email(""), GPA(0.0), units_taken(0)
	{
	}

	// The parameterized constructor for Student using initializer list.
	Student(std::string name, uint64_t red_id, std::string email, float GPA, int units_taken) : name(name), red_id(red_id), email(email), GPA(GPA), units_taken(units_taken)
	{
		// Boundary for GPA and units_taken. Neither can be negative. GPA max is 4.0 and units_taken max is 150.
		if(GPA < 0.0)
			this->GPA = 0.0;
		else if(GPA > 4.0)
			this->GPA = 4.0;
		if(units_taken < 0)
			this->units_taken = 0;
		if(units_taken > 150)
			this->units_taken = 150;

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

	// Print out red id and name of student
	void print(void) const
	{
		printf("Name:\t%s\tRedID:\t%lu\n", name.c_str(), red_id);
	}

private:
	std::string		name;
	uint64_t		red_id;
	std::string		email;
	float			GPA;
	int				units_taken;
};