#include <functional>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdexcept>

using namespace std;

template<typename T>
class Matrix {
private:
    long int rows;
    long int cols;
    T** arr;

public:
    Matrix() : rows(0), cols(0), arr(nullptr) {}

    Matrix(long int m, long int n) {
        rows = m;
        cols = n;
        arr = new T * [rows];
        for (unsigned int i = 0; i < rows; ++i) {
            arr[i] = new T[cols];
            for (unsigned int j = 0; j < cols; ++j) {
                arr[i][j] = 0;
            }
        }
    }

    explicit Matrix(const char* filename) : rows(0), cols(0), arr(nullptr) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error");
        }
        std::string line;
        int i = 0;
        int rows_tmp = 0;
        int cols_tmp = 0;
        while (std::getline(file, line)) {
            if (i == 0) {
                std::stringstream ss(line);
                ss >> rows_tmp;
                ss.ignore(1, ',');
                ss >> cols_tmp;
                if (cols_tmp > 0 && rows_tmp > 0) {
                    rows = rows_tmp;
                    cols = cols_tmp;
                    arr = new T * [rows];
                    for (unsigned int l = 0; l < rows; ++l) {
                        arr[l] = new T[cols];
                    }
                }
                else {
                    throw std::out_of_range("Error");
                }
            }
            else {
                std::stringstream ss(line);
                for (unsigned int j = 0; j < cols_tmp; j++) {
                    T value;
                    ss >> value;
                    ss.ignore(1, ',');
                    arr[i - 1][j] = value;
                }
            }
            i += 1;
        }
        file.close();
    }

    Matrix(const Matrix& second) {
        rows = second.rows;
        cols = second.cols;
        arr = new T * [rows];
        for (unsigned int i = 0; i < rows; ++i) {
            arr[i] = new T[cols];
            for (unsigned int j = 0; j < cols; ++j) {
                arr[i][j] = second.arr[i][j];
            }
        }
    }

    Matrix(Matrix&& second) noexcept {
        rows = second.rows;
        cols = second.cols;
        arr = second.arr;
        second.arr = nullptr;
    }

    ~Matrix() {
        for (unsigned int i = 0; i < rows; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
    }

    void initialize() {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                std::cin >> arr[i][j];
            }
        }
    }

    static Matrix<T> one(long int n) {
        Matrix<T> result(n, n);
        for (unsigned int i = 0; i < n; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                if (i == j) {
                    result.arr[i][j] = 1;
                }
                else {
                    result.arr[i][j] = 0;
                }
            }
        }
        return result;
    }

    static Matrix<T> zero(long int m, long int n) {
        Matrix<T> result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.arr[i][j] = 0;
            }
        }
        return result;
    }

    T getElement(long int i, long int j) const {
        if (i < rows && j < cols && i >= 0 && j >= 0) {
            return arr[i][j];
        }
        else {
            throw std::out_of_range("Error");
        }
    }

    T getDeterminant() {
        T sum = 0;
        if (rows == cols) {
            if (rows == 1) {
                return arr[0][0];
            }
            else if (rows == 2) {
                return arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
            }
            else {
                for (unsigned int j = 0; j < cols; j++) {
                    sum += (j % 2 == 0 ? 1 : -1) * arr[0][j] * makeMinor(0, j).getDeterminant();
                }
            }
        }
        else {
            throw std::runtime_error("Error");
        }
        return sum;
    }

    void print() const {
        if (rows > 0 && cols > 0) {
            for (unsigned int i = 0; i < rows; ++i) {
                std::cout << "[";
                for (unsigned int j = 0; j < cols; ++j) {
                    std::cout << getElement(i, j) << " ";
                }
                std::cout << "]\n";
            }
        }
    }

    void readFile() {
        Matrix<T> tmp("text.txt");
        *this = tmp;
    }

    void writeFile() {
        std::ofstream file("text.txt");
        if (file.is_open()) {
            file << rows << "," << cols << "," << std::endl;
            for (unsigned int i = 0; i < rows; i++) {
                for (unsigned int j = 0; j < cols; j++) {
                    file << arr[i][j] << ",";
                }
                file << std::endl;
            }
            file.close();
        }
        else {
            throw std::runtime_error("Error");
        }
    }

    Matrix& operator=(const Matrix& second) {
        if (this != &second) {
            for (unsigned int i = 0; i < rows; ++i)
                delete[] arr[i];
            delete[] arr;

            rows = second.rows;
            cols = second.cols;
            arr = new T * [rows];
            for (unsigned int i = 0; i < rows; ++i) {
                arr[i] = new T[cols];
                for (unsigned int j = 0; j < cols; ++j) {
                    arr[i][j] = second.arr[i][j];
                }
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& second) const {
        if (rows == second.rows && cols == second.cols) {
            Matrix result(rows, cols);
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < cols; ++j) {
                    result.arr[i][j] = arr[i][j] + second.arr[i][j];
                }
            }
            return result;
        }
        else {
            throw std::invalid_argument("Matrices dimensions do not match for addition");
        }
    }

    Matrix operator-(const Matrix& second) const {
        if (rows == second.rows && cols == second.cols) {
            Matrix result(rows, cols);
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < cols; ++j) {
                    result.arr[i][j] = arr[i][j] - second.arr[i][j];
                }
            }
            return result;
        }
        else {
            throw std::invalid_argument("Matrices dimensions do not match for subtraction");
        }
    }

    Matrix operator*(const Matrix& second) const {
        if (cols == second.rows) {
            Matrix result(rows, second.cols);
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < second.cols; ++j) {
                    result.arr[i][j] = 0;
                    for (unsigned int k = 0; k < cols; ++k) {
                        result.arr[i][j] += arr[i][k] * second.arr[k][j];
                    }
                }
            }
            return result;
        }
        else {
            throw std::invalid_argument("Matrices dimensions do not match for multiplication");
        }
    }

    Matrix operator*(T factor) const {
        Matrix result(rows, cols);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                result.arr[i][j] = arr[i][j] * factor;
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix& second) {
        *this = *this * second;
        return *this;
    }

    Matrix& operator*=(T factor) {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                arr[i][j] *= factor;
            }
        }
        return *this;
    }

    Matrix& operator+=(const Matrix& second) {
        if (rows == second.rows && cols == second.cols) {
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < cols; ++j) {
                    arr[i][j] += second.arr[i][j];
                }
            }
        }
        else {
            throw std::invalid_argument("Matrices dimensions do not match for addition");
        }
        return *this;
    }

    bool operator==(const Matrix& second) const {
        if (rows == second.rows && cols == second.cols) {
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < cols; ++j) {
                    if (arr[i][j] != second.arr[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    bool operator!=(const Matrix& second) const {
        return !(*this == second);
    }

    bool operator==(T scalar) const {
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                if (arr[i][j] != scalar) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(T scalar) const {
        return !(*this == scalar);
    }

    Matrix& operator!() {
        T det = this->getDeterminant();
        if (det != 0) {
            Matrix adj = this->makeAdjoint();
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = 0; j < cols; ++j) {
                    this->arr[i][j] = adj.arr[i][j] / det;
                }
            }
        }
        else {
            throw std::runtime_error("Matrix is singular, cannot find its inverse");
        }
        return *this;
    }

private:
    void SwapElements(long int i, long int j) {
        T temp = arr[i][j];
        arr[i][j] = arr[j][i];
        arr[j][i] = temp;
    }

    void swapLines(long int i1, long int i2) {
        T* temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }

    void dif2(const T* a) {
        unsigned int k = 0;
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                arr[i][j] = a[k];
                k += 1;
            }
        }
    }

    void transp() {
        if (rows == cols) {
            for (unsigned int i = 0; i < rows; ++i) {
                for (unsigned int j = i; j < cols; ++j) {
                    if (j != i)
                        this->SwapElements(i, j);
                }
            }
        }
        else {
            throw std::invalid_argument("Matrix must be square to transpose");
        }
    }

    Matrix makeAdjoint() const {
        Matrix adjoint(rows, cols);
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < cols; ++j) {
                adjoint.arr[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * makeMinor(i, j).getDeterminant();
            }
        }
        adjoint.transp();
        return adjoint;
    }

    Matrix makeMinor(long int i, long int j) const {
        Matrix minor(rows - 1, cols - 1);
        int minor_i = 0;
        for (unsigned int r = 0; r < rows; ++r) {
            if (r == i) continue;
            int minor_j = 0;
            for (unsigned int c = 0; c < cols; ++c) {
                if (c == j) continue;
                minor.arr[minor_i][minor_j] = arr[r][c];
                minor_j++;
            }
            minor_i++;
        }
        return minor;
    }
};

int main() {
    cout << boolalpha;
    Matrix<float> Matrix1(2, 2);
    Matrix1.initialize();
    Matrix<float> Matrix2(2, 2);
    Matrix2.initialize();

    Matrix<float> MatrixSum = Matrix1 + Matrix2;
    MatrixSum.print();

    cout << Matrix1.getDeterminant() << endl;
    !Matrix1;
    Matrix1.print();
    return 0;
}
 
