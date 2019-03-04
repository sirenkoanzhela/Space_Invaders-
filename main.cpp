#include <SFML/Graphics.hpp>
#include <string>
#include "map.h"
#include "Player.h"
#include "Invader.h"
#include "Bullet.h"
#include <list>
#include <algorithm>

using namespace sf;
using namespace std;

class Game
{
	RenderWindow*win; ///??????
public:
	Game(RenderWindow*win) {};
	void test(RenderWindow*win)
	{

	}
};
int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Space Invaders");
	RenderWindow*win = &window;
	Game game(win);

	Clock clock;

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/space_texture.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������

	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image enemyImage;
	enemyImage.loadFromFile("images/invader.png");

	Unit*p = new Player(heroImage, (window.getSize().x/2), (window.getSize().y-75), 75.0f, 75.0f,"player");//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	

           //////////////�������� ������////////////////
	list<Unit*>enemies;
	list<Unit*>::iterator it;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++)
		{
			enemies.push_back(new Invader(enemyImage, (10 + 60)*j, i*50, 50.0f, 50.0f, "enemy"));
		}
	}

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (p->ShootingStatus() == true) 
			{ 
			p->makeShot(); 
			enemies.push_back(new Bullet(BulletImage, "Bullet", p->getCoordinateX(), p->getCoordinateY(), 20, 20)); 
			}
			//���� ����������, �� ���������� ����. enum �������� ��� int 
		}


		p->update(time);//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		for (it = enemies.begin(); it != enemies.end();)
		{
			(*it)->update(time);//(�� ���� ��� ���, ��� ���)
			if ((*it)->isAlive() == false) { it = enemies.erase(it); delete (*it); }
			if ((*it)->getRect().intersects(p->getRect())) { (*it)->death(); } //rect() ����� ������������ � rect() ������
			else it++;
		}
		
		window.clear();

		///////////////////////��������� �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //���� ��������� ������ ������, �� ������ ������
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//���� ��������� ������ 0, �� ������ �����


				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);
			}
		for (it = enemies.begin(); it != enemies.end(); it++) {
			window.draw((*it)->draw()); 
		}
		window.draw(p->draw());
		window.display();
	}
	return 0;
}