#include <gtest/gtest.h>
#include "rztl/Matrix2D.h"

namespace rztl {

    TEST(Matrix2DTest, ParameterizedConstructor) {
        Matrix2D<int> matrix(3, 4);
        EXPECT_EQ(matrix.GetRowsNumber(), 4);
        EXPECT_EQ(matrix.GetColsNumber(), 3);
    }

    TEST(Matrix2DTest, SetAndGetElement) {
        Matrix2D<int> matrix(3, 4);
        matrix.SetCell(1, 2, 5);
        EXPECT_EQ(matrix.GetCell(1, 2), 5);
    }

    TEST(Matrix2DTest, Resize) {
        Matrix2D<int> matrix(3, 4);
        matrix.Resize(5, 6);
        EXPECT_EQ(matrix.GetRowsNumber(), 6);
        EXPECT_EQ(matrix.GetColsNumber(), 5);
    }

    TEST(Matrix2DTest, Fill) {
        Matrix2D<int> matrix(3, 4);
        matrix.FillCells(7);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_EQ(matrix.GetCell(i, j), 7);
            }
        }
    }

    TEST(Matrix2DTest, CopyConstructor) {
        Matrix2D<int> matrix1(3, 4);
        matrix1.FillCells(7);
        Matrix2D<int> matrix2(matrix1);
        EXPECT_EQ(matrix2.GetRowsNumber(), 4);
        EXPECT_EQ(matrix2.GetColsNumber(), 3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_EQ(matrix2.GetCell(i, j), 7);
            }
        }
    }

    TEST(Matrix2DTest, AssignmentOperator) {
        Matrix2D<int> matrix1(3, 4);
        matrix1.FillCells(7);
        Matrix2D<int> matrix2(3, 4);
        matrix2 = matrix1;
        EXPECT_EQ(matrix2.GetRowsNumber(), 4);
        EXPECT_EQ(matrix2.GetColsNumber(), 3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                EXPECT_EQ(matrix2.GetCell(i, j), 7);
            }
        }
    }



} // namespace rztl