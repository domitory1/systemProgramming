/*
    1. массив со значениями пикселей
    2. обход контура
    3. заполнение фигуры, если контур замкнут
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};
void generate_matrix (){
    ifstream file("C:\\Users\\sauto\\OneDrive\\Рабочий стол\\учеба\\Математическое моделирование2\\Обход контура.bmp", ios_base::binary);

    if (file.is_open()) {
        int width = 0;
        int height = 0;

        file.seekg(18);
        file.read(reinterpret_cast<char*>(&width), sizeof(int));
        file.read(reinterpret_cast<char*>(&height), sizeof(int));

        char** matrix = new char* [height];
        for (int i = 0; i < height; i++) {
            matrix[i] = new char[width];
        }

        int linePadding = (4 - (width % 4)) % 4;

        std::cout << width << " " << height << " " << linePadding << std::endl;

        file.seekg(54);
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                unsigned char bufer = ' ';
                file.read(reinterpret_cast<char*>(&bufer), sizeof(unsigned char));
                if (static_cast<int>(bufer) == 0) {
                    std::cout << " " << static_cast<int>(bufer) << "  ";
                }
                else {
                    std::cout << static_cast<int>(bufer) << " ";
                }

                matrix[x][y] = bufer;
            }
            std::cout << std::endl;
            file.seekg(linePadding, ios_base::cur);
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
            std:cout << matrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < height; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;

        file.close();
    }
    else {
        std::cout << "Не удалось открыть файл" << std::endl;
    }
}
void renderArray(char array[20][20]) {
    for (int i = 0; i < 20; i++) {
       for (int j = 0; j < 20; j++) {
            std:cout << array[i][j] << ' ';
       }
       std::cout << std::endl;
    }
}
Point startFigure(char array[20][20]) {
    struct Point point;
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < 20; i++) {
            if (array[j][i] == '*') {
                point.x = i;
                point.y = j;
                return point;
            }
        }
    }
}
Point nextReferencePoint(int x, int y) {
    struct Point nextPoint;
    nextPoint.x = x;
    nextPoint.y = y;
    return nextPoint;
}
bool walker(char b[20][20], std::vector<Point>& a, Point startPoint) {
    a.push_back(startPoint);

    bool flagNorth = true;
    bool flagNorthEast = true;
    bool flagEast = true;
    bool flagSouthEast = true;
    bool flagSouth = true;
    bool flagSouthWest = true;
    bool flagWest = true;
    bool flagNorthWest = true;

    while (true) {
        if (flagNorth && (b[a.back().y - 1][a.back().x] == '*')) {
            if ((a.front().x == a.back().x) && (a.front().y == a.back().y - 1)) {
                return true;
            }
            a.push_back(nextReferencePoint(a.back().x, a.back().y - 1));
            flagSouth = false;
        }
        else {
            if (flagNorthEast && (b[a.back().y - 1][a.back().x + 1] == '*')) {
                if ((a.front().x == a.back().x + 1) && (a.front().y == a.back().y - 1)) {
                    return true;
                }
                a.push_back(nextReferencePoint(a.back().x + 1, a.back().y - 1));
                flagSouth = true;
                flagSouthWest = false;
            }
            else {
                if (flagEast && (b[a.back().y][a.back().x + 1] == '*')) {
                    if ((a.front().x == a.back().x + 1) && (a.front().y == a.back().y)) {
                        return true;
                    }
                    a.push_back(nextReferencePoint(a.back().x + 1, a.back().y));
                    flagSouth = true;
                    flagSouthWest = true;
                    flagWest = false;
                }
                else {
                    if (flagSouthEast && (b[a.back().y + 1][a.back().x + 1] == '*')) {
                        if ((a.front().x == a.back().x + 1) && (a.front().y == a.back().y + 1)) {
                            return true;
                        }
                        a.push_back(nextReferencePoint(a.back().x + 1, a.back().y + 1));
                        flagSouth = true;
                        flagSouthWest = true;
                        flagWest = true;
                        flagNorthWest = false;
                    }
                    else {
                        if (flagSouth && (b[a.back().y + 1][a.back().x] == '*')) {
                            if ((a.front().x == a.back().x) && (a.front().y == a.back().y + 1)) {
                                return true;
                            }
                            a.push_back(nextReferencePoint(a.back().x, a.back().y + 1));
                            flagSouth = true;
                            flagSouthWest = true;
                            flagWest = true;
                            flagNorthWest = true;
                            flagNorth = false;
                        }
                        else {
                            if (flagSouthWest && (b[a.back().y + 1][a.back().x - 1] == '*')) {
                                if ((a.front().x == a.back().x - 1) && (a.front().y == a.back().y + 1)) {
                                    return true;
                                }
                                a.push_back(nextReferencePoint(a.back().x - 1, a.back().y + 1));
                                flagSouth = true;
                                flagSouthWest = true;
                                flagWest = true;
                                flagNorthWest = true;
                                flagNorth = true;
                                flagNorthEast = false;
                            }
                            else {
                                if (flagWest && (b[a.back().y][a.back().x - 1] == '*')) {
                                    if ((a.front().x == a.back().x - 1) && (a.front().y == a.back().y)) {
                                        return true;
                                    }
                                    a.push_back(nextReferencePoint(a.back().x - 1, a.back().y));
                                    flagSouth = true;
                                    flagSouthWest = true;
                                    flagWest = true;
                                    flagNorthWest = true;
                                    flagNorth = true;
                                    flagNorthEast = false;
                                    flagEast = false;
                                }
                                else {
                                    if (flagNorthWest && (b[a.back().y - 1][a.back().x - 1] == '*')) {
                                        if ((a.front().x == a.back().x - 1) && (a.front().y == a.back().y - 1)) {
                                            return true;
                                        }
                                        a.push_back(nextReferencePoint(a.back().x - 1, a.back().y - 1));
                                        flagSouth = true;
                                        flagSouthWest = true;
                                        flagWest = true;
                                        flagNorthWest = true;
                                        flagNorth = true;
                                        flagNorthEast = true;
                                        flagEast = true;
                                        flagSouthEast = false;
                                    }
                                    else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void shadingFigure(char b[20][20], std::vector<Point>& a, Point startPoint) {
    
    int min_y;
    int max_y;
    int bufferMinY;
    int bufferMaxY;
    for (Point p1 : a) {
        bufferMinY = p1.y;
        bufferMaxY = p1.y;
        for (Point p2 : a) {
            if (bufferMinY > p2.y) {
                bufferMinY = p2.y;
            }
            if (bufferMaxY < p2.y) {
                bufferMaxY = p2.y;
            }
        }
        min_y = bufferMinY;
        max_y = bufferMaxY;
    }
    for (int i = min_y; i < max_y; i++) {
        int min_x;
        int max_x;
        int bufferMinX;
        int bufferMaxX;
        for (Point p1 : a) {
            if (p1.y == i){
                bufferMinX = p1.x;
                bufferMaxX = p1.x;
                for (Point p2 : a) {
                    if (p2.y == i){
                        if (bufferMinX > p2.x) {
                            bufferMinX = p2.x;
                        }
                        if (bufferMaxX < p2.x) {
                            bufferMaxX = p2.x;
                        }
                    }
                }
                min_x = bufferMinX;
                max_x = bufferMaxX;
            }
        }
        for (int j = min_x; j < max_x; j++) {
            b[i][j] = '*';
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    std::vector<Point> a;
    char b[20][20] = {
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ','*', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', ' ',' ', ' ',' ', ' ',' ', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ','*', '*','*', '*','*', '*','*', '*',' ', ' ',' ', ' ',' ', ' ',' ', ' '},
        {' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' ',' ', ' '}
    };

    renderArray(b);
    Point startPoint = startFigure(b);

    if (walker(b, a, startPoint)) {
        std::cout << "Фигура замкнута" << std::endl;
        shadingFigure(b, a, startPoint);
        renderArray(b);
    } 
    else {
        std::cout << "Фигура не замкнута" << std::endl;
    }

    return 0;
}