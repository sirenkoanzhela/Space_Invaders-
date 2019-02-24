#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Unit {
protected:
	float dx, dy, x, y, speed, moveTimer;//�������� ���������� ������ ��� ������� �����
	int w, h, health;
	bool isLive, isMove;
	enum { left, right, down, stay } state;//��������� ��� ������������ - ��������� �������
	Texture texture;
	Sprite sprite;
	String name;//����� ����� ���� ������, �� �� ����� ������ ������ ����� ��� �����.����� ���� �������� ������ �� ����� � ����� ������� ���� �������� � update � ����������� �� �����
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
