#pragma once
#include "SFML/Graphics.hpp"
#include "Unit.h"
class Invader :public Unit
{
public:
	Invader(Image &image, float X, float Y, int W, int H, String Name) :Unit(image, X, Y, W, H, Name) {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.1;//���� ��������.���� ������ ������ ���������
	}

	void checkCollisionWithMap(float Dx, float Dy) override//� ��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				//if (TileMap[i][j] == '0')//���� ������� ��� ������ �����, ��
				//{
				//	if (Dx>0) { x = j * 32 - w; dx = -0.1; }//� ������ ����� �����
				//	if (Dx<0) { x = j * 32 + 32; dx = 0.1; }// � ����� ����� �����
				//}
			}
	}

	void update(float time)
	{

		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		x += dx * time;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { isLive = false; }
	}
	Sprite draw() override
	{
		return sprite;
	}
};