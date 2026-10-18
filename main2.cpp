#include <iostream>
#include <new>
#include <limits>

void create_matrix(int **&matrix, size_t n, size_t m) {
    try {
        matrix = new int *[n];
    } catch (std::bad_alloc &) {
        throw;
    }
    for (size_t k = 0; k < n; k++) {
        try {
            matrix[k] = new int[m];
        } catch (std::bad_alloc &) {
            for (size_t i = 0; i < k; i++) {
                delete [] matrix[i];
            }
            delete [] matrix;
            matrix = nullptr;
            throw;
        }
    }
}

void clear_matrix(int **lhs, size_t n1, int **rhs, size_t n2, int **res_arr) {
    size_t n = 0;
    if (lhs != nullptr) {
        for (size_t i = 0; i < n1; i++) {
            delete [] lhs[i];
        }
    }
    if (rhs != nullptr) {
        for (size_t i = 0; i < n2; i++) {
            delete [] rhs[i];
        }
    }
    if (n1 >= n2) {
        n = n1;
    } else {
        n = n2;
    }
    if (res_arr != nullptr) {
        for (size_t i = 0; i < n; i++) {
            delete [] res_arr[i];
        }
    }
    delete [] lhs;
    delete [] rhs;
    delete [] res_arr;
}

int **concat_rows(const int *const *lhs, size_t n1, size_t m1, const int *const *rhs, size_t n2, size_t m2) {
    size_t min_n = 0, max_n = 0, m_of_max = 0;
    const int *const *matrix_of_max = nullptr;
    if (n1 < n2) {
        min_n = n1;
        max_n = n2;
        m_of_max = m2;
        matrix_of_max = rhs;
    } else {
        min_n = n2;
        max_n = n1;
        m_of_max = m1;
        matrix_of_max = lhs;
    }
    if (m1 > std::numeric_limits<size_t>::max() - m2) {
        std::cerr << "Error creating matrix!" << std::endl;
        throw std::bad_alloc();
    }
    int **res_arr = nullptr;
    try {
        res_arr = new int *[max_n];
    } catch (std::bad_alloc &) {
        std::cerr << "Error creating matrix!" << std::endl;
        throw;
    }
    for (size_t k = 0; k < max_n; k++) {
        try {
            if (k < min_n) {
                res_arr[k] = new int[m1 + m2];
            } else {
                res_arr[k] = new int[m_of_max];
            }
        } catch (std::bad_alloc &) {
            std::cerr << "Error creating matrix!" << std::endl;
            for (size_t i = 0; i < k; i++) {
                delete [] res_arr[i];
            }
            delete [] res_arr;
            throw;
        }
    }
    for (size_t i = 0; i < min_n; i++) {
        for (size_t j1 = 0; j1 < m1; j1++) {
            res_arr[i][j1] = lhs[i][j1];
        }
        for (size_t j2 = 0; j2 < m2; j2++) {
            res_arr[i][j2 + m1] = rhs[i][j2];
        }
    }
    for (size_t i = min_n; i < max_n; i++) {
        for (size_t j3 = 0; j3 < m_of_max; j3++) {
            res_arr[i][j3] = matrix_of_max[i][j3];
        }
    }
    return res_arr;
}

int main() {
    size_t n1 = 0, m1 = 0, n2 = 0, m2 = 0, max_n = 0, min_n = 0, m_of_max = 0;
    std::cin >> n1 >> m1 >> n2 >> m2;
    if (std::cin.fail()) {
        return 1;
    }
    int **lhs = nullptr;
    int **rhs = nullptr;
    int **res_arr = nullptr;
    try {
        create_matrix(lhs, n1, m1);
    } catch (std::bad_alloc &) {
        std::cerr << "Error creating matrix!" << std::endl;
        clear_matrix(lhs, n1, rhs, n2, res_arr);
        return 1;
    }
    for (size_t i = 0; i < n1; i++) {
        for (size_t j1 = 0; j1 < m1; j1++) {
            std::cin >> lhs[i][j1];
        }
    }
    if (std::cin.fail()) {
        clear_matrix(lhs, n1, rhs, n2, res_arr);
        return 1;
    }
    try {
        create_matrix(rhs, n2, m2);
    } catch (std::bad_alloc &) {
        std::cerr << "Error creating matrix!" << std::endl;
        clear_matrix(lhs, n1, rhs, n2, res_arr);
        return 1;
    }
    for (size_t i = 0; i < n2; i++) {
        for (size_t j2 = 0; j2 < m2; j2++) {
            std::cin >> rhs[i][j2];
        }
    }
    if (std::cin.fail()) {
        clear_matrix(lhs, n1, rhs, n2, res_arr);
        return 1;
    }
    try {
        res_arr = concat_rows(lhs, n1, m1, rhs, n2, m2);
    } catch (std::bad_alloc &) {
        clear_matrix(lhs, n1, rhs, n2, res_arr);
        return 1;
    }
    if (n1 >= n2) {
        max_n = n1;
        min_n = n2;
        m_of_max = m1;
    } else {
        max_n = n2;
        min_n = n1;
        m_of_max = m2;
    }
    for (size_t i = 0; i < max_n; i++) {
        if (i < min_n) {
            for (size_t j1 = 0; j1 < (m1 + m2); j1++) {
                std::cout << res_arr[i][j1] << " ";
            }
            std::cout << std::endl;
        } else {
            for (size_t j1 = 0; j1 < m_of_max; j1++) {
                std::cout << res_arr[i][j1] << " ";
            }
            std::cout << std::endl;
        }
    }
    clear_matrix(lhs, n1, rhs, n2, res_arr);
    return 0;
}
