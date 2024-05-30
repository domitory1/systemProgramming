#include <iostream>
#include <string>

int main()
{
    int firstTemp;
    int secondTemp;
    int answer;
    char operation;

    printf("Enter a mathemarical example using a temptale «Number Operator Number» (10 + 1): ");
    scanf_s("%d %c %d", &firstTemp, &operation, 1, &secondTemp);

    switch (operation)
    {
        case '+':
            answer = firstTemp + secondTemp;
            printf("%d %c %d %c %d", firstTemp, operation, secondTemp, '=', answer);
            break;
        case '-':
            answer = firstTemp - secondTemp;
            printf("%d %c %d %c %d", firstTemp, operation, secondTemp, '=', answer);
            break;
        case '*':
            answer = firstTemp * secondTemp;
            printf("%d %c %d %c %d", firstTemp, operation, secondTemp, '=', answer);
            break;
        case '/':
            answer = firstTemp / secondTemp;
            printf("%d %c %d %c %d", firstTemp, operation, secondTemp, '=', answer);
            break;
        defaut:
            printf("Invalid operation");
            break;
    }

    return 0;
}
