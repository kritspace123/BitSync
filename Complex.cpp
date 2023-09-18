//
// Created by Антон on 18.09.2023.
//

/** Деректива препроцессора. */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class complex_number{
private:
    double Re;
    double Im;
public:
    complex_number():Re(0), Im(0){}
    complex_number(double RE, double IM): Re(RE), Im(IM){}

    //перегрузим оператор +
    complex_number operator+(const complex_number& other) const{
        complex_number Z(Re + other.Re, Im + other.Im);
        return Z;
    }
    complex_number operator-(const complex_number& other) const{
        complex_number Z(Re - other.Re, Im - other.Im);
        return Z;
    }
    complex_number operator*(const complex_number& other) const{
        complex_number Z(Re*other.Re - Im*other.Im, Re*other.Im + other.Re * Im);
        return Z;
    }
    complex_number operator/(const complex_number& other) const{
        double c = other.Re*other.Re + other.Im*other.Im;
        double a = (Re*other.Re - Im*other.Im)/c;
        double b = (other.Re*Im -Re*other.Im)/c;
        complex_number Z(a, b);
        return Z;
    }
    friend ostream& operator<<(ostream& in, const complex_number& other);
    friend istream& operator>>(istream& out, complex_number& other);
};
ostream& operator<<(ostream& out, const complex_number& number){
    out << number.Re << "+"<< number.Im<< "i"<<  endl;
    return out;
}
istream& operator>>(istream& in, complex_number& number){
    in >> number.Re;
    in >> number.Im;
    return in;
}


int main(){
    system("chcp 65001"); // Русификация ввода/вывода
    ifstream In("input.txt"); //открываем файл "input.txt"
    ofstream Out("output.txt"); //открываем файл "output.txt"
    if(!In || !Out){
        cout << "Не удалось открыть файлы"<< endl;
        return 1;
    }
    complex_number Z, K, T;
    In >> Z;
    In >> K;
    In >> T;
    cout << Z << endl << K<< endl;
    cout << Z*K;


    return 0;
}