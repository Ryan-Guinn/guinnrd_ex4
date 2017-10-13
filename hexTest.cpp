#include "hexiConverter.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

TEST(HexTest, AddHappyPath) {
    std::istringstream in1("ABC + 123"); 
    std::ostringstream out1;
    readValPrintLoop(in1, out1);
    EXPECT_EQ(out1.str(), ">BDF\n");
}

TEST(HexTest, AddDifferentLengths) {
    std::istringstream in1("ABC + 1234"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1CF0\n");
}

TEST(HexTest, AddNegatives) {
    std::istringstream in1("-ABC + -123"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-BDF\n");
}

TEST(HexTest, AddBigNum) {
    std::istringstream in1("FFFFFFFFF8349587298752378FEACB485 + FFFFFFFF83987207BCADE8374298"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">100000FFFF8348DC0B0A7CE026E6E3F71D\n");
}

TEST(HexTest, AddCarryPropagation) {
    std::istringstream in1("FFFFFFFFFFFFF + 1"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">10000000000000\n");
}

// Positive + Positive 
TEST(HexTest, PosPPosTest) {
    std::istringstream in1("ABC + ABC"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1578\n");
}

// Positive + Negative 
TEST(HexTest, PosPNegTest) {
    std::istringstream in1("FAB + -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1FE\n");
}

// Negative + Positive
TEST(HexTest, NegPPosTest) {
    std::istringstream in1("-FAB + DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1);
    EXPECT_EQ(out1.str(), ">-1FE\n");
}

// Negative + Negative
TEST(HexTest, NegPNegTest) {
    std::istringstream in1("-FAB + -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-1D58\n");
}

// Positive - Positive 
TEST(HexTest, PosNPosTest) {
    std::istringstream in1("ABC - ABC"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">000\n");
}

// Positive - Negative 
TEST(HexTest, PosNNegTest) {
    std::istringstream in1("FAB - -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1D58\n");
}

// Negative - Positive 
TEST(HexTest, NegNPosTest) {
    std::istringstream in1("-FAB - DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-1D58\n");
}

// Negative - Negative 
TEST(HexTest, NegNNegTest) {
    std::istringstream in1("-FAB - -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-1FE\n");
}

// Negative * Negative 
TEST(HexTest, multTestNN) {
    std::istringstream in1("-FAB * -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">D6458F\n");
}

// Negative * Positive 
TEST(HexTest, multTestNP) {
    std::istringstream in1("-FAB * DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-D6458F\n");
}

// Positive * Negative 
TEST(HexTest, multTestPN) {
    std::istringstream in1("FAB * -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-D6458F\n");
}

// Positive * Positive 
TEST(HexTest, multTestPP) {
    std::istringstream in1("FAB * DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">D6458F\n");
}

// Positive | Positive 
TEST(HexTest, orTestPP) {
    std::istringstream in1("FAB | DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">FAF\n");
}

// Negative | Positive 
TEST(HexTest, orTESTNP) {
    std::istringstream in1("-FAB | DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">FAF\n");
}

// Negative | Positive 
TEST(HexTest, orTESTPN) {
    std::istringstream in1("FAB | -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">FAF\n");
}

// Negative | Positive 
TEST(HexTest, orTESTNN) {
    std::istringstream in1("-FAB | -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">FAF\n");
}

// Positive & Positive 
TEST(HexTest, andTestPP) {
    std::istringstream in1("FAB & DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">DA9\n");
}

// Negative & Positive 
TEST(HexTest, andTESTNP) {
    std::istringstream in1("-FAB & DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">DA9\n");
}

// Positive & Negative 
TEST(HexTest, andTESTPN) {
    std::istringstream in1("FAB & -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">DA9\n");
}

// Negative & Negative 
TEST(HexTest, andTESTNN) {
    std::istringstream in1("-FAB & -DAD"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">DA9\n");
}

// Positive & Positive 
TEST(HexTest, exTestPP) {
    std::istringstream in1("F ^ F"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">613B62C597707EF\n");
}

// Negative & Positive 
TEST(HexTest, exTESTNP) {
    std::istringstream in1("-F ^ F"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">-613B62C597707EF\n");
}

// Negative & 0 
TEST(HexTest, exTESTN0) {
    std::istringstream in1("-F ^ 0"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1\n");
}

// 0 & positive 
TEST(HexTest, exTEST0P) {
    std::istringstream in1("0 ^ F"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">0\n");
}
// Positive & Negative: Nope! 

// Negative & Negative: Nope! 

TEST (HexTest, getHistory){
    std::string historyMock[10] = {"ABC + ABC"}; 
    std::ostringstream out1; 
    extractHistory(historyMock, false, out1); 
    EXPECT_EQ(out1.str(), "> ABC + ABC\n");
}


TEST(HexTest, confrimHEXTestT) {
    bool check = confirmHex("ABC"); 
    EXPECT_EQ(true, check);
}

TEST(HexTest, confrimHEXTestF) {
    bool check = confirmHex("GGG"); 
    EXPECT_EQ(false, check);
}


TEST(HexTest, confirmOPT){
    bool check = confirmOp("+");
    EXPECT_EQ(true, check);
}

TEST(HexTest, confirmOPF){
    bool check = confirmOp("$");
    EXPECT_EQ(false, check);
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

      
