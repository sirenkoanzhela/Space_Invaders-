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
		case 0: dx = -speed; dy = 0;   break;//������� �������� state = left
		case 1: dx = speed; dy = 0;   break;//������� �������� state = right
		case 2: dx = 0; dy = -speed;   break;//������� �������� state = up
		case 3: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 4: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 5: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		}

		x += dx * time;//���� �������� ���� �� �
		y += dy * time;//�� �

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;

		//for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
		//	if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
		//	{
		//		isLive = false;// �� ���� �������
		//	}
		//}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	}
};