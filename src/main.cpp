#include <iostream>
#include <model/date/date.h>

int main() {
  Date d;
  d.addMinutes(64);
  std::cout << d.getCompleteDate();
}
