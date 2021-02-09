#include <algorithm>
#include <iostream>

/*
 *class Select_Contains : public Select_Column {
public:
        Select_Contains( const Spreadsheet* sheet, const std::string& columnName, const std::string& ss);
        
        virtual bool select(const std::string& s) const;

private:
        int column;
        std::string substring;

};

 * */

Select_Contains::Select_Contains(const Spreadsheet* sheet, const std::string& columnName, const std::string& ss) 
{
	column = sheet->get_column_by_name(columnName);
	substring = ss;	
}

virtual bool Select_Contains::select(const std::string& s)
{
	if(s.find(substring) != std::string::npos)
	{
		return true;
	}
	return false;		
}
