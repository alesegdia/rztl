
#pragma once

#include <stdlib.h>
#include <iostream>

template <typename T>
class Matrix2D
{


private:

	int rows, cols;
	T* data;


public:

	const void* Raw()
	{
		return ((void*)data);
	}


	Matrix2D() : data( NULL )
	{

	}

	Matrix2D( int rows_, int cols_ ) : data( NULL )
	{
		rows = rows_;
		cols = cols_;
		Alloc( rows, cols );
	}

	Matrix2D( int size ) : data( NULL )
	{
		rows = size;
		cols = size;
		Alloc( rows, cols );
	}

	Matrix2D( const Matrix2D& other ) : data( NULL )
	{
		Alloc( other.rows, other.cols );

		for( int i = 0; i < this->rows; i++ )
		{
			for( int j = 0; j < this->cols; j++ )
			{
				Set( i, j, other.Get( i, j ) );
			}
		}
	}

	~Matrix2D()
	{
		if( data != NULL )
			delete [] data;
	}

	void Alloc( int rows, int cols )
	{
		if( data != NULL ) delete [] data;
		this->rows = rows;
		this->cols = cols;
		data = new T[rows * cols];
		for( int r = 0; r < rows; r++ )
			for( int c = 0; c < cols; c++ )
				Set( r, c, 0 );
	}

	/*
	T operator()(int i, int j)
	{
		return data.Get(i,j);
	}
	*/

	void Set( int row, int col, T val )
	{
		data[row * this->cols + col] = val;
	}

	void Set( T val )
	{
		for( int i = 0; i < this->rows; i++ )
		{
			for( int j = 0; j < this->cols; j++ )
			{
				Set( i, j, val );
			}
		}
	}

	T Get( int row, int col ) const
	{
		return data[row * this->cols + col];
	}

	/*
	Matrix2D& operator=( const Matrix2D& other )
	{
		for( int i = 0; i < cols; i++ )
		for( int j = 0; j < rows; j++ )
		{
			Set(i,j,other.Get(i,j));
		}
		return *this;
	}
	*/

	void Debug()
	{
		for( int i = 0; i < rows; i++ )
		{
			for( int j = 0; j < cols; j++ )
			{
				std::cout << Get( i, j ) << "";
			}
			printf("\n");
		}
	}

	int Rows() { return rows; }
	int Cols() { return cols; }

	Matrix2D& operator=( const Matrix2D& other )
	{
		Alloc( other.rows, other.cols );
		for( int i = 0; i < rows; i++ )
		for( int j = 0; j < cols; j++ )
		{
			Set( i, j, other.Get(i, j) );
		}

		return *this;
	}


};

//template class Matrix2D<int>;
