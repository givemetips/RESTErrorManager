#include "stdafx.h"
#include "ServerHandler.h"
#include "Error.h"
#include "DBHandler.h"
#include "Instruction.h"
ErrorListener::ErrorListener(const http::uri& url) : mListener(http_listener(url)) {
	
	mListener.support(methods::GET, handleGet);
	mListener.support(methods::POST, handlePost);
	
	try {
		mListener.open().wait();
		while (true);
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
}

void ErrorListener::handleGet(http_request request) {
	
	std::vector<std::pair<utility::string_t, json::value>> answer;

	request
		.extract_json()
		.then([&answer](pplx::task<json::value> task) {
		
		auto jvalue = task.get();

		DBHandler dataBase = DBHandler::getInstance();
		dataBase.openConnection(constants::ERRDBNAME);

		Instruction instruction(jvalue);
		std::string selectQuery = instruction.getSelectQuery();
		
		std::vector<Error> errorsToAnswer { dataBase.selectErrors(selectQuery) };
		
		for (size_t ind = 0; ind < errorsToAnswer.size(); ++ind) {
			answer.push_back(errorsToAnswer[ind].getJson(ind));
		}

	})
		.wait();
	
	request
		.reply(status_codes::OK, json::value(&answer));

}

void ErrorListener::handlePost(http_request request) {

	request
		.extract_json()
		.then([](pplx::task<json::value> task) {
		
		auto jvalue = task.get();

		std::vector<Error> errorsToPut = Error::errorsFromJson(jvalue);
		
		DBHandler dataBase = DBHandler::getInstance();

		dataBase.openConnection(constants::ERRDBNAME);
		dataBase.insertErrors(errorsToPut, constants::ERRTABLENAME);
		dataBase.closeConnection();
	})
		.wait();

	utility::string_t answer = L"Errors succesfully added";

	request
		.reply(status_codes::OK, json::value(answer))
		.wait();

}