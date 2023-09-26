//====================================================
// Задание 1.1.1. Реализовать класс для работы с квадратными матрицами целых чисел задаваемой размерности.
//====================================================
// September 2023           Create      A. Naibauer 22112
//====================================================

/** Деректива препроцессора. */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Matrix {
private:
    int m_Rows;
    int m_Cols;
    int **m_Arr;
public:
    //Конструктора по умолчанию для инициализации матрицы размерности 0
    Matrix();
    //Конструктор, инициализации единичной матрицы указанной размерности
    Matrix(int n);
    //Конструктора, принимающего размерность и массив элементов, которые нужно расположить на главной
    //диагонали, остальные элементы заполнить нулями
    Matrix(int n, const int *a);
    //Конструктор, принимающей кол-во строк и кол-во столбцов матрицы, - создаёт матрицу и заполняет её нулями
    Matrix(int n , int m);

    friend ostream& operator<<(ostream& in, const Matrix& Matrix);
    friend istream& operator>>(istream& out, Matrix& Matrix);

    // Перегрузка оператора +
    Matrix operator+(const Matrix& other) const;
    //перегрузка оператора -
    Matrix operator-(const Matrix& other) const;
    //перегрузка оператора -
    Matrix operator*(const Matrix& other) const;
    //перегрузка оператора  ==
    bool operator==(const Matrix& other) const;
    //перегрузка оператора  !=
    bool operator!=(const Matrix& other) const;
    //перегрузка оператора ! для транспонирования матрицы
    Matrix operator!();
    //перегрузка оператора (,) -построение минора
    Matrix operator()(int a, int b) const;
    // copy
    void operator=(const Matrix& other);

    int Get_Number_Rows() const;
    int Get_Number_Cols() const;
    //Доп задания:
    // Перегрузка оператора []: Обращение к строке матрицы по индексу
    int* operator[](int index);

    // Обращение к столбцу матрицы
    const int* operator()(int m_Index) const {
        if (m_Index < 0 || m_Index >= m_Cols) {
            throw std::out_of_range("Column index out of range");
        }

        int* column = new int[m_Cols];
        for (int i = 0; i < m_Cols; ++i) {
            column[i] = m_Arr[i][m_Index];
        }
        return column;
    }

    int* operator()(int columnIndex) {
        if (columnIndex < 0 || columnIndex >= m_Cols) {
            throw std::out_of_range("Column index out of range");
        }

        int* column = new int[m_Rows];
        for (int i = 0; i < m_Cols; ++i) {
            column[i] = m_Arr[i][columnIndex];
        }
        return column;
    }

    // Деструктор
    ~Matrix() {
        if (m_Arr != nullptr) {// Проверка: была ли выделена память и нужно ли её освобождать
            for (int i = 0; i < m_Rows; ++i) {
                delete[] m_Arr[i];
            }
            delete[] m_Arr;
        }
    }
};

//Конструкторы
Matrix::Matrix() : m_Rows(0), m_Cols(0), m_Arr(nullptr) {}
Matrix::Matrix(int n) : m_Rows(n), m_Cols(n), m_Arr(nullptr) {
    m_Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
    for (int i = 0; i < n; ++i) {
        m_Arr[i] = new int[n]; //выделяем память под массив размера n
        for (int j = 0; j < n; ++j) {
            if (j == i) {
                m_Arr[j][j] = 1; //Заполняем диагональ 1
            } else {
                m_Arr[i][j] = 0; //вне диагонали 0
            }
        }
    }
}
Matrix::Matrix(int n, const int *a) : m_Rows(n), m_Cols(n), m_Arr(nullptr) {
    m_Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
    int cou = 0;
    for (int i = 0; i < n; ++i) {
        m_Arr[i] = new int[n]; //выделяем память под массив размера n
        for (int j = 0; j < n; ++j) {
            if (j == i) {
                m_Arr[j][j] = a[cou++]; //Заполняем диагональ элементами из массива (a)
            } else {
                m_Arr[i][j] = 0; //вне диагонали 0
            }
        }
    }
}

Matrix::Matrix(int n , int m) : m_Rows(n), m_Cols(m), m_Arr(nullptr) {
    m_Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
    for (int i = 0; i < n; ++i) {
        m_Arr[i] = new int[m]; //выделяем память под массив размера n
        for (int j = 0; j < n; ++j) {
            m_Arr[i][j] = 0;
        }
    }
}


//перегрузка оператора << - для вывода матрицы
ostream& operator<<(ostream& out, const Matrix& Matrix){
    for( int i = 0; i < Matrix.m_Rows; ++i){
        for (int j = 0; j < Matrix.m_Cols; ++j) {
            out << Matrix.m_Arr[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}
//перегрузка оператора >> - для заполнения матрицы элементами из файла
istream& operator >> (istream& in, Matrix& Matrix){
    Matrix.m_Arr = new int*[Matrix.m_Rows];
    for (int i = 0; i < Matrix.m_Rows; ++i) {
        Matrix.m_Arr[i] = new int[Matrix.m_Cols];
    }
    for( int i = 0; i < Matrix.m_Rows; ++i){
        for (int j = 0; j < Matrix.m_Cols; ++j) {
            in >> Matrix.m_Arr[i][j];
        }
    }
    return in;
}

Matrix Matrix::operator+(const Matrix& other) const{
    if(m_Rows != other.m_Rows || m_Cols != other.m_Cols){
        cerr << "Сложение не возможно: не совпадает размерность матриц";
        exit(1);
    }
    Matrix result(m_Rows, m_Cols);
    for(int i = 0; i < m_Rows; ++i){
        for (int j = 0; j < m_Cols; ++j) {
            result.m_Arr[i][j] = m_Arr[i][j] + other.m_Arr[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& other) const{
    if(m_Rows != other.m_Rows || m_Cols != other.m_Cols){
        cerr << "вычитание не возможно: не совпадает размерность матриц";
        exit(1);
    }
    Matrix result(m_Rows, m_Cols);
    for(int i = 0; i < m_Rows; ++i){
        for (int j = 0; j < m_Cols; ++j) {
            result.m_Arr[i][j] = m_Arr[i][j] - other.m_Arr[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& other) const{ //возмжно утечка памяти
    if(m_Cols != other.m_Rows){
        cerr << "умножение не возможно: не совпадает размерность матриц";
        exit(1);
    }
    Matrix result(m_Rows, other.m_Cols);
    for(int i = 0; i < m_Rows; ++i){
        for (int j = 0; j < other.m_Cols; ++j) {
            for (int k =0; k < m_Cols; ++k){
                result.m_Arr[i][j] += m_Arr[i][k] * other.m_Arr[k][j];
            }
        }
    }
    return result;
}
bool Matrix::operator==(const Matrix& other) const{
    if(m_Rows != other.m_Rows || m_Cols != other.m_Cols){
        cerr << "Не совпадает размерность матриц";
        exit(1);
    }
    for (int i = 0; i < m_Rows; ++i){
        for (int j = 0; j < m_Cols; ++j) {
            if(m_Arr[i][j] != other.m_Arr[i][j]){
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix& other) const{
    if(m_Rows != other.m_Rows || m_Cols != other.m_Cols){
        cerr << "Не совпадает размерность матриц";
        exit(1);
    }
    for (int i = 0; i < m_Rows; ++i){
        for (int j = 0; j < m_Cols; ++j) {
            if(m_Arr[i][j] != other.m_Arr[i][j]){
                return true;
            }
        }
    }
    return false;
}
Matrix Matrix::operator!(){
    Matrix A(m_Cols, m_Rows);
    for (int i = 0; i < m_Cols; ++i) {
        for (int j = 0; j < m_Rows; ++j) {
            A.m_Arr[i][j] = m_Arr[j][i];
        }
    }
    return A;
}
Matrix Matrix::operator()(int a, int b) const{
    if(m_Rows != m_Cols){
        cerr << "Не возможно построить минор";
        exit(1);
    }
    if(a > m_Rows || b > m_Cols){
        cerr << "Ошибка: выход за размер матрицы";
        exit(1);
    }
    a = a-1;
    b = b-1;
    Matrix A(m_Rows-1);
    int c = 0, d = 0;
    for( int i = 0; i < m_Rows; ++i){
        if(i == a){
            continue;
        }
        for (int j = 0; j < m_Cols; ++j) {
            if(j == b){
                continue;
            }
            A.m_Arr[c][d] = m_Arr[i][j];
            d++;
            if(d == m_Cols-1){
                d = 0;
                c++;
            }
        }
    }
    return A;
}
void Matrix::operator=(const Matrix& other){
    if(m_Rows != other.m_Rows || m_Cols != other.m_Cols){
        cerr << "Не совпадает размерность матриц";
        exit(1);
    }
    for(int i = 0; i < m_Rows; ++i){
        for(int j  = 0; j < m_Cols; ++j){
            m_Arr[i][j] = other.m_Arr[i][j];
        }
    }
}

int* Matrix::operator[](int index){
    if(index >= m_Rows){
        cerr << "Ошибка: выход за размер матрицы";
        exit(1);
    }
    return m_Arr[index];
}

int Matrix::Get_Number_Rows() const{
    return m_Rows;
}
int Matrix::Get_Number_Cols() const{
    return m_Cols;
}


int main() {
    system("chcp 65001"); // Русификация ввода/вывода
    ifstream F("input.txt"); //открываем файл "input.txt"
    ofstream Out("output.txt"); //открываем файл "input.txt"
    if(!F || !Out){
        cout << "Не удалось открыть файлы"<< endl;
        return 1;
    }
    int n, k;
    F >> n; //Считываем размер матриц
    F >> k; //Считываем число К
    Matrix A(n), B(n), C(n), D(n);
    F >> A >> B >> C >> D;

    int *cc = new int[n]; //Создаю массив = {k, k, k, ..., k}
    for (int i = 0; i < n; ++i) {
        cc[i] = k;
    }

    Matrix K(n, cc);

    //Пример по заданию
    Out << (A + B * !C + K)* !D << endl;

    cout << A << endl;

    cout << A(0)[0] << endl;

    delete[] cc;
    Out.close();
    F.close();
    return 0;
}
