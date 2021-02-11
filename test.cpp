#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"

TEST(Select_Contains, NormalInput) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"First","Last"});
        sheet.add_row({"Amanda","Andrews"});
        sheet.add_row({"Brian","Becker"});
        sheet.add_row({"Carol","Conners"});
        sheet.add_row({"Joe","Jackson"});

        sheet.set_selection(new Select_Contains(&sheet,"Last","Becker"));
        sheet.print_selection(ss);
        expS = "Brian Becker \n";

        EXPECT_EQ(ss.str(),expS);
}
TEST(Select_Contains, EmptyString) {
	std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"First"});
        sheet.add_row({"Amanda"});
        sheet.add_row({"Brian"});
        sheet.add_row({"Carol"});
        sheet.add_row({"Joe"});

        sheet.set_selection(new Select_Contains(&sheet,"First",""));
        sheet.print_selection(ss);
        expS = "Amanda \nBrian \nCarol \nJoe \n";

        EXPECT_EQ(ss.str(),expS);

}
TEST(Select_Contains, DiffCaseLetters) {
	std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"Cat"});

	sheet.set_selection(new Select_Contains(&sheet, "test", "cat"));
	sheet.print_selection(ss);
	expS = "";

	EXPECT_EQ(ss.str(), expS);
	

}
TEST(Select_Contains, Substrings) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"apples"});
	sheet.add_row({"snapple"});
	sheet.add_row({"APPLE"});
	sheet.add_row({"app"});

        sheet.set_selection(new Select_Contains(&sheet, "test", "apple"));
        sheet.print_selection(ss);
        expS = "apples \nsnapple \n";

        EXPECT_EQ(ss.str(), expS);
	
}
TEST(Select_Contains, MatchingToEmpty) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({""});

        sheet.set_selection(new Select_Contains(&sheet, "test", "cat"));
        sheet.print_selection(ss);
        expS = "";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Contains, NonexistantColumn) {
        std::stringstream ss;
        std::string expS;
	bool isThere = true;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"Cat"});

	if(sheet.get_column_by_name("test2") == -1){
		ss << "not found";
	}
	else {
		sheet.print_selection(ss);
	}       
	
        expS = "not found";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Contains, ColumnWithSameName) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"First", "First"});
        sheet.add_row({"apples", "grapes"});
        sheet.add_row({"snapple", "berries"});
        sheet.add_row({"APPLE", "apple"});
        sheet.add_row({"app", "melon"});

        sheet.set_selection(new Select_Contains(&sheet, "First", "l"));
        sheet.print_selection(ss);
        expS = "apples grapes \nsnapple berries \n";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Not, normalTest){
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"apples"});
        sheet.add_row({"snapple"});
        sheet.add_row({"APPLE"});
        sheet.add_row({"app"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "test", "APPLE")));
        sheet.print_selection(ss);
        expS = "apples \nsnapple \napp \n";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Not, SelectNotAll) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"apples"});
        sheet.add_row({"snapple"});
        sheet.add_row({"aPPLE"});
        sheet.add_row({"app"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "test", "z")));
        sheet.print_selection(ss);
        expS = "apples \nsnapple \naPPLE \napp \n";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Not, SelectNotNone) {
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"apples"});
        sheet.add_row({"snapple"});
        sheet.add_row({"aPPLE"});
        sheet.add_row({"app"});

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "test", "a")));
        sheet.print_selection(ss);
        expS = "";

        EXPECT_EQ(ss.str(), expS);

}

TEST(Select_And, normalTest){
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"cat"});
        sheet.add_row({"bat"});
        sheet.add_row({"rat"});
        sheet.add_row({"dog"});

        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"test","a"),new Select_Contains(&sheet,"test","t")));
        sheet.print_selection(ss);
        expS = "cat \nbat \nrat \n";

        EXPECT_EQ(ss.str(), expS);

}

TEST(Select_And, SelectNone){
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"sheep"});
        sheet.add_row({"crab"});
        sheet.add_row({"ram"});
        sheet.add_row({"dog"});

        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"test","a"),new Select_Contains(&sheet,"test","t")));
        sheet.print_selection(ss);
        expS = "";

        EXPECT_EQ(ss.str(), expS);
}
TEST(Select_Or, normalTest){
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"cat"});
        sheet.add_row({"bat"});
        sheet.add_row({"rat"});
        sheet.add_row({"dog"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"test","a"),new Select_Contains(&sheet,"test","o")));
        sheet.print_selection(ss);
        expS = "cat \nbat \nrat \ndog \n";

        EXPECT_EQ(ss.str(), expS);

}
TEST(Select_Or, Selectnone){
        std::stringstream ss;
        std::string expS;

        Spreadsheet sheet;

        sheet.set_column_names({"test"});
        sheet.add_row({"cat"});
        sheet.add_row({"bat"});
        sheet.add_row({"rat"});
        sheet.add_row({"dog"});

        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"test","z"),new Select_Contains(&sheet,"test","y")));
        sheet.print_selection(ss);
        expS = "";

        EXPECT_EQ(ss.str(), expS);

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
