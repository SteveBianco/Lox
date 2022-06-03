#include "LiteralExpression.h"

LiteralExpression::LiteralExpression(const Token& token):
    token_{ token }
{
}

const LiteralValue& LiteralExpression::getValue() const
{
    // The optional should never be empty.
    return token_.getOptionalValue().value();
}

const Token& LiteralExpression::token() const
{
    return token_;
}

std::string LiteralExpression::to_string() const
{
    return token_;
}
