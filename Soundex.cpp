#include "Soundex.h"

Soundex::Soundex()
{
    // Generate Soundex Mapping
    for (auto ch : {'b', 'f', 'p', 'v'})
        codeMap[ch] = '1';
    for (auto ch : {'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'})
        codeMap[ch] = '2';
    for (auto ch : {'d', 't'})
        codeMap[ch] = '3';
    codeMap['l'] = '4';
    for (auto ch : {'m', 'n'})
        codeMap[ch] = '5';
    codeMap['r'] = '6';
    for (auto ch : {'a', 'e', 'i', 'o', 'u', 'y'})
        codeMap[ch] = 0;
};

string Soundex::encode(string word)
{
    if (word.length() == 0)
        return "";
    string code{static_cast<char>(toupper(word.front()))};
    
    char cprev(0), cnew(0);
    bool first = true;
    for (auto ch : word)
    {
        ch = tolower(ch);
        auto it = codeMap.find(ch);
        if (it != codeMap.end())
            cnew = it->second;
        if (!first && cnew)
        {
            if (cnew != cprev)
            {
                code += cnew;
                if (code.length() == 4)
                    break;
            }
        }
        cprev = cnew;
        first = false;
    }
    
    zeroPad(code);

    return code;
};

void Soundex::zeroPad(string& code)
{
    for (int i = code.length(); i < 4; i++)
        code += '0';
};