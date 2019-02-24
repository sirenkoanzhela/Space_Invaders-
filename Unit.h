#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Unit {
protected:
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h, health;
	bool isLive, isMove;
	enum { left, right, down, stay } state;//добавляем тип перечисления - состояние объекта
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
public:
	Unit(Image &image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		isLive = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
	virtual void checkCollisionWithMap(float, float) = 0;
	virtual void update(float) = 0;
	virtual Sprite draw() = 0;
};
