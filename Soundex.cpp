#include "gtest/gtest.h"
#include <numeric>
#include <set>
#include <string>
#include <chrono>

using namespace std;

class Soundex
{
public:
    string code(string word)
    {
        if (word.length() == 0)
            return "";
        string code { static_cast<char>(toupper(static_cast<char>(word[0]))) };
        // word.erase(0, 1);
        char cprev(0), cnew(0);
        int i = 0;
        for (auto ch : word) {
            ch = tolower(ch);
            if (set<char>{'b', 'f', 'p', 'v'}.count(ch) > 0U)
                cnew = '1';
            else if (set<char>{'c', 'g', 'j', 'k', 'q', 's', 'x', 'z'}.count(ch) > 0U)
                cnew = '2';
            else if (ch == 'd' || ch == 't')
                cnew = '3';
            else if (ch == 'l')
                cnew = '4';
            else if (ch == 'm' || ch == 'n')
                cnew = '5';
            else if (ch == 'r')
                cnew = '6';
            else if (set<char>{'a', 'e', 'i', 'o', 'u', 'y'}.count(ch) > 0U)
                cnew = 0;
            if (i++ && cnew) {
                if (cnew != cprev) {
                    code += cnew;
                    if (code.length() == 4)
                        break;
                }
            }
            cprev = cnew;
        }
        // limit size
        if (code.length() < 4) {
            for (int i = code.length(); i < 4; i++)
                code += '0';
        }
        return code;
    }
};

class test_fixture : public testing::Test 
{
public:
    Soundex snd;
};

TEST_F(test_fixture, code_for_code_long_word_less_than_3msec) {
    string longWord = "PfisterEND";
    auto j = longWord.length();
    for (size_t i = 0; i < 10; i++, j *= 2)
        longWord += longWord;
    ASSERT_EQ(longWord.length(), j);
    // Execution Time measurement
    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();
    ASSERT_EQ(snd.code(longWord), "P236");
    duration<double> dt = duration_cast<duration<double>>(high_resolution_clock::now() - t0);
    std::cout << ">> longWord length= " << j << ", Exec Time= " << static_cast<double>(dt.count()) << std::endl;
    ASSERT_TRUE(dt.count() <= 0.003);
}

TEST_F(test_fixture, code_for_test_word_2) {
    ASSERT_EQ(snd.code("Pfister"), "P236");
}

TEST_F(test_fixture, code_for_test_word_1) {
    ASSERT_EQ(snd.code("Honeyman"), "H555");
}

TEST_F(test_fixture, code_for_word_mixed_upper_and_lower_chars) {
    ASSERT_EQ(snd.code("TWdMcZAk"), "T522");
}

TEST_F(test_fixture, code_for_word_first_char_number_repeated) {
    ASSERT_EQ(snd.code("Tdmczak"), "T522");
}

TEST_F(test_fixture, code_for_word_contians_same_consequtive_numbers) {
    ASSERT_EQ(snd.code("Matthew"), "M300");
}

TEST_F(test_fixture, code_for_word_contians_vowels_and_yhw) {
    ASSERT_EQ(snd.code("Tymczak"), "T522");
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_with_code_len_smaller_than_4) {
    ASSERT_EQ(snd.code("zb"), "Z100");
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_without_vowels) {
    ASSERT_EQ(snd.code("zbgdlmr"), "Z123");
}

TEST_F(test_fixture, code_for_single_char_is_char_following_000) {
    ASSERT_EQ(snd.code("r"), "R000");
}

TEST_F(test_fixture, code_for_empty_string_is_empty_string) {
    ASSERT_EQ(snd.code(""), "");
}
