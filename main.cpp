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

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/space_texture.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения

	Image heroImage;
	heroImage.loadFromFile("images/hero.png");

	Image enemyImage;
	enemyImage.loadFromFile("images/invader.png");

	Unit*p = new Player(heroImage, (window.getSize().x/2), (window.getSize().y-75), 75.0f, 75.0f,"player");//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	

           //////////////СОЗДАНИЕ ВРАГОВ////////////////
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
			//если выстрелили, то появляется пуля. enum передаем как int 
		}


		p->update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		for (it = enemies.begin(); it != enemies.end();)
		{
			(*it)->update(time);//(по сути для тех, кто жив)
			if ((*it)->isAlive() == false) { it = enemies.erase(it); delete (*it); }
			if ((*it)->getRect().intersects(p->getRect())) { (*it)->death(); } //rect() врага пересекается с rect() игрока
			else it++;
		}
		
		window.clear();

		///////////////////////ОТРИСОВКА КАРТЫ/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32)); //если встретили символ пробел, то рисуем КОСМОС
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем СТЕНУ


				s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

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