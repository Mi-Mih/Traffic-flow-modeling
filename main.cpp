#include <iostream>
#include <vector>
using namespace std;

//класс стандартного водителя
//(мб потом сделаем классы водителей с разным поведением)
class standart_Car{
    
	public:
    
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
    
	//метод, для извлечение параметров объекта
	//параметры хранятся в массиве parameters
	void GetParameters(){
        //cout<<x<<endl;
        //cout<<y<<endl;
        //cout<<dx<<endl;
        //cout<<dy<<endl;
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
    
//создание объекта класса Car
//в дальнейшем объекты будут создаваться циклом, 
//так как будет много автомобилей
    standart_Car Test_Car;

//Бесконечный цикл для запуска симуляции
while (life==true){
    
    //Последовательность действий (надо придумать)
    //Одинаковая для всех, но с разными числами x y dx dy
    Test_Car.SetParameters(1,2,3,4);//образец
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

