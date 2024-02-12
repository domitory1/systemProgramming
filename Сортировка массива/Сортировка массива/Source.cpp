// ДЗ: 1) написать алгоритм для сортировки пузырьковым методом 
//	2) Вынести в отельную функцию алгоритм + сортировка от макси к мин

// Написать алгоритм сортировки массива методом вставки

#include <iostream>
#include <random>

void min_max(int arr[], int demension) {
	for (int i = 0; i < demension; i++) {
		int min = i;
		for (int j = i; j < demension; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}
void max_min(int arr[], int demension) {
	for (int i = 0; i < demension; i++) {
		int max = i;
		for (int j = i; j < demension; j++) {
			if (arr[max] < arr[j]) {
				max = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
	}
}

int main() {
	int demension;
	int start = 0;
	int end = 100;

	printf("Введите размерность массива: ");
	scanf_s("%d", &demension);

	int* a_original = new int[demension];
	int* a_min_max = new int[demension];
	int* a_max_min = new int[demension];

	for (int i = 0; i < demension; i++) {
		a_original[i] = a_min_max[i] = a_max_min[i] = rand() % (end - start + 1) + start;
	}
	
	for (int i = 0; i < demension; i++) {
		printf("%d ", a_original[i]);
	}
	printf("\n\n");

	min_max(a_min_max, demension);
	max_min(a_max_min, demension);

	for (int i = 0; i < demension; i++) {
		printf("%d ", a_min_max[i]);
	}
	printf("\n\n");
	for (int i = 0; i < demension; i++) {
		printf("%d ", a_max_min[i]);
	}

	delete[] a_original;
	delete[] a_min_max;
	delete[] a_max_min;

	return 0;
}
