#include <iostream>
#include <vector>
using namespace std;

/* Пример карты, 1 - дорога, 0 не дорога
1 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 0 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
*/

//класс Окружающей среды
class Outside{
/*
	в этом классе будет отображено влияние на объекты среды
	То есть: цвета светофора будут менять зн-е клетки в матрице на 1 - можно ехать, 0 - нельзя
*/
};

//класс стандартного водителя
//(мб потом сделаем классы водителей с разным поведением)
class standart_Car{
    
	public:
        //нужно как-то передать сюда матрицу карты  
    	int x,y,dx,dy;
        vector<int> parameters;
     
     //параметры по умолчанию
	standart_Car(){
		x=0;
		y=0;
		dx=1;
		dy=1;
}
    //метод, задающий параметры объекта, всё завязано на матрице карты
	void SetParameters(int input_x, int input_y,int input_dx,int input_dy){
        x=input_x;
        y=input_y;
        dx=input_dx;
        dy=input_dy;
    }
    //метод, отвечающий за движение по дороге, не учитывает близость 
    //других объектов
     void Calc(){
        //если надо ехать вдоль оси x
        if (x + dx + y +dy> 5){//по-нормальному так: if (Map_city[x+dx][y] == 1)
           SetParameters(x+dx,y,dx+1,0); 
        }
        //если надо ехать вдоль оси y
        else if(x + y + dy +dx< 5){//по-нормальному так: if (Map_city[x][y+dy] == 1)
            SetParameters(x,y+dy,0,dy+1);
        }
        //если с такой скоростью вылетаешь за дорогу, понижаем скорость
        //в конечном итоге, если некуда ехать - стоим
        else{
            SetParameters(x,y,dx-1,dy-1); 
           
        }
    }
	//метод, для извлечение параметров объекта
	//параметры хранятся в массиве parameters
	void GetParameters(){
        
        cout<<x<<endl;
        cout<<y<<endl;
        cout<<dx<<endl;
        cout<<dy<<endl;
        
        parameters.push_back(x);
        parameters.push_back(y);
        parameters.push_back(dx);
        parameters.push_back(dy);
        
    }
    /*
     1)Метод проверка близости к другим объектам
     2)Метод изменения скорости:
     2.1 Просто ускорение
     2.2 При приближении к впереди едущему автомобилю
     2.3 При остановке у светофора
     ....
     */
};


int main()
{
    bool life;
    life= true;
//    int Map_city[100][100]; матрица карты 
//создание объекта класса Car
//в дальнейшем объекты будут создаваться циклом, 
//так как будет много автомобилей
    standart_Car Test_Car;

//1)Задание начальных параметров, всё завязано на матрице карты
//Одним циклом зададим много объектов
    Test_Car.SetParameters(1,0,0,4);//образец


//Бесконечный цикл для запуска симуляции
while (life==true){
    
    //Последовательность действий (надо придумать)
    //Одинаковая для всех, но с разными числами x y dx dy
    Test_Car.Calc(); //передвижение по дороге без учёта близости объектов
    Test_Car.GetParameters();
 /*
 1)Задание начальных параметров, всё завязано на матрице карты
 2)Проверка на близость других объектов
 3)движение
 4)проверка на близость других объектов
 ....
 Также стоит подумать о функции задерживании времени(для понятной визуализации) 
 */
}
return 0;
}

