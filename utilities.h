#pragma once

void printM(boost::numeric::ublas::matrix<double>& matrix) {
    for (std::size_t row = 0; row < matrix.size1(); ++row) {
        for (std::size_t column = 0; column < matrix.size2(); ++column) {
            std::cout << matrix(row, column) << " ";
        }
        std::cout << std::endl;
    }
}

