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

	void checkCollisionWithMap(float Dx, float Dy)//�-��� �������� ������������ � ������
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������� �����
			for (int j = x / 32; j<(x + w) / 32; j++)
			{

				if (TileMap[i][j] == '0')//���� ������� [ 0 ], ��:
				{
					if (Dy>0) { y = i * 32 - h;  dy = 0; }//�� Y ����=>���� � ���(����� �� �����) ��� ������. � ���� ������ ���� ���������� ��������� � ��������� ��� �� �����
					if (Dx>0) { x = j * 32 - w; }//� ������ ����� �����
					if (Dx<0) { x = j * 32 + 32; }// � ����� ����� �����
				}
			}
	}

	void update(float time) override
	{
		control();
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; break;//��������� ���� ������
		case left: dx = -speed; break;//��������� ���� �����
		case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy * time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { isLive = false; }
		if (!isMove) { speed = 0; }
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isShoot = true;
		}
	}
};