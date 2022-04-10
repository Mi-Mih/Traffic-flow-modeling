#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class Cars {
public:
    int x_n;
    int y_n;
    int x_f;
    int y_f;

    void Car_Direction_Right(int x_n, int y_n) {
        x_f = x_n;
        y_f = y_n + 1;
    }
    void Car_Direction_Left(int x_n, int y_n) {
        x_f = x_n;
        y_f = y_n - 1;
    }
    void Car_Direction_Up(int x_n, int y_n) {
        x_f = x_n - 1;
        y_f = y_n;
    }
    void Car_Direction_Down(int x_n, int y_n) {
        x_f = x_n + 1;
        y_f = y_n;
    }
};

void Change_Map(int** map, int x, int y, int x_f, int y_f) {
    map[x][y] = 1;
    map[x_f][y_f] = 2;
};

string Look_Map(int** map, string car_direction, int x, int y) {
    string direction;
    if (car_direction == "right") {
        if ((map[x][y + 2] == 0) && (map[x - 1][y + 1] == 1) && (map[x + 1][y + 1] == 1)) { //условие, что дальше другая полоса
            if (map[x + 1][y] == 1) {
                direction = "down";
            }
            else {
                direction = "up";
            }
        }
        else {
            if (map[x][y + 1] == 1) {
                direction = "right";
            }
            else {
                if (map[x + 1][y] == 1) {
                    direction = "down";
                }
                else {
                    direction = "up";
                }
            }
        }
    }
    else if (car_direction == "left") {
        if ((map[x][y - 2] == 0) && (map[x + 1][y - 1] == 1) && (map[x - 1][y - 1] == 1)) {
            if (map[x - 1][y] == 1) {
                direction = "up";
            }
            else {
                direction = "down";
            }
        }
        else {
            if (map[x][y - 1] == 1) {
                direction = "left";
            }
            else {
                if (map[x - 1][y] == 1) {
                    direction = "up";
                }
                else {
                    direction = "down";
                }
            }
        }
    }
    else if (car_direction == "up") {
        if ((map[x - 2][y] == 0) && (map[x - 1][y - 1] == 1) && (map[x - 1][y + 1] == 1)) {
            if (map[x][y + 1] == 1) {
                direction = "right";
            }
            else {
                direction = "left";
            }
        }
        else {
            if (map[x - 1][y] == 1) {
                direction = "up";
            }
            else {
                if (map[x][y + 1] == 1) {
                    direction = "right";
                }
                else {
                    direction = "left";
                }
            }
        }
    }
    else if (car_direction == "down") {
       
        if ((map[x + 2][y] == 0) && (map[x + 1][y - 1] == 1) && (map[x + 1][y + 1] == 1)) { //Возникла ошибка, нужный нам индекс выходит за пределы матрицы
            if (map[x][y - 1] == 1) {
                direction = "left";
            }
            else {
                direction = "right";
            }
        }
        else {
            if (map[x + 1][y] == 1) {
                direction = "down";
            }
            else {
                if (map[x][y - 1] == 1) {
                    direction = "left";
                }
                else {
                    direction = "right";
                }
            }
        }
    }
    return direction;
};



int main()
{   

    //БЛОК СЧИТЫВАНИЯ ИНФОРМАЦИИ С ФАЙЛА И ЗАПИСЬ В МАТРИЦУ КАРТЫ. НАЧАЛО
    
    //подключается <fstream> <vector> <string>
    //матрица карты в файле
    vector<vector<int> > input_data;
    //считываем матрицу с файла
    string line;
    ifstream in("input.txt");
    for (int i = 0; getline(in, line); i++) {
        vector<int> vec; //создаем одномерный вектор
        for (int j = 0; j < line.size(); j++) {
            //отбрасываем пробелы и переводим в char в int
            //и добавляем vec в двумерный вектор
            if (line[j] - '0' != -16) { 
                //ПРИМЕЧАНИЕ: ТК ПРОБЕЛ ВИДИТСЯ КАК -16, ТО НЕ ОБОЗНАЧАЕМ ОБЪЕКТЫ ЭТИМ ЧИСЛОМ
                //ИНАЧЕ ПРИ СЧИТЫВАНИИ КОД ОТБРОСИТ ЭТОТ ЭЛЕМЕНТ
                vec.push_back(line[j] - '0');
            }
        }
        input_data.push_back(vec);
    }
    in.close();
    //считываем размеры получившийся матрицы
    int column = input_data[0].size();
    int row = input_data.size();
    
    //для дальнейшей работы используем указатели и данные из файла заносим в матрицу карты
    int** map; //взял отсюда https://code-live.ru/post/cpp-array-tutorial-part-2/  
    // создание
    map = new int* [row];    // массив указателей
    for (int i = 0; i < row; i++) {
        map[i] = new int[column];     // инициализация указателей
    }
    //с входного файла заносим данные в матрицу карт map
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            map[i][j] = input_data[i][j];
        }
    }

    //БЛОК СЧИТЫВАНИЯ ИНФОРМАЦИИ С ФАЙЛА И ЗАПИСЬ В МАТРИЦУ КАРТЫ. КОНЕЦ

    // БЛОК НАСТИ. НАЧАЛО
    Cars car;
    //Возникла ошибка что нач положение вышло за пределы матрицы
    int x = car.x_n = 0;
    int y = car.y_n = 0;
    map[x][y] = 2;
    string  car_direction = "right";



    while ((y < row - 1) && (x < column - 1)) {

        string car_direction_next = Look_Map(map, car_direction, x, y);
        if (car_direction_next == "right") {
            car.Car_Direction_Right(x, y);
        }
        else if (car_direction_next == "left") {
            car.Car_Direction_Left(x, y);
        }
        else if (car_direction_next == "up") {
            car.Car_Direction_Up(x, y);
        }
        else if (car_direction_next == "down") {
            car.Car_Direction_Down(x, y);
        }
        int x_f = car.x_f;
        int y_f = car.y_f;
        Change_Map(map, x, y, x_f, y_f);
        x = x_f;
        y = y_f;
        car_direction = car_direction_next;
    }

    //БЛОК НАСТИ. КОНЕЦ

    return 0;
}
