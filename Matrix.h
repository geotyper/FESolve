
#ifndef MATRIX_H
#define MATRIX_H

#include "Fe.h"

#include <valarray>
#include <iostream> //for cholesky-solve error message
#include <cmath>

namespace femath {

using namespace fe;

typedef std::valarray<FEdouble>	DoubleVector;
typedef std::valarray<FEint>	IntVector;

//pre-declare each template friend function,  add <> in the friend lines
template<class T> class Matrix;
template<class T> std::valarray<T> operator* (const Matrix<T>& A, const std::valarray<T>& b);
template<class T> Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B);


template<class T> class Matrix
{
public:
	Matrix();
	Matrix(FEint rows);
	Matrix(FEint rows, FEint columns);
	~Matrix();

	FEint	GetNumberOfRows()		const { return _rows;}
	FEint	GetNumberOfColumns()	const { return _columns;}
	void	SetDimension(FEint rows, FEint columns);
	
	Matrix&	operator*=(T x);
	T& operator()(FEint i, FEint j);
	
	void	Transpose();
	void	Cut(IntVector* vec);
	void	Insert(Matrix* mat, IntVector* vec);

	static void	CholeskySolveLGS(Matrix* A, std::valarray<T>* b);

    Matrix(const Matrix& original);
    Matrix& operator=(const Matrix& original);
	
	friend std::valarray<T> operator* <> (const Matrix& A, const std::valarray<T>& b);
	friend Matrix operator* <> (const Matrix& A, const Matrix& B);

protected:
	std::valarray<T>* _matrix;
	FEint _rows;
	FEint _columns;
};


template<class T> Matrix<T>::Matrix()
{
	_rows = _columns = 0;
	_matrix = new std::valarray<T>;
}

template<class T> Matrix<T>::Matrix(FEint rows)
{
	_rows = _columns = rows;
	_matrix = new std::valarray<T>(0.0,rows*rows);
}

template<class T> Matrix<T>::Matrix(FEint rows, FEint columns)
{
	_rows = rows;
	_columns = columns;
	_matrix = new std::valarray<T>(0.0,rows*columns);
}

template<class T> Matrix<T>::~Matrix()
{
	delete _matrix;
}

template<class T> void Matrix<T>::SetDimension(FEint rows, FEint columns)
{
	_rows = rows;
	_columns = columns;
	_matrix->resize(rows*columns,0.0);
}

template<class T> Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B)
{
	
	if(A.GetNumberOfColumns() != B.GetNumberOfRows()){
		std::cout << "A*B not pssible" << std::endl;
		return A;
	}
	FEdouble cij = 0;

	FEint rows = A.GetNumberOfRows();
	FEint columns = B.GetNumberOfColumns();

	Matrix<T> C(rows,columns);
	
	for(FEint i = 0; i < rows; i++)
	{
		for(FEint j = 0; j < columns; j++)
		{
			for(FEint k = 0; k < A.GetNumberOfColumns(); k++)
			{
				cij += (*A._matrix)[i*A._columns + k]*(*B._matrix)[k*B._columns + j];
			}
			C(i,j) = cij;
			cij = 0;
		}
	}
	return C;
}

template<class T> std::valarray<T> operator*(const Matrix<T>& A, const std::valarray<T>& b)
{
	std::valarray<T> l = b;

	for(FEint i = 0; i < A.GetNumberOfRows(); i++)
	{
		for(FEint j = 0; j < A.GetNumberOfColumns(); j++)
		{
			l[i] += (*A._matrix)[i*A._columns + j]*b[j];
			
		}
	}
	return l;
}

template<class T> Matrix<T>& Matrix<T>::operator*=(T x)
{
	(*_matrix)*=x;
	return *this;
}

template<class T> Matrix<T>::Matrix(const Matrix<T>& original)
{
	_columns = original._columns;
	_rows = original._rows;
	_matrix = new std::valarray<FEdouble>(0.0,_rows*_columns); 
	*_matrix = *(original._matrix);
}

template<class T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& original)
{
	if(this != &original) {
		_columns = original._columns;
		_rows = original._rows;
		_matrix = new std::valarray<FEdouble>;
		_matrix->resize(_rows*_columns,0); 
		*_matrix = *(original._matrix);
	}
	return *this;
}

template<class T> void Matrix<T>::Transpose()
{
	std::valarray<T>* temp = new std::valarray<T>(0.0,_rows*_columns);
	for(FEint i = 0; i < _rows; i++)
	{
		for(FEint j = 0; j < _columns; j++)
		{
			(*temp)[j*_rows + i] = (*this)(i,j);
		}
	}
	(*_matrix) = *temp;
	delete temp;
	FEint s = _rows;
	_rows = _columns;
	_columns = s;
}

template<class T> void Matrix<T>::Cut(IntVector* vec)
{
	if(vec->size() == 0)
		return;

	FEint X;
	std::valarray<T>* new_Matrix = new std::valarray<T>;
	FEint new_rows, new_columns;
	FEint I,J,i,j;

	for (FEint K = 0; K < static_cast<FEint>(vec->size()); K++){
		
		X = (*vec)[K];
		new_rows = _rows - 1;
		new_columns = _columns - 1;
		
		new_Matrix->resize(new_rows*new_columns,0.0);
		
		I = 0;
		J = 0;
		for(i = 0; i < _rows; i++)
		{
			if(i != X){
				for(j = 0; j < _columns; j++)
				{
					if(j != X){
						(*new_Matrix)[I*new_columns + J] = (*this)(i, j);
						J++;
					}
				}
				J = 0;
				I++;
			} 
		}
		
		_rows = new_rows;
		_columns = new_columns;
		(*_matrix)=(*new_Matrix);
		(*vec)-=1;
	}

	delete new_Matrix;
}

template<class T> void Matrix<T>::Insert(Matrix* mat, IntVector* vec)
{
	
	FEint rows = mat->GetNumberOfRows();
	FEint columns = mat->GetNumberOfColumns();

	FEint i,j;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			(*this)((*vec)[i],(*vec)[j]) =(*this)((*vec)[i],(*vec)[j]) + (*mat)(i,j);
		}
	}

}

template<class T> T& Matrix<T>::operator()(FEint i, FEint j)
{
	return (*_matrix)[i*_columns + j];
}

template<class T> void Matrix<T>::CholeskySolveLGS(Matrix* A, std::valarray<T>* c)
{
	FEint rows = A->GetNumberOfRows();
	
	FEint i,j,k;
	// perform cholesky decomposition
	for(k = 0; k < rows; k++)
	{
		if((*A)(k,k) <= 0){
			std::cout << "Cholesky-Error, StiffnessMatrix not positiv definit!" << std::endl;
			return;
		}

		(*A)(k,k) = sqrt((*A)(k,k));

		for(i = k+1; i < rows; i++)
		{
			(*A)(i,k) /= (*A)(k,k);
			
			for(j = k+1; j <= i; j++)
			{
				(*A)(i,j)-=(*A)(i,k)*(*A)(j,k);
			}
			
		}
	}
	
	FEdouble s;
	// reverse unroll
	for(i = 1; i < rows; i++)
	{
		s = (*c)[i];
		for(j = 1; j <= i-1; j++)
			s-=(*A)(i,j)*(*c)[j];

		(*c)[i]=s/(*A)(i,i);
	}
	
	for(i = rows-1; i >= 0; i--)
	{
		s = (*c)[i];
		for(k = i+1; k < rows; k++)
		{
			s+=(*A)(k,i)*(*c)[k];
		}
		(*c)[i]=-s/(*A)(i,i);
	}
	
	(*c)*=-1.0;
}

} //end namespace

#endif