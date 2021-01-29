#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Soundex.h"

using namespace testing;

class test_fixture : public Test 
{
public:
    Soundex snd;
};

TEST_F(test_fixture, code_for_empty_string_is_empty_string) {
    ASSERT_THAT(snd.encode(""), Eq(""));
}

TEST_F(test_fixture, code_for_single_char_is_char_following_000) {
    ASSERT_THAT(snd.encode("r"), Eq("R000"));
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_without_vowels) {
    ASSERT_THAT(snd.encode("zbgdlmr"), Eq("Z123"));
}

TEST_F(test_fixture, code_for_simple_not_repeteative_chars_with_code_len_smaller_than_4) {
    ASSERT_THAT(snd.encode("zb"), Eq("Z100"));
}

TEST_F(test_fixture, code_for_word_contians_vowels_and_yhw) {
    ASSERT_THAT(snd.encode("Tymczak"), Eq("T522"));
}

TEST_F(test_fixture, code_for_word_contians_same_consequtive_numbers) {
    ASSERT_THAT(snd.encode("Matthew"), Eq("M300"));
}

TEST_F(test_fixture, code_for_word_first_char_number_repeated) {
    ASSERT_THAT(snd.encode("Tdmczak"), Eq("T522"));
}

TEST_F(test_fixture, code_for_word_mixed_upper_and_lower_chars) {
    ASSERT_THAT(snd.encode("TWdMcZAk"), Eq("T522"));
}

TEST_F(test_fixture, code_for_test_word_1) {
    ASSERT_THAT(snd.encode("Honeyman"), Eq("H555"));
}

TEST_F(test_fixture, code_for_test_word_2) {
    ASSERT_THAT(snd.encode("Pfister"), Eq("P236"));
}
