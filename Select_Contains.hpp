#ifndef __SELECT_CONTAINS__
#define __SELECT_CONTAINS__

#include "select.hpp"
#include "spreadsheet.h"

class Select_Contains : public Select_Column {
public:
	Select_Contains( const Spreadsheet* sheet, const std::string& columnName, const std::string& ss);
	
	virtual bool select(const std::string& s) const;

private:
	int column;
	std::string substring;

};



#endif
