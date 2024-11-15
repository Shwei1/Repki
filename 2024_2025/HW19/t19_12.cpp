#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Matrix {
public:
    std::vector<std::vector<T>> matrix;

    explicit Matrix(std::vector<std::vector<T>> vector_of_vectors): matrix(vector_of_vectors) {
        unsigned int size_row = vector_of_vectors[0].size();
        bool criterion = true;
        for (auto row: vector_of_vectors){
            if (row.size() != size_row){
                criterion = false;
            }
        }
        if (!criterion){
            throw std::runtime_error("Rows of matrix must be of equal size.");
        }
    }

    std::vector<int> matrix_size(){
        std::vector<int> m_size;
        m_size.push_back(matrix.size());
        m_size.push_back(matrix[0].size());
        return m_size;
    };


    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& M){
        for (auto row: M.matrix){
            for (auto el: row){
                os << el << ' ';
            }
            os << '\n';
        }
        return os;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (matrix_size() != other.matrix_size()) {
            throw std::runtime_error("Addends must be of the same size.");
        }
        std::vector<std::vector<T>> result = matrix;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                result[i][j] += other.matrix[i][j];
            }
        }
        return Matrix<T>(result);
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (matrix_size()[0] != other.matrix_size()[1])
            throw std::runtime_error("The amount of rows of one multiplicand must be equal to the amount of columns in the other.");

        size_t rows = matrix_size()[0];
        size_t cols = other.matrix_size()[1];
        size_t common = matrix_size()[1];

        std::vector<std::vector<T>> result(rows, std::vector<T>(cols, T()));

        for (size_t i = 0; i < rows; ++i){
            for (size_t j = 0; j < cols; ++j){
                for (size_t k = 0; k < common; ++k ){
                    result[i][j] = matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    friend std::vector<T> operator*(const Matrix<T>& mat, const std::vector<T>& vec) {
        if (mat.matrix_size().second != vec.size()) {
            throw std::runtime_error("The amount of columns must be the same as the size of the vector.");
        }

        size_t rows = mat.matrix_size().first;
        size_t cols = mat.matrix_size().second;


        std::vector<T> result(rows, T());

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[i] += mat.matrix[i][j] * vec[j];
            }
        }
        return result;
    }

    friend std::vector<T> operator*(const std::vector<T>& vec, const Matrix<T>& mat) {
        if (vec.size() != mat.matrix_size().first) {
            throw std::runtime_error("The amount of rows must be equal to the size of the vector.");
        }
        size_t cols = mat.matrix_size().second;

        std::vector<T> result(cols, T());

        for (size_t j = 0; j < cols; ++j) {
            for (size_t i = 0; i < vec.size(); ++i) {
                result[j] += vec[i] * mat.matrix[i][j];
            }
        }

        return result;
    }

};

int main(){
    std::vector<std::vector<int>> vov = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix M1(vov);
    std::vector<int> myvec = {1, 1, 0};

    std::vector<int> resvec = M1 * myvec;

    for (auto coord: resvec){

    }
}