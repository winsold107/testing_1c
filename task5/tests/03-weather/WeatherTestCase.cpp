//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"
#include <gtest/gtest.h>

TEST(D, WEATHER2) {
    Weather w;
    w.SetApiKey("e5101e3fc7bdca4a626dcc38e2fa01f8");
    ASSERT_EQ(w.GetDifferenceString("London", "Moscow"), "Weather in London is warmer than in Moscow by 8 degrees");
    ASSERT_EQ(w.GetDifferenceString("Moscow", "London"), "Weather in Moscow is colder than in London by 8 degrees");
};
