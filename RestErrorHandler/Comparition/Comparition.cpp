#include "stdafx.h"
#include "Comparation.h"

Comparator::Comparator() {

};

FullComparator::FullComparator() {

};

bool FullComparator::compare(Error firstError, Error secondEerror) {
	
	bool nameEquality { firstError.getName() == secondEerror.getName() };
	bool sourceEquality { firstError.getSource() == secondEerror.getSource() };
	bool stackTraceEquality { firstError.getStackTrace() == secondEerror.getStackTrace() };
	bool dateEquality { firstError.getRegDate() == secondEerror.getRegDate() };
	bool correctedStatusEquality { firstError.getCorrectedStatus() == secondEerror.getCorrectedStatus() };

	return	nameEquality &&
			sourceEquality &&
			stackTraceEquality &&
			dateEquality &&
			correctedStatusEquality;
}
