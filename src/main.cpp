#include <iostream>

#include "model/person.h"
#include <stdexcept>

int main() {
    //Date d1(29,02,2019,23,53);
    try {
        Date d1(29,02,2019,23,53);
    }
    catch(const std::runtime_error& e){
        std::cout << "chovem tchouriças, também";
    }
    return 0;
}
