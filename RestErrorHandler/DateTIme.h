#pragma once
#include "stdafx.h"
#include <ctime>

class Date {
private:
	int day;
	int month;
	int year;
	static int curYear() {
		time_t t = time(NULL);
		struct tm* timePtr = localtime(&t);
		return timePtr->tm_year + 1900;
	}

public:
	Date() {
		day = 1;
		month = 1;
		year = 1960;
	}

	Date(int a, int b, int c) : day(a), month(b), year(c) {
		if (day < 1 || day > 31) day = 1;
		if (month < 1 || month > 12) month = 1;
		if (year < 2000 || year > curYear()) {
			year = curYear();
		}
	}

	Date(const std::string& s) {
		Date result = dateFromString(s);
		day = result.day;
		month = result.month;
		year = result.month;
	}

	Date dateFromString(const std::string s) {
		using stringIt = std::string::const_iterator;

		stringIt firstSpace = s.begin();
		stringIt secondSpace = s.begin();

		for (auto it = s.begin(); it != s.end(); ++it) {
			if (*it >= '0' && *it <= '9') continue;
			if (firstSpace == s.begin()) firstSpace = it;
			secondSpace = it;
		}

		day = std::stoi(std::string(s.begin(), firstSpace));
		month = std::stoi(std::string(firstSpace + 1, secondSpace));
		year = std::stoi(std::string(secondSpace + 1, s.end()));
		
		Date result(day, month, year);
		return result;
	}

	static std::string toString (Date d) {
		std::string res;

		res += std::to_string(d.day);
		res += '/';
		res += std::to_string(d.month);
		res += '/';
		res += std::to_string(d.year);
	
		return res;
	}

	void swap(Date& secondDate) {
		
		std::swap((*this).day, secondDate.day);
		std::swap((*this).month, secondDate.month);
		std::swap((*this).year, secondDate.year);
	
	}

	Date& operator=(Date newDate) {
		
		this->swap(newDate);

		return *this;
	}

	friend bool operator == (Date firstDate, Date secondDate) {
		return (firstDate.day == secondDate.day
			&& firstDate.month == secondDate.month
			&& firstDate.year == secondDate.year);
	}
	
	std::string getString() {
		std::string resultString;
		
		if (day < 10) resultString += '0';
		resultString += std::to_string(day);
		
		resultString += '/';

		if (month < 10) resultString += '0';
		resultString += std::to_string(month);

		resultString += '/';

		resultString += std::to_string(year);

		return resultString;
	}
};

static std::string toString(utility::string_t str_t) {
	return (std::string(str_t.begin(), str_t.end()));
}
