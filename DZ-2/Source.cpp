#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    int str;
    int stl;
    std::vector<std::vector<double>> data;

public:
    // Конструктор
    Matrix(int str, int stl) : str(str), stl(stl) {
        data.resize(str, std::vector<double>(stl, 0));
    }

    // Деструктор
    ~Matrix() {}

    // Метод для ввода матрицы с консоли
    void vvod() {
        std::cout << "Matrix : \n";
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                std::cout << "element [" << i + 1 << "," << j + 1 << "] ";
                std::cin >> data[i][j];
            }
        }
    }

    // Метод для вывода матрицы на консоль
    void vivod() const {
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Метод для записи матрицы в файл
    void tofile(const char* filename) const {
        std::ofstream file("qwerty.txt");
        if (!file) {
            std::cerr << "Error";
            return;
        }

        file << str << " " << stl << std::endl;
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                file << data[i][j] << " ";
            }
            file << std::endl;
        }

        file.close();
    }

    // Метод для считывания матрицы из файла
    void fromfile(const char* filename) {
        std::ifstream file("qwerty.txt");
        if (file.is_open()) {
            file >> str >> stl;
            data.resize(str, std::vector<double>(stl, 0));
            for (int i = 0; i < str; ++i) {
                for (int j = 0; j < stl; ++j) {
                    file >> data[i][j];
                }
            }
            file.close();
        }
        else {
            std::cout << "Unable to open file";
        }
    }

    // Перегрузка оператора присваивания
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this; // Самоприсваивание

        str = other.str;
        stl = other.stl;
        data = other.data;

        return *this;
    }

    // Перегрузка оператора вывода для вывода матрицы
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.str; ++i) {
            for (int j = 0; j < matrix.stl; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // Статический метод для создания нулевой матрицы указанного размера
    static Matrix zeros(int str, int stl) {
        return Matrix(str, stl);
    }

    // Статический метод для создания единичной матрицы указанного размера
    static Matrix identity(int size) {
        Matrix identityMatrix(size, size);
        for (int i = 0; i < size; ++i) {
            identityMatrix.data[i][i] = 1;
        }
        return identityMatrix;
    }

    // Перегрузка оператора ! для вычисления обратной матрицы
    Matrix operator!() const {
        if (str != stl) {
            throw std::invalid_argument("Матрица должна быть квадратной!");
        }

        // Пример вычисления обратной матрицы можно реализовать здесь
        // Но в данном примере просто выбрасываем исключение, как требуется в задании
        throw std::runtime_error("Матрица необратима");
    }

    // Перегрузка оператора сложения матриц
    Matrix operator+(const Matrix& other) {
        Matrix result(str, stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Перегрузка оператора вычитания матриц
    Matrix operator-(const Matrix& other) {
        Matrix result(str, stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    // Перегрузка оператора умножения матрицы на матрицу
    Matrix operator*(const Matrix& other) {
        Matrix result(str, other.stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < other.stl; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < stl; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Перегрузка оператора умножения матрицы на скаляр
    Matrix operator*(const int scalar) {
        Matrix result(str, stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }

        return result;
    }
};

int main() {
    // Пример использования

    // Создание матрицы 3x3 и заполнение ее элементами
    Matrix mat(3, 3);
    mat.vvod();

    // Вывод матрицы
    std::cout << "Original Matrix:\n";
    std::cout << mat;

    try {
        // Вычисление обратной матрицы
        Matrix inverse = !mat;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Создание нулевой и единичной матриц
    Matrix zeroMatrix = Matrix::zeros(3, 3);
    Matrix identityMatrix = Matrix::identity(3);

    std::cout << "Zero Matrix:\n";
    std::cout << zeroMatrix;

    std::cout << "Identity Matrix:\n";
    std::cout << identityMatrix;

    return 0;
}


