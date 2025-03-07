#include <gtest/gtest.h>
#include "rztl/rect.h"

namespace rztl {

    // Test default constructor
    TEST(RectTest, DefaultConstructor) {
        Rect<int> rect;
        EXPECT_EQ(rect.GetX(), 0);
        EXPECT_EQ(rect.GetY(), 0);
        EXPECT_EQ(rect.GetWidth(), 0);
        EXPECT_EQ(rect.GetHeight(), 0);
    }

    // Test parameterized constructor
    TEST(RectTest, ParameterizedConstructor) {
        Rect<int> rect(10, 20, 30, 40);
        EXPECT_EQ(rect.GetX(), 10);
        EXPECT_EQ(rect.GetY(), 20);
        EXPECT_EQ(rect.GetWidth(), 30);
        EXPECT_EQ(rect.GetHeight(), 40);
    }

    // Test copy constructor
    TEST(RectTest, CopyConstructor) {
        Rect<int> rect1(10, 20, 30, 40);
        Rect<int> rect2(rect1);
        EXPECT_EQ(rect2.GetX(), 10);
        EXPECT_EQ(rect2.GetY(), 20);
        EXPECT_EQ(rect2.GetWidth(), 30);
        EXPECT_EQ(rect2.GetHeight(), 40);
    }

    // Test assignment operator
    TEST(RectTest, AssignmentOperator) {
        Rect<int> rect1(10, 20, 30, 40);
        Rect<int> rect2;
        rect2 = rect1;
        EXPECT_EQ(rect2.GetX(), 10);
        EXPECT_EQ(rect2.GetY(), 20);
        EXPECT_EQ(rect2.GetWidth(), 30);
        EXPECT_EQ(rect2.GetHeight(), 40);
    }

    // Test getters and setters
    TEST(RectTest, GettersAndSetters) {
        Rect<int> rect;
        rect.SetX(10);
        rect.SetY(20);
        rect.SetWidth(30);
        rect.SetHeight(40);
        EXPECT_EQ(rect.GetX(), 10);
        EXPECT_EQ(rect.GetY(), 20);
        EXPECT_EQ(rect.GetWidth(), 30);
        EXPECT_EQ(rect.GetHeight(), 40);
    }

    // Test Area method
    TEST(RectTest, Area) {
        Rect<int> rect(10, 20, 30, 40);
        EXPECT_EQ(rect.Area(), 30 * 40);
    }

    // Test Contains method
    TEST(RectTest, Contains) {
        Rect<int> rect(10, 20, 30, 40);
        EXPECT_TRUE(rect.Contains(15, 25));
        EXPECT_FALSE(rect.Contains(5, 25));
        EXPECT_FALSE(rect.Contains(15, 65));
    }

    // Test Intersects method
    TEST(RectTest, Intersects) {
        Rect<int> rect1(10, 20, 30, 40);
        Rect<int> rect2(20, 30, 30, 40);
        Rect<int> rect3(50, 70, 30, 40);
        EXPECT_TRUE(rect1.Intersects(rect2));
        EXPECT_FALSE(rect1.Intersects(rect3));
    }

    // Test Depth method
    TEST(RectTest, Depth) {
        Rect<int> rect1(10, 20, 30, 40);
        Rect<int> rect2(15, 25, 10, 10);
        int leftDepth, rightDepth, topDepth, bottomDepth;
        rect1.Depth(rect2, leftDepth, rightDepth, topDepth, bottomDepth);
        EXPECT_EQ(leftDepth, 5);
        EXPECT_EQ(rightDepth, 15);
        EXPECT_EQ(topDepth, 5);
        EXPECT_EQ(bottomDepth, 15);

        Rect<int> rect3(5, 15, 10, 10);
        rect1.Depth(rect3, leftDepth, rightDepth, topDepth, bottomDepth);
        EXPECT_EQ(leftDepth, -5);
        EXPECT_EQ(rightDepth, 25); // Corrected from 30 to 25
        EXPECT_EQ(topDepth, -5);
        EXPECT_EQ(bottomDepth, 45);
    }

} // namespace rztl