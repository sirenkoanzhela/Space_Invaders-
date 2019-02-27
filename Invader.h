#pragma once
#include "SFML/Graphics.hpp"
#include "Unit.h"
#include <vector>
#include <iostream>
using namespace std;
class Invader :public Unit
{
private:
	float moveTimer;
public:
	Invader(Image &image, float X, float Y, int W, int H, String Name) :Unit(image, X, Y, W, H, Name) {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.03;//даем скорость.этот объект всегда двигается (+УПРАВЛЕНИЕ СКОРОСТЬЮ)
		moveTimer = 0;
	}

	
	void move(float time)
	{
		x = x + dx * time;//реализация движения по горизонтали
		moveTimer += time;//наращиваем таймер
		if (moveTimer > 3000) 
		{ 
			dx = 0;       //ОСТАНАВЛИВАЕТСЯ
			dy = 0.03;            //Задается скорость для движения по горизонтали
			y = y + dy * time;   //Едет ВНИЗ - реализация движения по вертикали

			if (moveTimer > 5000) {
				dy = 0;
				dx = 0.03; 
				x = x + dx * time;
				dx = dx * -1; //смены направления ПО ГОРИЗОНТАЛИ(+возможность ускорения при смене значения)
				moveTimer = 0; //ОБНУЛЕНИЕ таймера
			}
		}  //если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
	}
	void update(float time)
	{
		move(time);
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
	}
};