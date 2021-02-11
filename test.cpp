#include "spreadsheet.hpp"
#include "gtest/gtest.h"
#include "select.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ContainTest, Regular){
	Spreadsheet sheet;
	sheet.set_column_names({"First"});
	sheet.add_row({"Cat"});
	sheet.add_row({"Dog"});
	sheet.add_row({"Rat"});
	sheet.set_selection(new Select_Contains(&sheet,"First","Cat"));
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string str = ss.str();
	ASSERT_EQ(str,"Cat \n");
}

TEST(ContainTest, EmptyColumnName){
        Spreadsheet sheet;
        sheet.set_column_names({""});
        sheet.add_row({"Cat"});
        sheet.add_row({"Dog"});
        sheet.add_row({"Rat"});
        sheet.set_selection(new Select_Contains(&sheet,"","Cat"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"Cat \n");
}

TEST(ContainTest, RepeatedColumnName){
        Spreadsheet sheet;
        sheet.set_column_names({"First","First"});
        sheet.add_row({"Cat","Dog"});
        sheet.add_row({"Dog","Rat"});
        sheet.add_row({"Rat","Cat"});
        sheet.set_selection(new Select_Contains(&sheet,"First","Cat"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"Cat Dog \n");
}

TEST(ContainTest, SingleCharacter){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"Cat"});
        sheet.add_row({"Dog"});
        sheet.add_row({"Rat"});
        sheet.set_selection(new Select_Contains(&sheet,"First","a"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"Cat \nRat \n");
}

TEST(ContainTest, InvolveAll){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Contains(&sheet,"First","apple"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"apple \napples \n");
}

TEST(Contain_AndTest, Regular_Empty){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","a"),new Select_Contains(&sheet,"First","A")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"");
}

TEST(Contain_AndTest, Regular_Full){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","p"),new Select_Contains(&sheet,"First","l")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"apple \napples \nApple \n");
}

TEST(Contain_OrTest, Regular_Full){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","a"),new Select_Contains(&sheet,"First","A")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"apple \napples \nApple \n");
}

TEST(Contain_OrTest, Regular_Empty){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","ewq"),new Select_Contains(&sheet,"First","xe")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"");
}

TEST(Contain_NotTest, Regular_Empty){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","pp")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"");
}

TEST(Contain_NotTest, Regular_Full){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","b")));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"apple \napples \nApple \n");
}

TEST(Mix_Function_Test,Regular_checkOrder){
	Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
	sheet.add_row({"Banana"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","Banana"),new Select_And(new Select_Not(new Select_Contains(&sheet,"First","Banana")),new Select_Contains(&sheet,"First","A"))));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"Apple \nBanana \n");
}
