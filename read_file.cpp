#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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

    return 0;
}
