#include "ToolkitTest.h"

TEST_F(ToolkitTest, integerToString){
	EXPECT_EQ("10", toolkit.integerToString(1));
	EXPECT_EQ("10", toolkit.integerToString(10));
	EXPECT_EQ("10", toolkit.integerToString(-1));
}