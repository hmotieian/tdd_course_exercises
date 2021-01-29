#include "gtest/gtest.h"
#include "Soundex.h"

class test_fixture : public testing::Test 
{
public:
    Soundex snd;
};

TEST_F(test_fixture, code_for_empty_string_is_empty_string) {
    ASSERT_EQ(snd.encode(""), "");
}

TEST_F(test_fixture, code_for_single_char_is_char_following_000) {
    ASSERT_EQ(snd.encode("r"), "R000");
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_without_vowels) {
    ASSERT_EQ(snd.encode("zbgdlmr"), "Z123");
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_with_code_len_smaller_than_4) {
    ASSERT_EQ(snd.encode("zb"), "Z100");
}

TEST_F(test_fixture, code_for_word_contians_vowels_and_yhw) {
    ASSERT_EQ(snd.encode("Tymczak"), "T522");
}

TEST_F(test_fixture, code_for_word_contians_same_consequtive_numbers) {
    ASSERT_EQ(snd.encode("Matthew"), "M300");
}

TEST_F(test_fixture, code_for_word_first_char_number_repeated) {
    ASSERT_EQ(snd.encode("Tdmczak"), "T522");
}

TEST_F(test_fixture, code_for_word_mixed_upper_and_lower_chars) {
    ASSERT_EQ(snd.encode("TWdMcZAk"), "T522");
}

TEST_F(test_fixture, code_for_test_word_1) {
    ASSERT_EQ(snd.encode("Honeyman"), "H555");
}

TEST_F(test_fixture, code_for_test_word_2) {
    ASSERT_EQ(snd.encode("Pfister"), "P236");
}
