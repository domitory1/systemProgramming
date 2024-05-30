// ДЗ сделать умножение двух матриц, с разными размерностями 
// залить на гит две поседние версии прогрммы

#include <iostream>
#include <random>

int main()
{
    // Объявляем переменные - размерность матрицу по горизонтали и вертикали 
    int n, m;


    // Объявляем диапазон случайных значений
    int start = 0;
    int end = 1000;


    // Выводим в консоль строку и считываем ввод  
    printf("Введите два целых числа для задания размерности матриц: ");
    scanf_s("%d%d", &n, &m);


    // Объявляем массив 
    int** a = new int* [n];
    int** b = new int* [n];
    int** c = new int* [n];


    // Выделяем память под каждую строку массива
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
        b[i] = new int[m];
        c[i] = new int[m];
    }


    // Заполняем матрицы a и b случайными числами
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = rand() % (end - start + 1) + start;
            b[i][j] = rand() % (end - start + 1) + start;
        }
    }


    // Складываем соответствующие элементы матриц
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    // Выводим матрицы в консоль
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("    ");
        for (int j = 0; j < m; j++) {
            printf("%d ", b[i][j]);
        }
        printf("    ");
        for (int j = 0; j < m; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        delete[] a[i];
        delete[] b[i];
        delete[] c[i];
    }
    delete[] a;
    delete[] a;
    delete[] b;


    return 0;
}