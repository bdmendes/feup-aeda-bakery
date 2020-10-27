#include <iostream>

#include "model/person.h"


int main() {
    try {
        Date d1(29,02,2019,23,53);
    }
    catch(InvalidDate& e){
        std::cout << e.what();
        std::cout << "\ne chovem tchouriças, também";
    }
    return 0;
}

