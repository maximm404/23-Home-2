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
    // �����������
    Matrix(int str, int stl) : str(str), stl(stl) {
        data.resize(str, std::vector<double>(stl, 0));
    }

    // ����������
    ~Matrix() {}

    // ����� ��� ����� ������� � �������
    void vvod() {
        std::cout << "Matrix : \n";
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                std::cout << "element [" << i + 1 << "," << j + 1 << "] ";
                std::cin >> data[i][j];
            }
        }
    }

    // ����� ��� ������ ������� �� �������
    void vivod() const {
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // ����� ��� ������ ������� � ����
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

    // ����� ��� ���������� ������� �� �����
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

    // ���������� ��������� ������������
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this; // ����������������

        str = other.str;
        stl = other.stl;
        data = other.data;

        return *this;
    }

    // ���������� ��������� ������ ��� ������ �������
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.str; ++i) {
            for (int j = 0; j < matrix.stl; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // ����������� ����� ��� �������� ������� ������� ���������� �������
    static Matrix zeros(int str, int stl) {
        return Matrix(str, stl);
    }

    // ����������� ����� ��� �������� ��������� ������� ���������� �������
    static Matrix identity(int size) {
        Matrix identityMatrix(size, size);
        for (int i = 0; i < size; ++i) {
            identityMatrix.data[i][i] = 1;
        }
        return identityMatrix;
    }

    // ���������� ��������� ! ��� ���������� �������� �������
    Matrix operator!() const {
        if (str != stl) {
            throw std::invalid_argument("������� ������ ���� ����������!");
        }

        // ������ ���������� �������� ������� ����� ����������� �����
        // �� � ������ ������� ������ ����������� ����������, ��� ��������� � �������
        throw std::runtime_error("������� ����������");
    }

    // ���������� ��������� �������� ������
    Matrix operator+(const Matrix& other) {
        Matrix result(str, stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // ���������� ��������� ��������� ������
    Matrix operator-(const Matrix& other) {
        Matrix result(str, stl);

        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < stl; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    // ���������� ��������� ��������� ������� �� �������
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

    // ���������� ��������� ��������� ������� �� ������
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
    // ������ �������������

    // �������� ������� 3x3 � ���������� �� ����������
    Matrix mat(3, 3);
    mat.vvod();

    // ����� �������
    std::cout << "Original Matrix:\n";
    std::cout << mat;

    try {
        // ���������� �������� �������
        Matrix inverse = !mat;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // �������� ������� � ��������� ������
    Matrix zeroMatrix = Matrix::zeros(3, 3);
    Matrix identityMatrix = Matrix::identity(3);

    std::cout << "Zero Matrix:\n";
    std::cout << zeroMatrix;

    std::cout << "Identity Matrix:\n";
    std::cout << identityMatrix;

    return 0;
}


