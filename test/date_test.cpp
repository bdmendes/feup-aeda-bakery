
#include <gtest/gtest.h>
#include "model/date/date.h"

using testing::Eq;

TEST(Date, create_date){
    EXPECT_THROW(Date date1(29,02,2019,23,53),InvalidDate);
    EXPECT_THROW(Date date2(29,05,2020,23,60), InvalidDate);
}

TEST(Date, is_leap_year){
    EXPECT_EQ(true, Date::isLeapYear(2008));
    EXPECT_EQ(true, Date::isLeapYear(2020));

    EXPECT_EQ(false, Date::isLeapYear(2003));
    EXPECT_EQ(false, Date::isLeapYear(2017));
}

TEST(Date, get_Calendar_Day){
    Date date1(12, 3,1998);
    Date date2(28, 12, 2006);

    EXPECT_EQ("12/03/1998", date1.getCalendarDay());
    EXPECT_EQ("28/12/2006", date2.getCalendarDay());
}

TEST(Date, get_Clock_Time){
    Date date1(29,9,2001, 13, 57);
    Date date2 (24, 4, 2001, 2, 34);

    EXPECT_EQ("13:57", date1.getClockTime());
    EXPECT_EQ("02:34", date2.getClockTime());
}

TEST(Date, get_complete_date){
    Date date1(21, 10, 1976, 18, 21);
    Date date2(21, 6, 1972, 9, 39);

    EXPECT_EQ("21/10/1976 18:21", date1.getCompleteDate());
    EXPECT_EQ("21/06/1972 09:39", date2.getCompleteDate());
}

TEST(Date, add_days){
    Date date1(28, 12, 2012, 13, 24);
    Date date2(28, 2, 2001, 9, 47);

    EXPECT_EQ(28, date1.getDay());

    date1.addDays(4);

    EXPECT_EQ("01/01/2013 13:24", date1.getCompleteDate());
    EXPECT_EQ(28, date2.getDay());

    date2.addDays(7);

    EXPECT_EQ("07/03/2001 09:47", date2.getCompleteDate());
}

TEST(Date, add_minutes){
    Date date1(17, 3, 1986, 14, 54);
    Date date2(24, 7, 1989,  23, 43);

    EXPECT_EQ(54, date1.getMinute());

    date1.addMinutes(26);

    EXPECT_EQ("17/03/1986 15:20", date1.getCompleteDate());
    EXPECT_EQ(43, date2.getMinute());

    date2.addMinutes(77);

    EXPECT_EQ("25/07/1989 01:00", date2.getCompleteDate());
}

TEST(Date, equal_dates){
    Date date1(9, 6, 2001, 10, 51);
    Date date2(9, 6, 2001, 10, 51);
    Date date3(9, 10, 2001, 10, 51);

    EXPECT_TRUE(date1==date2);
    EXPECT_TRUE(date2==date1);
    EXPECT_FALSE(date1==date3);
    EXPECT_FALSE(date2==date3);
}

TEST(Date, earlier_date){
    Date date1(14, 5, 1874, 11, 23);
    Date date2(14, 5, 1874, 11, 24);
    Date date3(14, 5, 1873, 23, 45);
    Date date4(14, 5, 1873, 0, 0);

    EXPECT_TRUE(date1 < date2);
    EXPECT_TRUE(date3 < date1);
    EXPECT_TRUE(date4 < date3);
    EXPECT_FALSE(date2 < date3);
}