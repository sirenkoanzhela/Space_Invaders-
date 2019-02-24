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

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/space_texture.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом


	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image enemyImage;
	enemyImage.loadFromFile("images/invader.png");

	Unit*p = new Player(heroImage, (window.getSize().x/2), (window.getSize().y-75), 75.0f, 75.0f,"player");//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	

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

		p->update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		for (it = enemies.begin(); it != enemies.end(); it++) { (*it)->update(time); }//для всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update

																						//easyEnemy.update(time);//старый вариант update врага


		window.clear();

		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили символ пробел, то рисуем КОСМОС
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем СТЕНУ


				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}
		for (it = enemies.begin(); it != enemies.end(); it++) {
			window.draw((*it)->draw()); //рисуем entities объекты (сейчас это только враги)
		}
		window.draw(p->draw());//рисуем спрайт объекта p класса player
		window.display();
	}
	return 0;
}