#pragma once
#include "Unit.h"
#include <vector>
using namespace std;
class Bullet :public Unit
{
	int direction;
public:
	Bullet(Image &image, String Name, float X, float Y, int W, int H) :Unit (image, X, Y, W, H, Name)
	{
		
		x = X;
		y = Y;
		direction = 0;
		speed = 0.8;
		w = h = 16;
		isLive = true;
	}
	void update(float time) override
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
		case 1: dx = speed; dy = 0;   break;//интовое значение state = right
		case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
		case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению
		case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению 
		case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению
		}

		x += dx * time;//само движение пули по х
		y += dy * time;//по у

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		//for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
		//	if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		//	{
		//		isLive = false;// то пуля умирает
		//	}
		//}

		sprite.setPosition(x + w / 2, y + h / 2);//задается позиция пуле
	}
};
