#include <gtest.h>
#include "arithmetic.h"

TEST(TArifmeticExpression, ConstructorValidExpression) {
    EXPECT_NO_THROW(TArifmeticExpression expr("a+b"));
}

TEST(TArifmeticExpression, ConstructorEmptyExpression) {
    ASSERT_ANY_THROW(TArifmeticExpression expr(""));
}

TEST(TArifmeticExpression, SetExpressionValid) {
    TArifmeticExpression expr("a+b");
    EXPECT_NO_THROW(expr.setExpression("c*d"));
}

TEST(TArifmeticExpression, SetExpressionEmpty) {
    TArifmeticExpression expr("a+b");
    ASSERT_ANY_THROW(expr.setExpression(""));
}

TEST(TArifmeticExpression, ToLexemsValidExpression) {
    TArifmeticExpression expr("a + b * (c - d)");
    EXPECT_NO_THROW(expr.toLexems());
}

TEST(TArifmeticExpression, ToLexemsInvalidCharacters) {
    TArifmeticExpression expr("a + b & c");
    ASSERT_ANY_THROW(expr.toLexems());
}

TEST(TArifmeticExpression, ToPostfixSimpleExpression) {
    TArifmeticExpression expr("a+b");
    EXPECT_NO_THROW(expr.toPostfix());

}

TEST(TArifmeticExpression, ToPostfixComplexExpression) {
    TArifmeticExpression expr("a+b*c");
    expr.toPostfix();
    EXPECT_EQ(expr.getPostfix(), "a b c * +");
}

TEST(TArifmeticExpression, ToPostfixMismatchedParentheses) {
    TArifmeticExpression expr;
    ASSERT_ANY_THROW(expr.setExpression("a+b)"));
}

TEST(TArifmeticExpression, SetValueInvalidVariable) {
    TArifmeticExpression expr("a+b");
    ASSERT_ANY_THROW(expr.setValue("1", 5.0));
}

TEST(TArifmeticExpression, CalculateSimpleAddition) {
    TArifmeticExpression expr("a+b");
    expr.setValue("a", 5);
    expr.setValue("b", 3);
    expr.toPostfix();

    int result = expr.calculate();
    EXPECT_EQ(result, 8); 
}

TEST(TArifmeticExpression, GetInfixReturnsCorrectValue) {
    std::string str = "a+b*c";
    TArifmeticExpression expr(str);
    EXPECT_EQ(expr.getInfix(), str);
}

TEST(TArifmeticExpression, GetPostfixWithoutConversion) {
    TArifmeticExpression expr("a+b");
    EXPECT_ANY_THROW(expr.getPostfix());
}

