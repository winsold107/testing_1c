//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherMock.h"
#include <gtest/gtest.h>
#include "cpr/cpr.h"

TEST(C, WEATHER) {
    Weather w;
    w.SetApiKey("e5101e3fc7bdca4a626dcc38e2fa01f8");

    ASSERT_THROW(w.GetTemperature("ghghghg"), std::invalid_argument);
    ASSERT_NO_THROW(w.GetTemperature("London"));
};