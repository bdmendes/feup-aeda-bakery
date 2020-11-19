
#include "date_exception.h"

InvalidDate::InvalidDate(const std::string& completeDate) :
    std::logic_error(completeDate + " is not a valid date!"){
}
