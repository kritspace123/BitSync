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

class matrix {
private:
    int rows;
    int cols;
    int **Arr;
public:
    //Конструктора по умолчанию для инициализации матрицы размерности 0
    matrix() : rows(0), cols(0), Arr(nullptr) {}

    //Конструктор, инициализации единичной матрицы указанной размерности
    matrix(int n) : rows(n), cols(n), Arr(nullptr) {
        Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
        for (int i = 0; i < n; ++i) {
            Arr[i] = new int[n]; //выделяем память под массив размера n
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    Arr[j][j] = 1; //Заполняем диагональ 1
                } else {
                    Arr[i][j] = 0; //вне диагонали 0
                }
            }
        }
    }

    //Конструктора, принимающего размерность и массив элементов, которые нужно расположить на главной
    //диагонали, остальные элементы заполнить нулями
    matrix(int n, const int *a) : rows(n), cols(n), Arr(nullptr) {
        Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
        int cou = 0;
        for (int i = 0; i < n; ++i) {
            Arr[i] = new int[n]; //выделяем память под массив размера n
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    Arr[j][j] = a[cou++]; //Заполняем диагональ элементами из массива (a)
                } else {
                    Arr[i][j] = 0; //вне диагонали 0
                }
            }
        }
    }

    //Конструктор, принимающей кол-во строк и кол-во столбцов матрицы, - создаёт матрицу и заполняет её нулями
    matrix(int n , int m) : rows(n), cols(m), Arr(nullptr) {
        Arr = new int *[n]; //выделяем память ( создаем массив указателей на указатели )
        for (int i = 0; i < n; ++i) {
            Arr[i] = new int[m]; //выделяем память под массив размера n
            for (int j = 0; j < n; ++j) {
                Arr[i][j] = 0;
            }
        }
    }

    friend ostream& operator<<(ostream& in, const matrix& matrix);
    friend istream& operator>>(istream& out, matrix& matrix);

    // Перегрузка оператора +
    matrix operator+(const matrix& other){
        if(rows != other.rows || cols != other.cols){
            cerr << "Сложение не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(rows, cols);
        for(int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j) {
                result.Arr[i][j] = Arr[i][j] + other.Arr[i][j];
            }
        }
        return result;
    }

    //перегрузка оператора -
    matrix operator-(const matrix& other){
        if(rows != other.rows || cols != other.cols){
            cerr << "вычитание не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(rows, cols);
        for(int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j) {
                result.Arr[i][j] = Arr[i][j] - other.Arr[i][j];
            }
        }
        return result;
    }

    //перегрузка оператора -
    matrix operator*(const matrix& other){ //возмжно утечка памяти
        if(cols != other.rows){
            cerr << "умножение не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(rows, other.cols);
        for(int i = 0; i < rows; ++i){
            for (int j = 0; j < other.cols; ++j) {
                for (int k =0; k < cols; ++k){
                    result.Arr[i][j] += Arr[i][k] * other.Arr[k][j];
                }
            }
        }
        return result;
    }

    //перегрузка оператора  ==
    bool operator==(const matrix& other){
        if(rows != other.rows || cols != other.cols){
            cerr << "Не совпадает размерность матриц";
            exit(1);
        }
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j) {
                if(Arr[i][j] != other.Arr[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    //перегрузка оператора  !=
    bool operator!=(const matrix& other){
        if(rows != other.rows || cols != other.cols){
            cerr << "Не совпадает размерность матриц";
            exit(1);
        }
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j) {
                if(Arr[i][j] != other.Arr[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
    //перегрузка оператора ! для транспонирования матрицы
    matrix operator!(){
        matrix A(cols, rows);
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                A.Arr[i][j] = Arr[j][i];
            }
        }
        return A;
    }
    //перегрузка оператора (,) -построение минора
    matrix operator()(int a, int b){
        if(rows != cols){
            cerr << "Не возможно построить минор";
            exit(1);
        }
        if(a > rows || b > cols){
            cerr << "Ошибка: выход за размер матрицы";
        }
        a = a-1;
        b = b-1;
        matrix A(rows-1);
        int c = 0, d = 0;
        for( int i = 0; i < rows; ++i){
            if(i == a){
                continue;
            }
            for (int j = 0; j < cols; ++j) {
                if(j == b){
                    continue;
                }
                A.Arr[c][d] = Arr[i][j];
                d++;
                if(d == cols-1){
                    d = 0;
                    c++;
                }
            }
        }
        return A;
    }

    //Доп задания:
    // Перегрузка оператора []: Обращение к строке матрицы по индексу
    matrix operator[](int a){
        if(a >= rows){
            cerr << "Ошибка: выход за размер матрицы";
        }
        matrix A(1, cols);
        for(int i = 0; i < cols; ++i){
            A.Arr[0][i] = Arr[a][i];
        }
        return A;
    }
    matrix operator()(int a){
        if(a >= cols){
            cerr << "Ошибка: выход за размер матрицы";
        }
        matrix A(rows, 1);
        for(int i = 0; i < rows; ++i){
            A.Arr[i][0] = Arr[i][a];
        }
        return A;
    }



    // Деструктор
    ~matrix() {
        if (Arr != nullptr) {// Проверка: была ли выделена память и нужно ли её освобождать
            for (int i = 0; i < rows; ++i) {
                delete[] Arr[i];
            }
            delete[] Arr;
        }
    }
};

//перегрузка оператора << - для вывода матрицы
ostream& operator<<(ostream& out, const matrix& matrix){
    for( int i = 0; i < matrix.rows; ++i){
        for (int j = 0; j < matrix.cols; ++j) {
            out << matrix.Arr[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

//перегрузка оператора >> - для заполнения матрицы элементами из файла
istream& operator >> (istream& in, matrix& matrix){
    matrix.Arr = new int*[matrix.rows];
    for (int i = 0; i < matrix.rows; ++i) {
        matrix.Arr[i] = new int[matrix.cols];
    }
    for( int i = 0; i < matrix.rows; ++i){
        for (int j = 0; j < matrix.cols; ++j) {
            in >> matrix.Arr[i][j];
        }
    }
    return in;
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
    matrix A(n), B(n), C(n), D(n);
    F >> A >> B >> C >> D;

    int *cc = new int[n]; //Создаю массив = {k, k, k, ..., k}
    for (int i = 0; i < n; ++i) {
        cc[i] = k;
    }

    matrix K(n, cc);

    //Пример по заданию
    Out << (A + B * !C + K)* !D << endl;

    delete[] cc;
    Out.close();
    F.close();
    return 0;
}
