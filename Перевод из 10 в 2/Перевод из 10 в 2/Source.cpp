#include <iostream>
using namespace std;


void conversionToBinary(int n) {
    if (n > 1) {
        conversionToBinary(n / 2);
    }
    printf_s("%d", n % 2);
}

int main() {
    int decimalNumber;
    printf("Введите число в десятичной системе: ");
    scanf_s("%d", &decimalNumber);

    printf("Число %d в двоичной системе: ", decimalNumber);
    conversionToBinary(decimalNumber);

    return 0;
}
