//
// Created by mhuels on 4/20/20.
//

#include "format.h"

//formatting strings

string surroundWithSeparator(string str, int length, int numberOfLines, char sign, bool spaces){
    if(spaces){
        str.insert(0, " ");
        str.append(" ");
    }
    int innerLength = str.size();
    int linesBefore = numberOfLines / 2;
    int linesAfter = numberOfLines - linesBefore - 1;
    string new_str;
    for(int i = 0; i < linesBefore; i++){
        new_str.append(length, sign);
        new_str.append("\n");
    }
    if(innerLength < length){
        int leftLength = (length - innerLength) / 2;
        int rightLength = length - leftLength - innerLength;
        new_str.append(leftLength, sign);
        new_str.append(str);
        new_str.append(rightLength, sign);
    }
    else{
        new_str.append(str);
    }
    for(int i = 0; i < linesAfter; i++){
        new_str.append("\n");
        new_str.append(length, sign);
    }
    return new_str;
}