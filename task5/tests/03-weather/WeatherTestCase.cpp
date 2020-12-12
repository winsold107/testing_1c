//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"
#include <gtest/gtest.h>

cpr::Response res(int status, std::string text) {
    cpr::Response res;
    res.status_code = status;
    if (text == "") {
        return res;
    }
    res.text = text;
    return res;
}

TEST_F(WeatherTestCase, WEATHER) {
    ASSERT_NO_THROW(w->SetApiKey("key"));

    cpr::Response res1;
    res1.status_code = 404;
    EXPECT_CALL(*w, Get("qwerty")).WillOnce(testing::Return(res1));
    ASSERT_THROW(w->GetResponseForCity("qwerty"),std::invalid_argument);

    cpr::Response res2;
    res2.status_code = 200;
    res2.text = "{\"list\" : [{\"main\": {\"temp\": 10}}]}";
    EXPECT_CALL(*w, Get("London")).WillRepeatedly(testing::Return(res2));
    ASSERT_EQ(w->GetTemperature("London"), 10);

    cpr::Response res3;
    res3.status_code = 200;
    res3.text = "{\"list\" : [{\"main\": {\"temp\": 20}}]}";
    EXPECT_CALL(*w, Get("Moscow")).WillRepeatedly(testing::Return(res3));
    ASSERT_EQ(w->GetDifferenceString("London", "Moscow"), "Weather in London is colder than in Moscow by 10 degrees");
    ASSERT_EQ(w->GetDifferenceString("Moscow", "London"), "Weather in Moscow is warmer than in London by 10 degrees");
};
