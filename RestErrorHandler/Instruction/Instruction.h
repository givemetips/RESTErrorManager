#pragma once
#include "stdafx.h"
#include "Comparation.h"
class Instruction {
private:
	
	Comparator *comp;

	std::string name;
	std::string source;
	Date startDate;
	Date endDate;
	Date onFixDate;
	
public:
	
	Instruction(json::value);
	Instruction();

	std::string getSelectQuery(); 
};