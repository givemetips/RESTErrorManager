#include "stdafx.h"
#include "Error.h"
//setters
void Error::setName(const std::string& newName) {
	name = newName;
}

void Error::setSource(const std::string& newSource) {
	source = newSource;
}

void Error::setStackTrace(const std::string& newStackTrace) {
	stackTrace = newStackTrace;
}

void Error::setRegDate(const Date& newDate) {
	registrationDate = newDate;
}

void Error::setCorrectedStatus(bool newStatus) {
	isCorrect = newStatus;
}

//getters
std::string Error::getName() const  {
	return name;
}

std::string Error::getSource() const  {
	return source;
}

std::string Error::getStackTrace() const  {
	return stackTrace;
}

Date Error::getRegDate() const  {
	return registrationDate;
}

bool Error::getCorrectedStatus() const  {
	return isCorrect;
}

Error::Error() {

}

Error::~Error() {

}
//construct from json
Error::Error(json::value jvalue) {

		auto map = jvalue.as_object();

		try {
			name = toString(map.at(L"name").as_string());
		}
		catch (std::exception e) {
			std::wcout << e.what() << std::endl;
		}

		try {
			source = toString(map.at(L"source").as_string());;
		}
		catch (std::exception e) {
			std::wcout << e.what() << std::endl;
		}

		try {
			stackTrace = toString(map.at(L"stacktrace").as_string());;

		}
		catch (std::exception e) {
			std::wcout << e.what() << std::endl;
		}
		
		try {
			registrationDate = Date(toString(map.at(L"date").as_string()));
		}
		catch (std::exception e) {
			std::wcout << e.what() << std::endl;
		}

		try {
			isCorrect = map.at(L"correct").as_bool();
		}
		catch (std::exception e) {
			std::wcout << e.what() << std::endl;
		}
}


//construct vector of errors from json 
std::vector<Error> Error::errorsFromJson(json::value jvalue) {

	std::vector<Error> answer;

	auto jArray = jvalue.as_array();

	for (auto jInstance : jArray) {

		answer.push_back(Error(jInstance));
	
	}

	return answer;
}

//create Error's json;
std::pair<utility::string_t, json::value> Error::getJson(int idintifier) {
	json::value ans;

	ans[L"name"] = json::value(utility::conversions::to_string_t(name));
	ans[L"source"] = json::value(utility::conversions::to_string_t(source));
	ans[L"stacktrace"] = json::value(utility::conversions::to_string_t(stackTrace));
	ans[L"date"] = json::value(utility::conversions::to_string_t(registrationDate.getString()));
	ans[L"correct"] = json::value(isCorrect);
	
	return std::make_pair(utility::conversions::to_string_t(std::to_string(idintifier)), ans);
}