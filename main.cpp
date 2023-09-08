#include <iostream>

using namespace std;

//Создаём класс - матрица
class matrix{
private:
    int dimension; //Размерность матрицы
    int** Arr;
public:
    //Конструктора по умолчанию для инициализации матрицы размерности 0
    matrix(): dimension(0), Arr(nullptr);

    //Конструктора, принимающего целочисленное значение, для инициализации единичной матрицы указанной размерности
    matrix(int n): dimension(n), Arr(nullptr) {
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
    matrix(int n, const int* a): dimension(n), Arr(nullptr){
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
    ~matrix(){
        if(Arr != nullptr){// Проверка: была ли выделена память и нужно ли её освобождать
            for (int i = 0; i < dimension; ++i) {
                delete[] Arr[i];
            }
            delete[] Arr;
            }
        }

    }





};

matrix::matrix() {

}


int main() {
    system("chcp 65001");

    string user;
    getline(cin, user);

    cout << user;

    return 0;
}
