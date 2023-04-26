#include <gtest/gtest.h>
#include <TestFunctions.h>

struct ResultTable
{
    int sumup_result=Test::sumup(20,20);            //Expected Result => 40
    double subup_result=Test::subup(20,20);         //Expected Result => 0
    long divideup_result=Test::divideup(20,20);     //Expected Result => 1
    unsigned int modup_result=Test::modup(20,20);   //Expected Result => 0
};


TEST(UnitTest, TestAddition) {
    ResultTable RT;
    ASSERT_EQ(RT.sumup_result, 40);
    ASSERT_EQ(RT.subup_result, 0);
    ASSERT_EQ(RT.divideup_result, 1);
    ASSERT_EQ(RT.modup_result, 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}