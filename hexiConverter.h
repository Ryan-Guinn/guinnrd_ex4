/*
 * hexiConverter.H
 *
 *  Created on: Sep 24, 2017
 *      Author: thaokaye
 */

#ifndef HEXICONVERTER_H_
#define HEXICONVERTER_H_

#include <iostream>

bool confirmOp(std::string oP);
int convertToDeci(std::string hexString);
bool confirmHex(std::string hexVal);
std::string convertToHex(int deciVal);
int readValPrintLoop(std::istream& input, std::ostream& output);
bool extractHistory(std::string history[10], bool exit, std::ostream& output); 



#endif /* HEXICONVERTER_H_ */
