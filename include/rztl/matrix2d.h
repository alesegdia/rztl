#pragma once

#include <initializer_list>
#include <vector>
#include <iostream>
#include <memory>
#include <iomanip>
#include <cassert>


namespace rztl {


template <typename T>
class Matrix2D
{
public:

    typedef std::shared_ptr<Matrix2D<T>> SharedPtr;

    Matrix2D( size_t cols, size_t rows ) {
        resize(cols, rows);
    }

    Matrix2D( size_t cols, size_t rows, T fill_value )
    {
        resize(cols, rows);
        fill(fill_value);
    }

    Matrix2D( const Matrix2D<int>& other )
        : m_cols(other.cols()),
          m_rows(other.rows()),
          m_data(other.m_data)
    {

    }

    Matrix2D( size_t cols, size_t rows, std::initializer_list<T> il )
        : m_cols(cols),
          m_rows(rows),
          m_data(il)
    {

    }

    inline void set( size_t col, size_t row, T value )
    {
        assert(col >= 0 && col < m_cols);
        assert(row >= 0 && row < m_rows);
        m_data[coordToIndex(col, row)] = value;
    }

    inline T get( size_t col, size_t row ) const
    {
        return m_data[coordToIndex(col, row)];
    }

    inline T& get( size_t col, size_t row )
    {
        return m_data[coordToIndex(col, row)];
    }

    size_t cols() const
    {
        return m_cols;
    }

    size_t rows() const
    {
        return m_rows;
    }

    void fill( T fill_value )
    {
        std::fill(m_data.begin(), m_data.end(), fill_value);
    }

    void fill( size_t x1, size_t y1, size_t x2, size_t y2, T fill_value)
    {
        assert(x1 < m_cols && x2 < m_cols);
        assert(y1 < m_rows && y2 < m_rows);

        for( size_t yy1 = y1; yy1 <= y2; yy1++ )
        {
            for( size_t xx1 = x1; xx1 <= x2; xx1++ )
            {
                set(xx1, yy1, fill_value);
            }
        }
    }

    void resize( size_t cols, size_t rows )
    {
        m_cols = cols;
        m_rows = rows;

        m_data.clear();
        m_data.shrink_to_fit();
        m_data.reserve(cols * rows);
        m_data.resize(cols * rows);
    }

    void resize( size_t cols, size_t rows, T defo )
    {
        resize(cols, rows);
        fill(defo);
    }

    const std::vector<T>& data()
    {
        return m_data;
    }

    void data(const std::vector<T>& new_data)
    {
        assert(new_data.size() == m_data.size());
        m_data = new_data;
    }

    void debugPrint()
    {
        printf("cols: %d, rows: %d\n", m_cols, m_rows);
        for( int i = 0; i < m_rows; i++ )
        {
            for( int j = 0; j < m_cols; j++ )
            {
                printf("%d", this->get(j, i));
            }
            printf("\n");
        }
    }

    Matrix2D<T>& operator==(const Matrix2D<T>& m)
    {
        std::copy( m.m_data.begin(), m.m_data.end(), this->m_data.begin() );
        return *this;
    }

private:

    int coordToIndex( int x, int y ) const
    {
        return y * m_cols + x;
    }

    std::vector<T> m_data;
    size_t m_rows, m_cols;

};

template <typename T>
void subcopy( const Matrix2D<T>& src, Matrix2D<T>& target,
              int subx, int suby, int subw, int subh )
{
    assert( src.cols() >= subw && src.rows() >= subh );
    for( int x = 0; x < subw; x++ )
    {
        for( int y = 0; y < subh; y++ )
        {
            target.set(x + subx, y + suby, src.get(x, y));
        }
    }
}

template <typename T>
void subcopy( const Matrix2D<T>& src, Matrix2D<T>& target,
              int subx, int suby )
{
    subcopy<T>(src, target, subx, suby, src.cols(), src.rows());
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
        for( int y = 0; y < matrix.rows(); y++ )
        {
            for( int x = 0; x < matrix.cols(); x++ )
            {
                std::cout << std::setw(3);
                std::cout << matrix.get(x, y) << " ";
            }
            std::cout << std::endl;
        }
    }
};


}
