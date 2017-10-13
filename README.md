# README #

### Authors: ###

* Kayeng Thao
* Ryan Guinn 

### Build Directions: ###

* Go into vagrant development 
* navigate to cd /vagrant
* Run make 
* type: ./HexTest 
* proft 

* NonTest Folder contains files for build with prompts 
* Files in the main directory have limited if any prompts


### Testing Directions: ###

TEST(HexTest, FirstTest) {
    std::istringstream in1("ABC + ABC"); 
    std::ostringstream out1; 
    readValPrintLoop(in1, out1); 
    EXPECT_EQ(out1.str(), ">1578\n");
}

Writing:

* Begin with test stub
* create an istream with the math you want to do 
* create an outstream to compare answeres with 
* standard calculations will have >[number]\n format

Running:

* Run ./hexTest or do make coverage 
* see results 

### Languages: ###

* C++ 11 
* English 

### Description: ### 

* A simple hex calculator. While you will be running the tests and not the main file, it is in charge of returning hex values. Also keep in mind that with the testing enviorment, you will not be receiving the full implementation. 

### Known Bugs/Limitations: ### 
 
* Multiplcation and Exponents are very ineficant
* Some un-used code in testing version