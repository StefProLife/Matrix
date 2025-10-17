#include <iostream>
#include <cassert>
#include "sparse_infinite_matrix.h"

int main(int argc, char const* argv[])
{
    SparseInfiniteMatrix<int> matrix;
    assert(matrix.Size() == 0);
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.Size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.Size() == 1);

    matrix[100][100] = 310;
    assert(matrix[100][100] == 310);
    assert(matrix.Size() == 1);

    matrix[100][100] = -1;
    assert(matrix[100][100] == -1);
    assert(matrix.Size() == 0);

    for (auto i = 0; i < 10; i++)
        matrix[i][i] = i;

    std::cout << std::endl;

    for (auto i = 0, j = 9; i < 10; i++, j--)
        matrix[i][j] = j;

    std::cout << "size: " << matrix.Size() << std::endl;
    std::cout << std::endl;

    for (auto c : matrix)
    {
        size_t x;
        size_t y;
        size_t v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}