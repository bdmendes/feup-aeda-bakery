
#ifndef FEUP_AEDA_PROJECT_DATE_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_DATE_EXCEPTIONS_H

#include <stdexcept>
#include "model/date/date.h"

/**
 * Class relative to the exception of an invalid date.
 */
class InvalidDate : public std::logic_error{
public:
    /**
     * Creates a new InvalidDate exception object.
     *
     * @param completeDate the complete date
     */
    explicit InvalidDate(const std::string& completeDate);
};

#endif //FEUP_AEDA_PROJECT_DATE_EXCEPTIONS_H
