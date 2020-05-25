
#include <SFML/Graphics.hpp>
#include <list>
#include "Plane.h"
#include "Player.h"
#include "Map.h"
#include "Wave.h"
#include "Tower.h"
#include "Bullet.h"
#include "Menu.h"
int main()
{
    Menu menu;
    Player player;
    sf::Clock clock;
    MyMap map;
    Wave wave;
    float time;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "myTD");
    menu.openMenu(window);
    while (window.isOpen())
    {
        if (player.getLife()) {
            sf::Event event;
            time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time /= 1000;
            player.setCursorPosition(window);
            //Если не стоит пауза, то выполняем
            if (!player.getIsPause()) {
                wave.start(time, window);
                player.checkDeath();
                player.checkKill(wave);
                wave.updateMTB(time); //MTB = mobs, towers, bullets
            }
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                player.checkButtonPressed(event, wave);
            }
            window.clear();
            //отрисовка спрайтов
            window.draw(map.getSprite());
            for (wave.getItTowers() = wave.getListTowers().begin(); wave.getItTowers() != wave.getListTowers().end(); wave.getItTowers()++)
                window.draw((*wave.getItTowers())->getSprite());
            for (wave.getItMobs() = wave.getListMobs().begin(); wave.getItMobs() != wave.getListMobs().end(); wave.getItMobs()++)
                window.draw((*wave.getItMobs())->getSprite());
            for (wave.getItBullets() = wave.getListBullets().begin(); wave.getItBullets() != wave.getListBullets().end(); wave.getItBullets()++)
                window.draw((*wave.getItBullets())->getSprite());

            player.drawInf(window, event); //отрисовка жизней и денег игрока
            window.display();
        }
        else { window.close(); }
    }
    return 0;
}