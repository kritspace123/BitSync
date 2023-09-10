#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class matrix {
private:
    int dimension; //Размерность матрицы || Можно использовать беззнаковый тип unsigned short(2 байта)
    int **Arr;
public:
    //Конструктора по умолчанию для инициализации матрицы размерности 0
    matrix() : dimension(0), Arr(nullptr) {}

    //Конструктор, инициализации единичной матрицы указанной размерности
    matrix(int n) : dimension(n), Arr(nullptr) {
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
    matrix(int n, const int *a) : dimension(n), Arr(nullptr) {
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

    friend ostream& operator<<(ostream& in, const matrix& matrix);
    friend istream& operator>>(istream& out, matrix& matrix);

    // Перегрузка оператора +
    matrix operator+(const matrix& other){
        if(dimension != other.dimension){
            cerr << "Сложение не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(dimension);
        for(int i = 0; i < dimension; ++i){
            for (int j = 0; j < dimension; ++j) {
                result.Arr[i][j] = Arr[i][j] + other.Arr[i][j];
            }
        }
        return result;
    }

    //перегрузка оператора -
    matrix operator-(const matrix& other){
        if(dimension != other.dimension){
            cerr << "вычитание не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(dimension);
        for(int i = 0; i < dimension; ++i){
            for (int j = 0; j < dimension; ++j) {
                result.Arr[i][j] = Arr[i][j] - other.Arr[i][j];
            }
        }
        return result;
    }

    //перегрузка оператора -
    matrix operator*(const matrix& other){
        if(dimension != other.dimension){
            cerr << "умножение не возможно: не совпадает размерность матриц";
            exit(1);
        }
        matrix result(dimension);
        matrix a(dimension);
        for(int i = 0; i < dimension; ++i){
            for (int j = 0; j < dimension; ++j) {
                for (int k =0; k < dimension; ++k){
                    result.Arr[i][j] += Arr[i][k] * other.Arr[k][j];
                }
            }
        }
        return result- a;
    }

    //перегрузка оператора  ==
     bool operator==(const matrix& other){
        if(dimension != other.dimension){
            cerr << "Не совпадает размерность матриц";
            exit(1);
        }
        for (int i = 0; i < dimension; ++i){
            for (int j = 0; j < dimension; ++j) {
                if(Arr[i][j] != other.Arr[i][j]){
                    return false;
                }
            }
        }
         return true;
    }

    //перегрузка оператора  !=
    bool operator!=(const matrix& other){
        if(dimension != other.dimension){
            cerr << "Не совпадает размерность матриц";
            exit(1);
        }
        for (int i = 0; i < dimension; ++i){
            for (int j = 0; j < dimension; ++j) {
                if(Arr[i][j] != other.Arr[i][j]){
                    return true;
                }
            }
        }
        return false;
    }

    //перегрузка оператора ! для транспонирования матрицы
    matrix operator!(){
        matrix A(dimension);
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                A.Arr[i][j] = Arr[j][i];
            }
        }
        return A;
    }
    //перегрузка оператора (,) -построение минора
    matrix operator()(int a, int b){
        a = a-1;
        b = b-1;
        matrix A(dimension-1);
        int c = 0, d = 0;
        for( int i = 0; i < dimension; ++i){
            if(i == a){
                continue;
            }
            for (int j = 0; j < dimension; ++j) {
                if(j == b){
                    continue;
                }
                A.Arr[c][d] = Arr[i][j];
                d++;
                if(d == dimension-1){
                    d = 0;
                    c++;
                }
            }
        }
        return A;
    }


    // Деструктор
    ~matrix() {
        if (Arr != nullptr) {// Проверка: была ли выделена память и нужно ли её освобождать
            for (int i = 0; i < dimension; ++i) {
                delete[] Arr[i];
            }
            delete[] Arr;
        }
    }
};

//перегрузка оператора << - для вывода матрицы
ostream& operator<<(ostream& out, const matrix& matrix){
    for( int i = 0; i < matrix.dimension; ++i){
        for (int j = 0; j < matrix.dimension; ++j) {
            out << matrix.Arr[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

//перегрузка оператора >> - для заполнения матрицы элементами из файла
istream& operator >> (istream& in, matrix& matrix){
    matrix.Arr = new int*[matrix.dimension];
    for (int i = 0; i < matrix.dimension; ++i) {
        matrix.Arr[i] = new int[matrix.dimension];
    }
    for( int i = 0; i < matrix.dimension; ++i){
        for (int j = 0; j < matrix.dimension; ++j) {
            in >> matrix.Arr[i][j];
        }
    }
    return in;
}

int main() {
    system("chcp 65001");
    ifstream F("input.txt"); //открываем файл "input.txt"
    ofstream Out("output.txt"); //открываем файл "input.txt"
    if(!F){
        cout << "Не удалось открыть файл input.txt"<< endl;
    }
    int n, k;
    F >> n; //Считываем размер матриц
    F >> k; //Считываем число К
    matrix A(n), B(n), C(n), D(n);
    F >> A >> B >> C >> D;

    int *cc = new int[n];
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
