#include "sparse_infinite_matrix.h"

template<typename T>
SparseInfiniteMatrix<T>::RowSparseInfiniteMatrix::RowSparseInfiniteMatrix(SparseInfiniteMatrix& matrix, size_t row)
    : _matrix(matrix), _row(row)
{}

template<typename T>
T& SparseInfiniteMatrix<T>::FindCellKeyValue(const CellKey& cellKey)
{
    auto& it = _elements.find(cellKey);
    if (it == _elements.cend())
        return static_cast<T>(_defaultValue);
    else
        return it->second;
}

template<typename T>
T& SparseInfiniteMatrix<T>::RowSparseInfiniteMatrix::operator[](size_t col)
{
    CellKey key { _row, col };
    return _matrix->FindCellKeyValue(key);
}

template <typename T>
size_t SparseInfiniteMatrix<T>::size()
{
    return _elements.size();
}

template <typename T>
SparseInfiniteMatrix<T>::RowSparseInfiniteMatrix& SparseInfiniteMatrix<T>::operator[](size_t row)
{
    return SparseInfiniteMatrix<T>::RowSparseInfiniteMatrix(this, row);
}

template <typename T>
int SparseInfiniteMatrix<T>::_defaultValue = -1;