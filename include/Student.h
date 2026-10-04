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
#include <stdexcept>
#include "math.h"


/* Class defs **********************************************************************************************/

class Student {
public:
	// The default constructor for Student. 
	Student() : name(""), red_id(0), email(""), GPA(0.0), units_taken(0)
	{
	}

	// The parameterized constructor for Student using initializer list.
	Student(std::string name, uint64_t red_id, std::string email, float GPA, float units_taken) : name(name), red_id(red_id), email(email), GPA(GPA), units_taken(units_taken)
	{
		// Boundary for GPA and units_taken. Neither can be negative. GPA max is 4.0 and units_taken max is 150.
		if (GPA < 0.0 || GPA > 4.0)
		{
			throw std::invalid_argument("GPA must be between 0.0 and 4.0");
		}
		if (units_taken < 0 || units_taken > 150)
		{
			throw std::invalid_argument("Units taken must be between 0 and 150");
		}

	}
	// Overloaded operator for deep comparison
	bool operator==(const Student& other) const
	{
		return name == other.name
			&& red_id == other.red_id
			&& email == other.email
			&& GPA == other.GPA
			&& units_taken == other.units_taken;
	}

	// Overloaded operator for comparing two students based on their computed priority.
	bool operator>(const Student& other) const
	{
		return computePriority() > other.computePriority();
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
	float getUnitsTaken(void) const
	{
		return units_taken;
	}

	float computePriority() const
	{
		float normalizedUnits = units_taken / 150.0f;
		float normalizedGPA   = GPA / 4.0f;
		return (0.7f * normalizedUnits) + (0.3f * normalizedGPA);
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
	float			units_taken;
};