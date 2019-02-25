#pragma once
#include "SFML/Graphics.hpp"
#include "Unit.h"
#include <vector>
#include <iostream>
using namespace std;
class Invader :public Unit
{
	float moveTimer;
public:
	Invader(Image &image, float X, float Y, int W, int H, String Name) :Unit(image, X, Y, W, H, Name) {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.03;//даем скорость.этот объект всегда двигаетс€
		moveTimer = 0;
	}

	void checkCollisionWithMap(float Dx, float Dy) override//ф ци€ проверки столкновений с картой
	{

	}
	void move(float time)
	{
		x += dx * time;//реализаци€ движени€ по горизонтали
		moveTimer += time;//наращиваем таймер
		if (moveTimer > 2000) 
		{ 
			dx *= -1; 
			moveTimer = 0; 
		}//если прошло примерно 2 сек, то мен€етс€ направление движени€ платформы,а таймер обнул€етс€
	}
	void update(float time)
	{
		move(time);
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
		x += dx * time;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
	}
};