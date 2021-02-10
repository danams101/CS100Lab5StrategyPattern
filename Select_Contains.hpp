#ifndef __SELECT_CONTAINS__
#define __SELECT_CONTAINS__

#include "select.hpp"
#include "spreadsheet.hpp"

class Select_Contains : public Select_Column {
public:
	Select_Contains( const Spreadsheet* sheet, const std::string& columnName, const std::string& ss) {
		Select_Column(sheet, columnName);
		substring = ss;
	}
	
	virtual bool select(const std::string& s) const {
		if(s.find(substring) != std::string::npos)
        	{
                	return true;
        	}
        	return false;
	}

protected:
	//int column;
	std::string substring;

};



#endif
