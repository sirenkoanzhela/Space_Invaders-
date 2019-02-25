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
		dx = 0.03;//���� ��������.���� ������ ������ ���������
		moveTimer = 0;
	}

	void checkCollisionWithMap(float Dx, float Dy) override//� ��� �������� ������������ � ������
	{

	}
	void move(float time)
	{
		x += dx * time;//���������� �������� �� �����������
		moveTimer += time;//���������� ������
		if (moveTimer > 2000) 
		{ 
			dx *= -1; 
			moveTimer = 0; 
		}//���� ������ �������� 2 ���, �� �������� ����������� �������� ���������,� ������ ����������
	}
	void update(float time)
	{
		move(time);
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		x += dx * time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { isLive = false; }
	}
};