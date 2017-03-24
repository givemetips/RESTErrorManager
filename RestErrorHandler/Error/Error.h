#pragma once
#include "stdafx.h"

class Error {
private:
	std::string name;
	std::string source;
	std::string stackTrace;
	Date registrationDate;
	bool isCorrect;

public:
	Error();
	Error(json::value);
	~Error();
	
	void setName(const std::string&);
	void setSource(const std::string&);
	void setStackTrace(const std::string&);
	void setRegDate(const Date&);
	void setCorrectedStatus(bool);
	
	std::string getName() const;
	std::string getSource() const;
	std::string getStackTrace() const;
	Date getRegDate() const;
	bool getCorrectedStatus() const;

	static std::vector<Error> errorsFromJson(json::value);
	std::pair<utility::string_t, json::value> getJson(const int);
};