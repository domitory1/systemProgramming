#include <iostream>
#include <random>

using namespace std;

struct Variables {
    float x1;
    float x2;
};
class myClass {
    const int  a, b, c;
    float D;
    struct Variables answer;
public:
    myClass(int a, int b, int c):
    a{a}, b{b}, c{c} // для изменения констант
    {
        this->disc(a, b, c);
    }
    
    void disc(int a, int b, int c) {
        this->D = b*b - 4 * a * c;
        this->solution(a, b, c, D);
    }
    void solution(int a, int b, int c, float D) {
        if (D > 0) {
            answer.x1 = (-b + sqrt(D)) / (2 * a);
            answer.x2 = (-b - sqrt(D)) / (2 * a);
        }
        else if (D == 0) {
            answer.x1 = -b / (2 * a);
        }
    }
    void print() {

        if (D > 0) {
            std::cout << "x1 = " << answer.x1 << " x2 = " << answer.x2 << endl;
        }
        else if (D == 0){
            std::cout << "x1 = " << answer.x1 << endl;
        }
        else {
            std::cout << "Решения нет" << endl;
        }
    }

};

int main()
{
    setlocale(LC_ALL, "rus");

    int start = -50;
    int end = 50;
    myClass* array[10];
    int size = sizeof(array)/sizeof(array[0]);

    for (int i = 0; i < size; i++) {
        int a = rand() % (end - start + 1) + start;
        int b = rand() % (end - start + 1) + start;
        int c = rand() % (end - start + 1) + start;
        array[i] = new myClass(a, b, c);
    }

    for (myClass* item : array) {
        item->print();
    }
}