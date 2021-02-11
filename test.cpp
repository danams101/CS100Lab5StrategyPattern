#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"

TEST(Select_Contains, NormalInput) {
	std::stringstream ss;
	std::string expS;

	Spreadsheet sheet;

    	sheet.set_column_names({"First","Last","Age","Major"});
    	sheet.add_row({"Amanda","Andrews","22","business"});
    	sheet.add_row({"Brian","Becker","21","computer science"});
    	sheet.add_row({"Carol","Conners","21","computer science"});
    	sheet.add_row({"Joe","Jackson","21","mathematics"});

	sheet.set_selection(new Select_Contains(&sheet,"Last","Becker"));
    	sheet.print_selection(ss);
	expS = "Brian Becker 21 computer science ";

	EXPECT_EQ(ss.str(),expS);//TWO STRINGS EQUAL, EXPECT_STRNE-> NOT EQUAL
}

TEST(Select_Contains, EmptyString) {

}
TEST(Select_Contains, DiffCaseLetters) {

}
TEST(Select_Contains, Substrings) {

}
TEST(Select_Contains, MatchingToEmpty) {

}
TEST(Select_Contains, NonexistantColumn) {

}
TEST(Select_Contains, ColumnWithSameName) {

}

TEST(Select_Not, normalTest){

}
TEST(Select_Not, SelectNotAll) {

}
TEST(Select_Not, SelectNotNone) {

}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
