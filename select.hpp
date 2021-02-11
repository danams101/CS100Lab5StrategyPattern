#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};


class Select_Contains : public Select_Column {
public:
        Select_Contains( const Spreadsheet* sheet, const std::string& columnName, const std::string& ss) : Select_Column(sheet, columnName) {
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
        std::string substring;
};

class Select_Not: public Select {
public:
	Select_Not(Select* selCont) {
		contains = selCont;
	}
	
	virtual bool select(const Spreadsheet* sheet, int row) const {
		if(contains->select(sheet,row) == true) {
			return false;
		}
		else {
			return true;
		}
	}

	virtual ~Select_Not() {
    
		delete contains;
	}
		
protected:
	Select* contains;
};


class Select_And: public Select{
protected:
	Select* one;
	Select* two;

public:
	Select_And(Select* check_one, Select* check_two){
		one = check_one;
		two = check_two;
}
	bool select(const Spreadsheet* sheet, int row) const{
		if(one->select(sheet,row) == true and two->select(sheet,row) == true){
			return true;
		}else{
			return false;
	}
	}

	virtual ~Select_And(){
		delete one;
		delete two;
	}
};


class Select_Or: public Select{
protected:
        Select* one;
        Select* two;

public:
        Select_Or(Select* check_one, Select* check_two){
                one = check_one;
                two = check_two;
}
        bool select(const Spreadsheet* sheet, int row) const{
                if(one->select(sheet,row) == true or two->select(sheet,row) == true){
                        return true;
                }else{
                        return false;
          }
        }

        virtual ~Select_Or(){
                delete one;
                delete two;
        }
};



#endif //__SELECT_HPP__
