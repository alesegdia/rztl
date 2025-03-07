#include <gtest/gtest.h>
#include "rztl/vec.h"

namespace rztl {

    TEST(Vec2Test, DefaultConstructor) {
        Vec2i v;
        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 0);
    }

    TEST(Vec2Test, ParameterizedConstructor) {
        Vec2i v(3, 4);
        EXPECT_EQ(v.GetX(), 3);
        EXPECT_EQ(v.GetY(), 4);
    }

    TEST(Vec2Test, CopyConstructor) {
        Vec2i v1(3, 4);
        Vec2i v2(v1);
        EXPECT_EQ(v2.GetX(), 3);
        EXPECT_EQ(v2.GetY(), 4);
    }

    TEST(Vec2Test, EuclideanDistance) {
        Vec2i v1(3, 4);
        Vec2i v2(0, 0);
        EXPECT_FLOAT_EQ(Vec2i::EuclideanDistance(v1, v2), 5.0);
    }

    TEST(Vec2Test, ManhattanDistance) {
        Vec2i v1(3, 4);
        Vec2i v2(0, 0);
        EXPECT_EQ(Vec2i::ManhattanDistance(v1, v2), 7);
    }

    TEST(Vec2Test, SetX) {
        Vec2i v;
        v.SetX(5);
        EXPECT_EQ(v.GetX(), 5);
    }

    TEST(Vec2Test, SetY) {
        Vec2i v;
        v.SetY(6);
        EXPECT_EQ(v.GetY(), 6);
    }

    TEST(Vec2Test, Set) {
        Vec2i v;
        v.Set(7, 8);
        EXPECT_EQ(v.GetX(), 7);
        EXPECT_EQ(v.GetY(), 8);
    }

    TEST(Vec2Test, Translate) {
        Vec2i v1(1, 2);
        Vec2i v2(3, 4);
        v1.Translate(v2);
        EXPECT_EQ(v1.GetX(), 4);
        EXPECT_EQ(v1.GetY(), 6);
    }

    TEST(Vec2Test, AdditionOperator) {
        Vec2i v1(1, 2);
        Vec2i v2(3, 4);
        Vec2i v3 = v1 + v2;
        EXPECT_EQ(v3.GetX(), 4);
        EXPECT_EQ(v3.GetY(), 6);
    }

    TEST(Vec2Test, SubtractionOperator) {
        Vec2i v1(5, 6);
        Vec2i v2(3, 4);
        Vec2i v3 = v1 - v2;
        EXPECT_EQ(v3.GetX(), 2);
        EXPECT_EQ(v3.GetY(), 2);
    }

    TEST(Vec2Test, DivisionOperator) {
        Vec2i v1(6, 8);
        Vec2i v2 = v1 / 2;
        EXPECT_EQ(v2.GetX(), 3);
        EXPECT_EQ(v2.GetY(), 4);
    }

    TEST(Vec2Test, MultiplicationOperator) {
        Vec2i v1(2, 3);
        Vec2i v2 = v1 * 2;
        EXPECT_EQ(v2.GetX(), 4);
        EXPECT_EQ(v2.GetY(), 6);
    }

    TEST(Vec2Test, EqualityOperator) {
        Vec2i v1(2, 3);
        Vec2i v2(2, 3);
        EXPECT_TRUE(v1 == v2);
    }

    TEST(Vec2Test, InequalityOperator) {
        Vec2i v1(2, 3);
        Vec2i v2(3, 4);
        EXPECT_TRUE(v1 != v2);
    }

    TEST(Vec2Test, ZeroVec) {
        Vec2i v = Vec2i::ZeroVec();
        EXPECT_EQ(v.GetX(), 0);
        EXPECT_EQ(v.GetY(), 0);
    }

    TEST(Vec2Test, SquaredModulus) {
        Vec2i v(3, 4);
        EXPECT_EQ(v.SquaredModulus(), 7);
    }

} // namespace rztl