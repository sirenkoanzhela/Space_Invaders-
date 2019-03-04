#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Unit {
protected:
	float dx, dy, x, y, speed;
	int w, h, health;
	bool isLive, isMove, isShoot;
	enum { left, right, down, stay } state;//добавл€ем тип перечислени€ - состо€ние объекта
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс дл€ врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени
public:
	Unit(Image &image, float X, float Y, int W, int H, String Name) {
		x = X; y = Y; w = W; h = H; name = Name;
		speed = 0; health = 100; dx = 0; dy = 0;
		isLive = true; isMove = false; isShoot = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	Sprite draw() //отрисовка —ѕ–ј…“ј
	{
		return sprite;
	}

	FloatRect getRect() {  //¬ќ«¬–јўј≈“ ѕ–яћќ”√ќЋ№Ќ»  —ѕ–ј…“ј
		return FloatRect(x, y, w, h);
	}

	bool isAlive()  //¬ќ«¬ј–јўј≈“ —ќ—“ќяЌ»≈ ќЅЏ≈ “ј (жив-не жив)
	{
		return isLive;
	}

	bool ShootingStatus()
	{
		return isShoot;
	}
	void makeShot()
	{
		isShoot = true;
	}
	void death()
	{
		isLive = false;
	}

	float getCoordinateX()
	{
		return x;
	}
	float getCoordinateY()
	{
		return y;
	}
	virtual void update(float) = 0;  
	~Unit() {};
};
