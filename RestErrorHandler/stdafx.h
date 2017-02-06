

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "DateTIme.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

namespace constants {
	const std::string ERRDBNAME = "ErrorsDB";

	const std::string ERRTABLENAME = "Errors";
};

