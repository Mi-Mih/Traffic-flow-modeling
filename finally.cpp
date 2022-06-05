#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <sstream>

using namespace std;

#define WHITE 0
#define GREY 1
#define BLACK 2

int n, e;
int capacity[1000][1000], // Матрица пропускных способнотей
flow[1000][1000],  // Матрица потока
color[1000],      // Цвета для вершин
pred[1000];       // Массив пути
int head, tail;  // Начало, Конец
int q[1000 + 2];      // Очередь, хранящая номера вершин входящих в неё

//Сравнение двух целых значений
int min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}

//Добавить в очередь(мы ступили на вершину)
void enque(int x)
{
    q[tail] = x;     // записать х в хвост
    tail++;          // хвостом становиться следующий элемент
    color[x] = GREY; // Цвет серый (из алгоритма поиска)
}

//Убрать из очереди(Вершина чёрная, на неё не ходить)
int deque()
{
    int x = q[head];  // Записать в х значение головы
    head++;           // Соответственно номер начала очереди увеличивается
    color[x] = BLACK; // Вершина х - отмечается как прочитанная
    return x;         // Возвращается номер х прочитанной вершины
}
//Поиск в ширину
int bfs(int start, int end)
{
    int u, v;
    for (u = 0; u < n; u++) // Сначала отмечаем все вершины не пройденными
        color[u] = WHITE;

    head = 0;   // Начало очереди 0
    tail = 0;   // Хвост 0
    enque(start);      // Вступили на первую вершину
    pred[start] = -1;   // Специальная метка для начала пути
    while (head != tail)  // Пока хвост не совпадёт с головой
    {
        u = deque();       // вершина u пройдена
        for (v = 0; v < n; v++) // Смотрим смежные вершины
        {
            // Если не пройдена и не заполнена
            if (color[v] == WHITE && (capacity[u][v] - flow[u][v]) > 0) {
                enque(v);  // Вступаем на вершину v
                pred[v] = u; // Путь обновляем
            }
        }
    }
    if (color[end] == BLACK) // Если конечная вершина, дошли - возвращаем 0
        return 0;
    else return 1;
}

//Максимальный поток из истока в сток
int max_flow(int source, int stock)
{
    int i, j, u;
    int maxflow = 0;            // Изначально нулевой
    for (i = 0; i < n; i++)  // Зануляем матрицу потока
    {
        for (j = 0; j < n; j++)
            flow[i][j] = 0;
    }
    while (bfs(source, stock) == 0)             // Пока сеществует путь
    {
        int delta = 10000;
        for (u = n - 1; pred[u] >= 0; u = pred[u]) // Найти минимальный поток в сети
        {
            delta = min(delta, (capacity[pred[u]][u] - flow[pred[u]][u]));
        }
        for (u = n - 1; pred[u] >= 0; u = pred[u]) // По алгоритму Форда-Фалкерсона 
        {
            flow[pred[u]][u] += delta;
            flow[u][pred[u]] -= delta;
        }
        maxflow += delta;                       // Повышаем максимальный поток
    }
    return maxflow;
}
vector<string> split(const string& s, vector<string>& res, char delim) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        res.push_back(item);
    }
    return res;
}


int main()
{
    string help;
    //максимальный/минимальный поток (координаты соотв участков)
    int max_x = 0, max_y = 0, min_x = 0, min_y = 0;
    //подключается <fstream> <vector> <string>
    //матрица карты в файле
    vector<vector<int> > input_data;
    //считываем матрицу с файла
    string line;
    ifstream in("input.txt");
    for (int i = 0; getline(in, line); i++) {
        vector<int> vec; //создаем одномерный вектор
        vector<string> res;
        split(line, res, ',');
        for (int j = 0; j < res.size(); j++) {
            vec.push_back(stoi(res[j]));
        
        }
        input_data.push_back(vec);
    }
    in.close();

    //закрыли файл

    //считываем размеры получившийся матрицы
    int column = input_data[0].size();
    int row = input_data.size();
    
    //устанавливаем
    n = row-1;
    setlocale(LC_ALL, "Russian");       // установка вывода (не ввода) русского языка в консоли (только Visual Studio)
    //переменные для циклов
    int i, j;
    //запись с файла в матрицу смежности
    for (i = 0; i < row-1; i++) {
        for (j = 0; j < row-1; j++) {
            capacity[i][j] = input_data[i][j];
            //cout << capacity[i][j];
        }
    }

    //просто вывод, потом можно убрать
    for (i = 0; i < row-1; i++) {
        for (j = 0; j < row-1; j++) {
           
            cout << capacity[i][j] << " ";
        }
        cout << endl;
    }

    //вычисляем максимальный поток через сеть
    int max_potok;
    max_potok = max_flow(0, n-1 );
    cout << "Максимальный поток через сеть: " << max_potok << endl;

    //выводим матрицу распределения потоков
    cout << "Матрица распределения потоков: " << endl;
    for (int i = 0; i < row-1; i++)
    {
        for (int j = 0; j < row-1; j++) {
            cout << flow[i][j] << " ";
        }
        cout << endl;
    }
    //поиск участка с минимальным/максимальным потоком
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (abs(flow[i][j]) >= abs(flow[max_y][max_x])) max_x = j, max_y = i;
            if (abs(flow[i][j]) >= abs(flow[min_y][min_x])) min_x = j, min_y = i;
        }
    }
    //запись матрицы в файл
    ofstream out("flow.txt", ios::out);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            out << flow[i][j] << ",";
        }
        out << ' ' << endl;

    }
    out << "Максимальный поток на участке " << max_x << "-" << max_y << " и равен " << abs(flow[max_y][max_x]) << endl;
    out << "Минимальный поток на участке " << min_x << "-" << min_y << " и равен " << abs(flow[min_y][min_x]) << endl;

    out.close();


    _getche(); //кто это?
    return 0;
}
