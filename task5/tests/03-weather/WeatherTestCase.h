
#pragma once

#include <gtest/gtest.h>
#include "WeatherMock.h"
#include "cpr/cpr.h"

class WeatherTestCase : public ::testing::Test {
public:
    WeatherMock* w;
    void SetUp() {
        w = new WeatherMock;
    }

    void TearDown() {
        delete w;
    }
};



