#pragma once
#include "stdafx.h"
#include "Error.h"

class Comparator {
public:

	virtual bool compare(Error, Error) =0;

	Comparator();
};

class FullComparator : public Comparator {
public:

	bool compare(Error, Error);

	FullComparator();
};

