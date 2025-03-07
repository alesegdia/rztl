#pragma once

#include <initializer_list>
#include <vector>
#include <iostream>
#include <memory>
#include <iomanip>
#include <cassert>

#include "vec.h"

namespace rztl {


template <typename T>
class Matrix2D
{
public:

    typedef std::shared_ptr<Matrix2D<T>> SharedPtr;

    Matrix2D( size_t cols, size_t rows ) {
        Resize(cols, rows);
    }

    Matrix2D( size_t cols, size_t rows, T fill_value )
    {
        Resize(cols, rows);
        FillCells(fill_value);
    }

    Matrix2D( const Matrix2D<int>& other )
        : m_cols(other.GetColsNumber()),
          m_rows(other.GetRowsNumber()),
          m_data(other.m_data)
    {

    }

    Matrix2D( size_t cols, size_t rows, std::initializer_list<T> il )
        : m_cols(cols),
          m_rows(rows),
          m_data(il)
    {

    }

	Matrix2D(const std::vector<T>& data, size_t cols, size_t rows)
		: m_cols(cols)
		, m_rows(rows)
		, m_data(data)
	{
		assert(data.size() == cols * rows);
	}

	Matrix2D(const std::vector<std::vector<T>>& data)
	{
		m_rows = data.size();
		m_cols = data[0].size();
		m_data.reserve(m_rows * m_cols);
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				m_data.push_back(data[i][j]);
			}
		}

		// check that all rows have the same size
		for (size_t i = 1; i < m_rows; i++)
		{
			assert(data[i].size() == m_cols);
		}
	}

    inline void SetCell( size_t col, size_t row, T value )
    {
        assert(col >= 0 && col < m_cols);
        assert(row >= 0 && row < m_rows);
        m_data[CoordToIndex(col, row)] = value;
    }

    inline T GetCell( size_t col, size_t row ) const
    {
        return m_data[CoordToIndex(col, row)];
    }

	inline const T& GetCellConstRef(size_t col, size_t row) const
	{
		return m_data[CoordToIndex(col, row)];
	}

    inline T& GetCell( size_t col, size_t row )
    {
        return m_data[CoordToIndex(col, row)];
    }

	size_t GetColsNumber() const
	{
		return m_cols;
	}

	size_t GetRowsNumber() const
	{
		return m_rows;
	}

	int GetColsNumberInt() const
	{
		return int(m_cols);
	}

	int GetRowsNumberInt() const
	{
		return int(m_rows);
	}

    void FillCells( T fill_value )
    {
        std::fill(m_data.begin(), m_data.end(), fill_value);
    }

    void FillCells( size_t x1, size_t y1, size_t x2, size_t y2, T fill_value)
    {
        assert(x1 < m_cols && x2 < m_cols);
        assert(y1 < m_rows && y2 < m_rows);

        for( size_t yy1 = y1; yy1 <= y2; yy1++ )
        {
            for( size_t xx1 = x1; xx1 <= x2; xx1++ )
            {
                SetCell(xx1, yy1, fill_value);
            }
        }
    }

    void Resize( size_t cols, size_t rows )
    {
        m_cols = cols;
        m_rows = rows;

        m_data.clear();
        m_data.shrink_to_fit();
        m_data.reserve(cols * rows);
        m_data.resize(cols * rows);
    }

    void Resize( size_t cols, size_t rows, T defo )
    {
        Resize(cols, rows);
        FillCells(defo);
    }

    const std::vector<T>& GetData()
    {
        return m_data;
    }

    void SetData(const std::vector<T>& new_data)
    {
        assert(new_data.GetSize() == m_data.GetSize());
        m_data = new_data;
    }

    void DebugPrint()
    {
        printf("cols: %d, rows: %d\n", m_cols, m_rows);
        for( size_t i = 0; i < m_rows; i++ )
        {
            for( int j = 0; j < m_cols; j++ )
            {
                printf("%d", this->GetCell(j, i));
            }
            printf("\n");
        }
    }

    Matrix2D<T>& operator==(const Matrix2D<T>& m)
    {
        assert(m_cols == m.m_cools && m_rows == m.m_rows);
        std::copy( m.m_data.begin(), m.m_data.end(), this->m_data.begin() );
        return *this;
    }

    bool IsValidCellCoord(int x, int y)
    {
        return x >= 0 && x < GetColsNumber() &&
               y >= 0 && y < GetRowsNumber();
    }

private:

    int CoordToIndex( size_t x, size_t y ) const
    {
        return int(y * m_cols + x);
    }

    std::vector<T> m_data;
    size_t m_rows, m_cols;

};

template <typename T>
void subcopy( const Matrix2D<T>& src, Matrix2D<T>& target,
              int subx, int suby, int subw, int subh )
{
    assert( src.GetColsNumber() >= subw && src.GetRowsNumber() >= subh );
    for( int x = 0; x < subw; x++ )
    {
        for( int y = 0; y < subh; y++ )
        {
            target.SetCell(x + subx, y + suby, src.GetCell(x, y));
        }
    }
}

template <typename T>
void subcopy( const Matrix2D<T>& src, Matrix2D<T>& target,
              int subx, int suby )
{
    subcopy<T>(src, target, subx, suby, src.GetColsNumber(), src.GetRowsNumber());
}

template <typename T>
Matrix2D<T> shrink_to_fit( const Matrix2D<T>& src, int border_size )
{
    // TODO
}

typedef Matrix2D<int> Matrix2Di;
typedef Matrix2D<uint8_t> Matrix2Du8;

template <typename T>
class Matrix2DDebug
{
public:
    void operator << ( const Matrix2D<T>& matrix )
    {
        for( int y = 0; y < matrix.GetRowsNumber(); y++ )
        {
            for( int x = 0; x < matrix.GetColsNumber(); x++ )
            {
                std::cout << std::setw(3);
                std::cout << matrix.GetCell(x, y) << " ";
            }
            std::cout << std::endl;
        }
    }
};


}
