#pragma once
#include "stdafx.h"
class ErrorListener : public experimental::listener::http_listener {

public:
	ErrorListener(const http::uri& url);
private:
	static void handleGet(http_request);
	static void handlePost(http_request);

	http_listener mListener;
};