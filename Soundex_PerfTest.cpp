#include "gtest/gtest.h"
#include "Soundex.h"
#include <chrono>

class test_perf_fixture : public testing::Test 
{
public:
    Soundex snd;
    
    void generateLongWord(string& longWord) {
        longWord = "PfisterEND";
        auto j = longWord.length();
        for (size_t i = 0; i < 10; i++, j *= 2)
            longWord += longWord;
        EXPECT_EQ(longWord.length(), j);
    }
};

TEST_F(test_perf_fixture, code_for_code_long_word_less_than_3msec) {
    string longWord;
    generateLongWord(longWord);
    
    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();
    
    ASSERT_EQ(snd.encode(longWord), "P236");
    
    duration<double> dt = duration_cast<duration<double>>(high_resolution_clock::now() - t0);
    // std::cout << ">> longWord length= " << j << ", Exec Time= " << static_cast<double>(dt.count()) << std::endl;
    EXPECT_TRUE(dt.count() <= 0.003);
};
