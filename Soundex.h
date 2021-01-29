#pragma once 

#include <numeric>
#include <set>
#include <string>
#include <map>

using namespace std;

class Soundex
{
public:
    Soundex();
    string encode(string word);

private:
    map<char, char> codeMap;
    void zeroPad(string& code); // for code length below 4
};