//
// Created by laimi on 25/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/date.h"

using testing::Eq;

TEST(Date, valid_date){
    //Date d1(23,53,29,02,2019);
    EXPECT_THROW(Date d1(23,53,29,02,2019),InvalidDate);
}