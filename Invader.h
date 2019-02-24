#pragma once
#include "SFML/Graphics.hpp"
#include "Unit.h"
class Invader :public Unit
{
public:
	Invader(Image &image, float X, float Y, int W, int H, String Name) :Unit(image, X, Y, W, H, Name) {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.1;//даем скорость.этот объект всегда двигаетс€
	}

	void checkCollisionWithMap(float Dx, float Dy) override//ф ци€ проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимс€ по элементам карты
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				//if (TileMap[i][j] == '0')//если элемент наш тайлик земли, то
				//{
				//	if (Dx>0) { x = j * 32 - w; dx = -0.1; }//с правым краем карты
				//	if (Dx<0) { x = j * 32 + 32; dx = 0.1; }// с левым краем карты
				//}
			}
	}

	void update(float time)
	{

		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
		x += dx * time;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
	}
	Sprite draw() override
	{
		return sprite;
	}
};