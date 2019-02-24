#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "Player.h"
#include"Invader.h"
#include <list>
#include <algorithm>

using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Space Invaders");

	Clock clock;

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/space_texture.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������


	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image enemyImage;
	enemyImage.loadFromFile("images/invader.png");

	Unit*p = new Player(heroImage, (window.getSize().x/2), (window.getSize().y-75), 75.0f, 75.0f,"player");//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	

	list<Invader*>enemies;
	list<Invader*>::iterator it;

	for (int i = 0; i < 10; i++)
	{
		enemies.push_back(new Invader(enemyImage, (10+60)*i, 10, 50.0f, 50.0f, "enemy"));
	}

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 500;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p->update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		for (it = enemies.begin(); it != enemies.end(); it++) { (*it)->update(time); }//��� ���� ��������� ������(���� ��� ������ �����,�� ����� ���� � ���� � �������) ���������� �-��� update

																						//easyEnemy.update(time);//������ ������� update �����


		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //���� ��������� ������ ������, �� ������ ������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//���� ��������� ������ 0, �� ������ �����


				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}
		for (it = enemies.begin(); it != enemies.end(); it++) {
			window.draw((*it)->draw()); //������ entities ������� (������ ��� ������ �����)
		}
		window.draw(p->draw());//������ ������ ������� p ������ player
		window.display();
	}
	return 0;
}