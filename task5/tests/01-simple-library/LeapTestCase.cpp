//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"
#include "Functions.h"
#include <gtest/gtest.h>

TEST(B, YEAR) {
    ASSERT_TRUE(IsLeap(400)); //4 100 400
    ASSERT_FALSE(IsLeap(600)); //4 100
    ASSERT_TRUE(IsLeap(256)); // 4
    ASSERT_TRUE(IsLeap(2020)); // 4
    ASSERT_TRUE(!(IsLeap(111))); // none
    ASSERT_THROW(IsLeap(-10), std::invalid_argument);
};

