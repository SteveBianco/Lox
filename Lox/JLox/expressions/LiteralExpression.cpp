#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(const Token& token):
    token_{ token }
{
}

const Token& LiteralExpression::token() const
{
    return token_;
}

std::string LiteralExpression::to_string() const
{
    return token_;
}
