#include "LiteralExpression.h"

std::string LiteralExpression::to_string() const
{
    if (std::holds_alternative<std::string>(value_))
    {
        return std::get<std::string>(value_);
    }

    if (std::holds_alternative<double>(value_))
    {
        double x = std::get<double>(value_);
        return std::to_string(x);
    }

    return std::string();
}
