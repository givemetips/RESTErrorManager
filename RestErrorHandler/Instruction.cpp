#include "stdafx.h"
#include "Instruction.h"

Instruction::Instruction(json::value jInstruction) {

	auto jMap = jInstruction.as_object();

	try {
		name = toString(jMap.at(L"name").as_string());
	}
	catch (std::exception e) {
		std::wcout << e.what() << std::endl;
	}

	try {
		source = toString(jMap.at(L"source").as_string());
	}
	catch (std::exception e) {
		std::wcout << e.what() << std::endl;
	}

	try {
		startDate = Date(toString(jMap.at(L"startdate").as_string()));
	}
	catch (std::exception e) {
		std::wcout << e.what() << std::endl;
	}

	try {
		endDate = Date(toString(jMap.at(L"enddate").as_string()));
	}
	catch (std::exception e) {
		std::wcout << e.what() << std::endl;
	}

	try {
		onFixDate = Date(toString(jMap.at(L"onfixdate").as_string()));
	}
	catch (std::exception e) {
		std::wcout << e.what() << std::endl;
	}

}

std::string Instruction::getSelectQuery() {
	
	std::string selectQuerry = "SELECT * FROM " + constants::ERRTABLENAME;
	std::string conditions;

	if (!name.empty()) {
		conditions += " WHERE name = " + name;
	}

	if (!source.empty()) {
		if (!conditions.empty()) {
			conditions += " AND source = " + source;
		}
		else {
			conditions += "WHERE source = " + source;
		}
	}

	if (!(startDate == Date())) {
		if (!conditions.empty()) {
			conditions += " AND date >= " + Date::toString(startDate);
		}
		else {
			conditions += " WHERE date >= " + Date::toString(startDate);
		}
	}

	if (!(endDate == Date())) {
		if (!conditions.empty()) {
			conditions += " AND date <= " + Date::toString(endDate);
		}
		else {
			conditions += " WHERE date <= " + Date::toString(endDate);
		}
	}

	if (!(onFixDate == Date())) {
		if (!conditions.empty()) {
			conditions += " AND date = " + Date::toString(onFixDate);
		}
		else {
			conditions += " WHERE date = " + Date::toString(onFixDate);
		}
	}

	return selectQuerry + conditions;
}