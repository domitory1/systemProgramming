// �� ������� ��������� ���� ������, � ������� ������������� 
// ������ �� ��� ��� �������� ������ ��������

#include <iostream>
#include <random>

int main()
{
    // ��������� ���������� - ����������� ������� �� ����������� � ��������� 
    int n, m;


    // ��������� �������� ��������� ��������
    int start = 0;
    int end = 1000;


    // ������� � ������� ������ � ��������� ����  
    printf("������� ��� ����� ����� ��� ������� ����������� ������: ");
    scanf_s("%d%d", &n, &m);


    // ��������� ������ 
    int** a = new int* [n];
    int** b = new int* [n];
    int** c = new int* [n];


    // �������� ������ ��� ������ ������ �������
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
        b[i] = new int[m];
        c[i] = new int[m];
    }


    // ��������� ������� a � b ���������� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = rand() % (end - start + 1) + start;
            b[i][j] = rand() % (end - start + 1) + start;
        }
    }


    // ���������� ��������������� �������� ������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    // ������� ������� � �������
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