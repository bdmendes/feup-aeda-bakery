#include <iostream>

#include "model/person/person/person.h"
#include "model/person/worker/worker.h"
#include "model/store/store.h"
#include <stdexcept>
#include <algorithm>
#include <vector>


int main() {
    Store s;
    s.clientManager.add("João Malheiro",123342);
    s.clientManager.add("Álvaro",23432);
    s.clientManager.write(std::cout);
}
