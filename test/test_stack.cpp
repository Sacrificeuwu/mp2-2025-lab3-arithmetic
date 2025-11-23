#include "stack.h"
#include <gtest.h>

TEST(TStack, ConstructorCreatesEmptyStack) {
    TStack<int> stack;
    EXPECT_EQ(stack.size(), 0);
}

TEST(TStack, ThrowsExceptionForInvalidSize) {
    ASSERT_ANY_THROW(TStack<int>(-1));
}

TEST(TStack, IsEmptyReturnsFalseAfterPush) {
    TStack<int> stack;
    stack.push(10);
    EXPECT_FALSE(stack.isEmpty());
}

TEST(TStack, IsEmptyReturnsTrueAfterPushAndPop) {
    TStack<int> stack;
    stack.push(10);
    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

TEST(TStack, PushIncreasesSize) {
    TStack<int> stack;
    stack.push(10);
    EXPECT_EQ(stack.size(), 1);
}

TEST(TStack, PushAddsCorrectValue) {
    TStack<int> stack;
    stack.push(1);
    EXPECT_EQ(stack.seeLast(), 1);
}

TEST(TStack, PushThrowsExceptionWhenFull) {
    TStack<int> stack(2);
    stack.push(1);
    stack.push(2);
    ASSERT_ANY_THROW(stack.push(3));
}

TEST(TStack, PopDecreasesSize) {
    TStack<int> stack(2);
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}

TEST(TStack, PopReturnsCorrectValue) {
    TStack<int> stack(2);
    stack.push(1);
    EXPECT_EQ(stack.pop(), 1);
}

TEST(TStack, PopThrowsExceptionWhenEmpty) {
    TStack<int> stack(2);
    ASSERT_ANY_THROW(stack.pop());
}
TEST(TStack, SeeLastReturnsTopElement) {
    TStack<int> stack;
    stack.push(10);
    stack.push(10);
    stack.seeLast();
    EXPECT_EQ(stack.size(), 2);
}
TEST(TStack, SeeLastThrowsExceptionWhenEmpty) {
    TStack<int> stack;
    ASSERT_ANY_THROW(stack.seeLast());
}

TEST(TStack, ClearMakesStackEmpty) {
    TStack<int> stack;
    stack.push(1);
    stack.push(1);
    stack.push(1);
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
}

