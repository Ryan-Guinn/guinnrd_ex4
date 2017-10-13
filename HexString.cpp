//
// Created by guinnrd on 9/28/2017.
//

#include "HexString.h"

using namespace std;

HexString::HexString(string input) {
    negative = input.at(0) == '-';
    if(negative){
        value = input.substr(1);
    } else{
        value = input;
    }
}

HexString HexString::operator&(const HexString &input) {
    string result = "";
    int maxLen = max(value.length(),input.value.length());
    int offset = maxLen - value.length();
    int offsetIn = maxLen - input.value.length();

    for(int i = 0; i < maxLen; i++){
        if(i >= offset && i >= offsetIn){
            int inVal = hexToInt(input.value.at(i - offsetIn));
            int thisVal = hexToInt(value.at(i - offset));
            result += intToHex(inVal & thisVal);
        }
    }
    HexString retVal(result);
    return retVal;
}

HexString HexString::operator*(const HexString &input) {
    HexString hexOne("1");
    HexString count(input.value);
    if(equalsZero(count)){
        HexString retVal("0");
        return retVal;
    }
    HexString result(value);
    HexString increment(value);
    count = count - hexOne;
    while(!equalsZero(count)){
        result = result + increment;
        count = count - hexOne;
    }

    if (negative != input.negative) {
        HexString retVal("-" + result.value);
        return retVal;
    }
    HexString retVal(result);
    return retVal;
}

HexString HexString::operator+(const HexString &input) {
    if(negative != input.negative){
        HexString absInput(input.value);
        if(negative){
            HexString absThis(value);
            return absInput - absThis;
        } else {
            return *this - absInput;
        }
    }
    string result = "";
    int maxLen = max(value.length(),input.value.length());
    int offset = maxLen - value.length();
    int offsetIn = maxLen - input.value.length();
    int carry = 0;
    for(int i = maxLen - 1; i >= 0; i--){
        if(i < offset){
            if(carry == 1){
                int curVal = hexToInt(input.value.at(i)) + 1;
                carry = 0;
                if(curVal == 16){
                    carry = 1;
                    curVal = 0;
                }
                result = intToHex(curVal) + result;
            } else {
                result = input.value.at(i) + result;
            }
        } else if(i < offsetIn){
            if(carry == 1){
                int curVal = hexToInt(value.at(i)) + 1;
                carry = 0;
                if(curVal == 16){
                    carry = 1;
                    curVal = 0;
                }
                result = intToHex(curVal) + result;
            } else {
                result = value.at(i) + result;
            }
        } else{
            int inVal = hexToInt(input.value.at(i - offsetIn));
            int thisVal = hexToInt(value.at(i - offset));
            int sum = inVal + thisVal + carry;
            carry = 0;
            if(sum > 15){
                carry = 1;
                sum -= 16;
            }
            result = intToHex(sum) + result;
        }
    }
    if(carry == 1){
        result = "1" + result;
    }
    if(negative){
        result = "-" + result;
    }
    HexString retVal(result);
    return retVal;
}

HexString HexString::operator-(const HexString &input) {
    if(negative != input.negative){
        if(negative){
            HexString invInput("-" + input.value);
            return *this + invInput;
        } else{
            HexString invInput(input.value);
            return *this + invInput;
        }
    }
    if(biggerThan(input.value)){ //@TODO do a better check for which is bigger
        if(negative){
            HexString invInput(input.value);
            HexString invThis(value);
            return invInput - invThis;
        } else{
            HexString invInput("-" + input.value);
            HexString invThis("-" + value);
            return invInput - invThis;
        }
    }
    string result = "";
    int maxLen = max(value.length(),input.value.length());
    int offsetIn = maxLen - input.value.length();
    int borrow = 0;
    for(int i = maxLen - 1; i >= 0; i--){
        if(i < offsetIn){
            int thisVal = hexToInt(value.at(i));
            if(borrow == 1) {
                if (thisVal > 0) {
                    thisVal -= borrow;
                    borrow = 0;
                } else {
                    thisVal = 15;
                }
            }
            result = intToHex(thisVal) + result;
        } else{
            int inVal = hexToInt(input.value.at(i - offsetIn));
            int thisVal = hexToInt(value.at(i));
            if(borrow == 1) {
                if (thisVal > 0) {
                    thisVal -= borrow;
                    borrow = 0;
                } else {
                    thisVal = 15;
                }
            }
            if(inVal > thisVal){
                borrow = 1;
                thisVal += 16;
            }
            int dif = thisVal - inVal;
            result = intToHex(dif) + result;
        }
    }
    if(negative){
        result = "-" + result;
    }
    HexString retVal(result);
    return retVal;
}

HexString HexString::operator|(const HexString &input) {
    string result = "";
    int maxLen = max(value.length(),input.value.length());
    int offset = maxLen - value.length();
    int offsetIn = maxLen - input.value.length();

    for(int i = 0; i < maxLen; i++){
        if(i < offset){
            result += input.value.at(i);
        } else if(i < offsetIn){
            result += value.at(i);
        } else{
            int inVal = hexToInt(input.value.at(i - offsetIn));
            int thisVal = hexToInt(value.at(i - offset));
            result += intToHex(inVal | thisVal);
        }
    }
    HexString retVal(result);
    return retVal;
}

HexString HexString::operator^(const HexString &input) {
    HexString hexOne("1");
    HexString count(input.value);
    if(equalsZero(count)){
        HexString retVal("1");
        return retVal;
    }
    HexString result(value);
    HexString increment(value);
    count = count - hexOne;
    bool invert = true;
    while(!equalsZero(count)){
        result = result * increment;
        count = count - hexOne;
        invert = !invert;
    }

    if (negative && invert) {
        HexString retVal("-" + result.value);
        return retVal;
    }
    HexString retVal(result);
    return retVal;
}

string HexString::toString() {
    if(negative){
        return "-" + value;
    }
    return value;
}

char HexString::intToHex(const int &input) {
    return (input >= 10) ? ('A' + (input - 10)) : ('0' + input);
}

int HexString::hexToInt(const char &input) {
    return (input >= 'A') ? (input - 'A' + 10) : (input - '0');
}

bool HexString::equalsZero(const HexString &input) {
    for(int i = 0; i < input.value.length(); i++){
        if(input.value.at(i) != '0'){
            return false;
        }
    }
    return true;
}

bool HexString::biggerThan(string inValue) {
    return inValue.length() > value.length() || (inValue.length() == value.length() && inValue.at(0) > value.at(0));
}
