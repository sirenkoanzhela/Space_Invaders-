#pragma once
#include "SFML/Graphics.hpp"
#include "Unit.h"

class Player :public Unit
{
	private:
	int playerScore;
public:
	Player(Image &image, float X, float Y, int W, int H, String Name) :Unit(image, X, Y, W, H, Name)
	{
		state = stay;
		playerScore = 0;
		sprite.setTextureRect(IntRect(4, 19, w, h));
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right;
			speed = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
			speed = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)//ф-ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
			for (int j = x / 32; j<(x + w) / 32; j++)
			{

				if (TileMap[i][j] == '0')//если элемент [ 0 ], то:
				{
					if (Dy>0) { y = i * 32 - h;  dy = 0; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю
					if (Dx>0) { x = j * 32 - w; }//с правым краем карты
					if (Dx<0) { x = j * 32 + 32; }// с левым краем карты
				}
			}
	}

	void update(float time) override
	{
		control();
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right: dx = speed; break;//состояние идти вправо
		case left: dx = -speed; break;//состояние идти влево
		case down: dx = 0; break;//будет состояние во время спуска персонажа (например по лестнице)
		case stay: break;//и здесь тоже		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy * time;
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		if (health <= 0) { isLive = false; }
		if (!isMove) { speed = 0; }
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isShoot = true;
		}
	}
};