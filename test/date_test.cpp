//
// Created by laimi on 25/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/date.h"

using testing::Eq;

TEST(Date, valid_date){
    EXPECT_THROW(Date d1(29,02,2019,23,53),InvalidDate);
    Date d1(29,02,2020,23,53);
}
