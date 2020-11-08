//
// Created by laimi on 25/10/2020.
//

#include <gtest/gtest.h>
#include "model/date/date.h"

using testing::Eq;

TEST(Date, create_date){
    EXPECT_THROW(Date d1(29,02,2019,23,53),InvalidDate);
    EXPECT_THROW(Date d2(29,05,2020,23,60), InvalidDate);
}

TEST(Date, is_leap_year){
    EXPECT_EQ(true, Date::isLeapYear(2008));
    EXPECT_EQ(true, Date::isLeapYear(2020));

    EXPECT_EQ(false, Date::isLeapYear(2003));
    EXPECT_EQ(false, Date::isLeapYear(2017));
}

TEST(Date, get_Calendar_Day){
    Date d1(12, 3,1998);
    Date d2 (28, 12, 2006);

    EXPECT_EQ("12/03/1998", d1.getCalendarDay());
    EXPECT_EQ("28/12/2006", d2.getCalendarDay());
}

TEST(Date, get_Clock_Time){
    Date d1(29,9,2001, 13, 57);
    Date d2 (24, 4, 2001, 2, 34);

    EXPECT_EQ("13:57", d1.getClockTime());
    EXPECT_EQ("02:34", d2.getClockTime());
}

TEST(Date, get_complete_date){
    Date d1(21, 10, 1976, 18, 21);
    Date d2(21, 6, 1972, 9, 39);

    EXPECT_EQ("21/10/1976 18:21", d1.getCompleteDate());
    EXPECT_EQ("21/06/1972 09:39", d2.getCompleteDate());
}

TEST(Date, operator_equal){
    Date d1(9, 6, 2001, 10, 51);
    Date d2(9, 6, 2001, 10, 51);
    Date d3(9, 10, 2001, 10, 51);

    EXPECT_TRUE(d1==d2);
    EXPECT_TRUE(d2==d1);

    EXPECT_FALSE(d1==d3);
    EXPECT_FALSE(d2==d3);
}