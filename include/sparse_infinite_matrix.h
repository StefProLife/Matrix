#include <map>
#include <tuple>
#include <algorithm>

struct CellKey
{
    size_t row;
    size_t col;

    bool operator<(const CellKey& other) const
    {
        if (row != other.row)
            return row < other.row;
        return col < other.col;
    }
};

template<typename T>
class SparseInfiniteMatrix;

template<typename T>
class RowSparseInfiniteMatrix
{
private:
    SparseInfiniteMatrix<T>& _pMatrix;
    T _currentValue;
    CellKey _currentCell;
    size_t _row;
public:
    RowSparseInfiniteMatrix(SparseInfiniteMatrix<T>& pMatrix, size_t row)
        : _pMatrix(pMatrix), _row(row)
    {}
public:
    RowSparseInfiniteMatrix<T>& operator[](size_t col)
    {
        _currentCell = { _row, col };
        _currentValue = _pMatrix.FindCellKeyValue(_currentCell);
        return *this;
    }
public:
    void operator=(T value)
    {
        if (value != _pMatrix._defaultValue && value != _pMatrix._zeroValue)
        {
            _pMatrix.Insert(_currentCell, value);
        }
        else
        {
            if (_currentValue != _pMatrix._defaultValue && value != _pMatrix._zeroValue)
                _pMatrix.Remove(_currentCell);
        }
    }

    operator T&() const
    {
        return _pMatrix.FindCellKeyValue(_currentCell);;
    }

    friend bool operator==(const RowSparseInfiniteMatrix<T>& lhs, T rhs)
    {
        return lhs._currentValue == rhs;
    }

    friend bool operator!=(const RowSparseInfiniteMatrix<T>& lhs, T rhs)
    {
        return !(lhs._currentValue == rhs);
    }

    friend bool operator==(T lhs, const RowSparseInfiniteMatrix<T>& rhs)
    {
        return lhs == rhs._currentValue;
    }

    friend bool operator!=(T lhs, const RowSparseInfiniteMatrix<T>& rhs)
    {
        return !(lhs == rhs._currentValue);
    }
};

template<typename T>
class SparseInfiniteMatrix
{
    using IteratorType = typename std::map<CellKey, T>::iterator;

private:
    std::map<CellKey, T> _elements;
public:
    static int _defaultValue;
    static int _zeroValue;
public:
    class Iterator;
public:
    SparseInfiniteMatrix() = default;
    T& FindCellKeyValue(const CellKey& cellKey)
    {
        auto it = _elements.find(cellKey);
        if (it == _elements.cend())
            return _defaultValue;
        else
            return it->second;
    }
public:
    Iterator begin()
    {
        return Iterator(_elements.begin());
    }

    Iterator end()
    {
        return Iterator(_elements.end());
    }
public:
    size_t Size()
    {
        return _elements.size();
    }

    void Insert(CellKey cellKey, T value)
    {
        _elements[cellKey] = value;
    }

    void Remove(const CellKey& cellKey)
    {
        _elements.erase(_elements.find(cellKey));
    }

public:
    RowSparseInfiniteMatrix<T> operator[](size_t row)
    {
        return RowSparseInfiniteMatrix<T>(*this, row);
    }

public:
    class Iterator
    {
    public:
        Iterator(IteratorType  iteratorType)
            : _iteratorType(iteratorType)
        {}

        std::tuple<size_t, size_t, T> operator*()
        {
            return std::make_tuple(_iteratorType->first.row, _iteratorType->first.col, _iteratorType->second);
        };

        Iterator& operator++()
        {
            ++_iteratorType;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++_iteratorType;
            return temp;
        }

        bool operator==(const Iterator& other) const
        {
            return _iteratorType == other._iteratorType;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(_iteratorType == other._iteratorType);
        }

    private:
        IteratorType _iteratorType;
    };
};

template <typename T>
int SparseInfiniteMatrix<T>::_defaultValue = -1;

template <typename T>
int SparseInfiniteMatrix<T>::_zeroValue = 0;
