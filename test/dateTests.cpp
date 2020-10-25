//
// Created by laimi on 25/10/2020.
//

#include <gtest/gtest.h>
#include "../src/model/date.h"

using testing::Eq;

bool validDate(Date d1){
    return(d1.testDate());
}

TEST(Date, valid_date){
    Date d1=Date();
    EXPECT_EQ(validDate(d1), true);
}