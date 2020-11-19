//
// Created by up201906166 on 23/10/2020.
//

#include "store_exception.h"

StoreHasNoWorkers::StoreHasNoWorkers() :
    std::logic_error("This store has no workers!"){
}