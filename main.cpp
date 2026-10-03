#include <iostream>
#include <stdexcept>

int **Transpos(int l, int h, int **matrix) {
    int **transposed = nullptr;
    try {
        transposed = new int *[h];
    } catch (std::exception &) {
        delete[] transposed;
        throw;
    }
    for (int k = 0; k < h; k++) {
        try {
            transposed[k] = new int[l];
        } catch (std::exception &) {
            for (int i = 0; i < k; ++i) {
                delete[] transposed[i];
            }
            delete[] transposed;
            throw;
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            transposed[i][j] = matrix[j][i];
        }
    }
    return transposed;
}

int main() {
    int l = 0, h = 0; // количество строк, столбцов матрицы
    std::cin >> l >> h;
    if (std::cin.fail() || l <= 0 || h <= 0) {
        std::cerr << "Error in matrix creation!" << std::endl;
        return 1;
    }
    int **matrix = nullptr;
    try {
        matrix = new int *[l];
    } catch (std::exception &) {
        std::cerr << "Error in memory allocation!" << std::endl;
        delete [] matrix;
        return 2;
    }
    for (int i = 0; i < l; i++) {
        try {
            matrix[i] = new int[h];
        } catch (std::exception &) {
            std::cerr << "Error in memory allocation!" << std::endl;
            for (int k = 0; k < i; k++) {
                delete[] matrix[k];
            }
            delete[] matrix;
            return 2;
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < h; j++) {
            std::cin >> matrix[i][j];
            if (std::cin.fail()) {
                std::cerr << "Error in matrix creation!" << std::endl;
                for (int k = 0; k < l; ++k) {
                    delete[] matrix[k];
                }
                delete[] matrix;
                return 1;
            }
        }
    }
    int **transposed = nullptr;
    try {
        transposed = Transpos(l, h, matrix);
    } catch (std::exception &) {
        std::cerr << "Error in memory allocation!" << std::endl;
        for (int i = 0; i < l; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 2;
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            std::cout << transposed[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < l; ++i) {
        delete[] matrix[i];
    }
    for (int i = 0; i < h; ++i) {
        delete[] transposed[i];
    }
    delete[] matrix;
    delete[] transposed;
    return 0;
}