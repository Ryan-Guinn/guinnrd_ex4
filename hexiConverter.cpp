//============================================================================
// Name        : hexiConverter.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale>
#include "HexString.h"

using namespace std;

void reportResult(ostream& output, string response){
    output << response;
}

bool confirmOp(string oP){
    if ((oP[0] == '+') || (oP[0] == '-') || (oP[0] == '*') || (oP[0] == '|') || (oP[0] == '&') || (oP[0] == '^')){
        //cout << "Good Sign: " << oP[0] <<endl;
        return true;
    } else {
        //cout << "Incorrect sign: " << oP[0] << endl;
        return false;
    }

}
bool confirmHex(string hexVal){
    int len = hexVal.size();
    int iStart = 0;

    // check if hexVal is negative, if so, ingore check of - sign
    if (hexVal[0] == '-'){
        iStart = 1;
    }

    for (int i = iStart; i < len; ++i){
        if (isxdigit(hexVal[i]) == false){
            //cout << "NOT HEX: " << hexVal[i] << endl;
            //cout << "program will halt!" << endl;
            return false;
        }
    }
    return true;
}

string readLine(istream& input){
    string line;
    getline(input, line);
    return line;
}

bool extractHistory(string history[10], bool exit, ostream& output) {
	for (int i = 0; i <= 9; ++i) {
		if (history[i] != "") {
			string temp = "> " + history[i] + "\n";
			reportResult(output, temp);
		}
	}
	exit = false;
	return exit;
}

bool exitPrompt(string history[10], string& choice, istream& input, ostream& output) {
    bool exit = true;
    bool backToTop = true;

    while (backToTop) {
        //prompt for more
        cout << "Exit (X),  show up to last 10 (H), clear history (c), or continue (Y)?" << endl;
        getline(input, choice);
        if (choice == "x" || choice == "X") {
            cout << "Goodbye" << endl;
            backToTop = false;
            // continue
        } else if (choice == "y" || choice == "y") {
            backToTop = false;
        } else if (choice == "h" || choice == "H") {
            cout << "History..." << endl;
			exit = extractHistory(history, exit, output);
            backToTop = true;
        } else if (choice == "c" || choice == "C") {
            for (int i = 0; i <= 9; ++i) {
                history[i] = "";
            }
            cout << "History Reset!" << endl;
            for (int i = 0; i <= 9; ++i) {
                if (history[i] != "") {
                    cout << "> " << history[i] << endl;
                }
            }
            backToTop = true;
        } else {
            cout << "You typed in: " << choice << "- unknown command!" << endl;
            cout << "Exiting..." << endl;
            backToTop = false;
        }
    }
    return exit;
}

int parseCalculation(std::stringstream& stream, std::string& temp, string& hex1, bool& cont, string& operation, string& hex2) {
    int counter = 1;
    while (getline(stream, temp, ' ')) {
        std::stringstream stream2(temp);
        if (counter == 1) {
            hex1 = temp;
            std::locale loc;
            for (std::string::size_type i = 0; i < hex1.size(); ++i)
                hex1[i] = std::toupper(hex1[i], loc);
            if (confirmHex(hex1) == false) {
            }
        } else if (counter == 2) {
            operation = temp;
            if (confirmOp(operation) == false) {
            }
        } else if (counter == 3) {
            hex2 = temp;
            std::locale loc;
            for (std::string::size_type i = 0; i < hex1.size(); ++i)
                hex2[i] = std::toupper(hex2[i], loc);
            if (confirmHex(hex2) == false) {
            }
        }

        ++counter;
    }
    return counter;
}

void operateNums(bool cont, const string& hex1, const string& hex2, const string& operation, ostream& output) {
    string ans = "";
    if (cont != false) {
        // convert each one;
        HexString* num1 = new HexString(hex1);
        HexString* num2 = new HexString(hex2);
        cout << hex1 << endl;
        cout << num1->toString() << endl;

        // do calculations
        cout << "Calculating..." << endl;
        if (operation == "+") {
            HexString numAns = *num1 + *num2;
            // cout << numAns.value << endl;
            ans = ">" + numAns.toString();
        } else if (operation == "-") {
            HexString numAns = *num1 - *num2;
            // cout << numAns.value << endl;
            ans = ">" + numAns.toString();
        } else if (operation == "*") {
            HexString numAns = *num1 * *num2;
            //cout << numAns.value << endl;
            ans = ">" + numAns.toString();
        } else if (operation == "&") {
            HexString numAns = *num1 & *num2;
            // cout << numAns.value << endl;
            ans = ">" + numAns.toString();
        } else if (operation == "|") {
            HexString numAns = *num1 | *num2;
            // cout << numAns.value << endl;
            ans = ">" + numAns.toString();
        } else if (operation == "^") {
            HexString numAns = *num1 ^ *num2;
            // cout << numAns.value << endl;
            ans = ">" + numAns.toString() ;
        } 
        ans = ans + "\n";
        reportResult(output, ans);
    } 
}

int readValPrintLoop(istream& input, ostream& output) {
    //std::cout.setf(std::ios::unitbuf);
    bool cont = true;
    bool contLoop = true;
    string sample;
    string hex1;
    string hex2;
    string operation;
    string choice;
    string hexOp;
    string ans;
    string history[10];
    //set history strings to null
    for (int i = 0; i <= 9; ++i){
        history[i] = "";
    }

    cout << "Welcome to calculator" << endl;
    int historyCounter = 0;

    while (contLoop == true){
        cout << "Type in calculation:" << endl;
        // set vars to blanks
        hexOp = "";
        // take in operation
        hexOp = readLine(input);

        // store in history
        if (historyCounter == 10){
            historyCounter = 0;
        }

        history[historyCounter] = hexOp;
        ++historyCounter;

        // parse up by spaces
        std::string temp;
        std::stringstream stream(hexOp);

        cout << "Parsing!" << endl;

        parseCalculation(stream, temp, hex1, cont, operation, hex2);
        operateNums(cont, hex1, hex2, operation, output);

        //prompt for more
        bool exit = exitPrompt(history, choice, input, output);

        if (exit == true){
            break;
        } else {
        	string ans = "Continuing Calculator!\n";
        	reportResult(output, ans);
        }
    }

    return 0;
}

