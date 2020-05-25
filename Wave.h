#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Tower.h"

class Wave :
    public Entity
{
private:
    float timer = 0;
    std::list<Entity*>mobs; //список для мобов
    std::list<Entity*>::iterator it; //итератор списка мобов
    std::list<Entity*>towers; //список для вышек
    std::list<Entity*>::iterator it2; //итератор списка вышек
    std::list<Entity*>bullets; //список для пуль
    std::list<Entity*>::iterator it3; //итератор списка пуль
    int i = 0; //итератор циклов
    int numWave = 0;
public:
    void setNumWave(int i) {
        numWave = i;
    }
    int getNumWave() {
        return numWave;
    }
    void setTimer(float x) {
        timer = x;
    }
    float getTimer() {
        return timer;
    }
    void setIterator(int i) {
        this->i = i;
    }
    int getIterator() {
        return i;
    }
    Wave() {
        setDelay(0);
    }
    sf::String getClass() {
        return "Wave";
    }
    void wave1(float time, sf::RenderWindow &window) {
        if (getNumWave() == 1)
            createMob(5, time, window);
        else if(getNumWave() == 0)
            setTimer(getTimer() + time);
        if (getNumWave() == 0 && getTimer() > 5000)
            setNumWave(1);
    }
    void wave2(float time, sf::RenderWindow& window) {
        if (getTimer() < 14000)
            setTimer(getTimer() + time);
        if (getNumWave() == 2 && getTimer() > 14000)
            createMob(10, time, window);
    }
    void wave3(float time, sf::RenderWindow& window) {
        if (getTimer() < 25000)
            setTimer(getTimer() + time);
        if (getNumWave() == 3 && getTimer() > 25000)
            createMob(20, time, window);
    }
    void wave4(float time, sf::RenderWindow& window) {
        if (getTimer() < 25000)
            setTimer(getTimer() + time);
        if (getNumWave() == 4 && getTimer() > 25000)
            createMob(35, time, window);
    }
    void wave5(float time, sf::RenderWindow& window) {
        if (getTimer() < 30000)
            setTimer(getTimer() + time);
        if (getNumWave() == 5 && getTimer() > 30000)
            createMob(100, time, window);
    }
    void createMob(int value, float time, sf::RenderWindow &window) {
        setDelay(getDelay() - time);
        if (getDelay() <= 0)
            for (getIterator(); getIterator() < value;) {
                getListMobs().push_back(new Plane("plane.png", 150, 0, 50, 55));
                setDelay(2000);
                setIterator(getIterator() + 1);
                return;
            }
        if (getIterator() == value) {
            //game over
            if (getNumWave() == 5 && getIterator() == 100 && getListMobs().empty())
                window.close();
            setTimer(0);
            setNumWave(getNumWave() + 1);
            setIterator(0);
        }
    }
    void createTower(float x, float y) {
        getListTowers().push_back(new Tower("tower.png", x, y, 50, 50));
    }
    void updateMTB(float time) {   
        updateMobs(time);
        updateTowers(time);
        updateBullets(time);
    }
    void updateMobs(float time) {
        ///////////////////////////апдейт информации и мобе и удаление при смерти
        for (getItMobs() = getListMobs().begin(); getItMobs() != getListMobs().end(); ) {
            Entity* mob = *getItMobs();
            mob->move(time, 0.1);
            mob->update(time);
            if (mob->getLife() == false)
            {
                getItMobs() = getListMobs().erase(getItMobs()); delete(mob);
                getItMobs() = getListMobs().begin();
            }
            else getItMobs()++;
        }
    }
    void updateTowers(float time) {
        //поворот и выстрелы башни, их смерть
        for (getItTowers() = getListTowers().begin(); getItTowers() != getListTowers().end(); ) {
            Entity* tow = *getItTowers(); //для удобства
            for (getItMobs() = getListMobs().begin(); getItMobs() != getListMobs().end(); getItMobs()++) {
                tow->update((*getItMobs())->getX(), (*getItMobs())->getY());
            }       //поворот в сторону ближайшего моба
            if (tow->getDelay() <= 0 && tow->getDistance() <= tow->getRange()) {    //если задержка равна нулю, и цель в радиусе атаки
                tow->shot(getListBullets(), 1, time);   //выстрел
                tow->setDelay(4000); //обновление задержки атаки вышки
            }
            tow->setDelay(tow->getDelay() - time); //вычитаем из задержки пройденное время 
            tow->setDistance(1000);     //сброс информации о ближайшем радиусе (после выстрела)
            if (tow->getLife() == false)    //если вышка мертва, то удаляем её
            {
                getItTowers() = getListTowers().erase(getItTowers()); delete(tow);
                getItTowers() = getListTowers().begin();
            }else
                getItTowers()++; //иначе переходим к следующей в списке
        }        
    }
    void updateBullets(float time) {
        ////////////отрисовка пуль, их смерть
        for (getItBullets() = getListBullets().begin(); getItBullets() != getListBullets().end(); ) {
            Entity* bullet = *getItBullets();
            bullet->move(1, time);
            for (getItMobs() = getListMobs().begin(); getItMobs() != getListMobs().end(); getItMobs()++)
                if (bullet->checkCollision((*getItMobs())->getSprite())) {     //если пуля врезалась в самолет
                    bullet->setLife(false);
                    (*getItMobs())->setHealth((*getItMobs())->getHealth() - bullet->getDamage()); //наносится урон - (устанавливается хп мобу(текущее хп - урон пули))
                }
            if (bullet->checkOut())     //проверка вылета пули за карту
                bullet->setLife(false);

            if (bullet->getLife() == false)     //если пуля мертва, то удаляем её
            {
                getItBullets() = getListBullets().erase(getItBullets()); delete(bullet);
                getItBullets() = getListBullets().begin();
            }
            else
                getItBullets()++;   //иначе переходим к следующей в списке
        }
    }
    void start(float time, sf::RenderWindow &window) {
        wave1(time, window);
        wave2(time, window);
        wave3(time, window);
        wave4(time, window);
        wave5(time, window);
       
    }
    std::list<Entity*>& getListMobs() {
        return mobs;
    }
    std::list<Entity*>::iterator& getItMobs() {
        return it;
    }
    std::list<Entity*>& getListTowers() {
        return towers;
    }
    std::list<Entity*>::iterator& getItTowers() {
        return it2;
    }
    std::list<Entity*>& getListBullets() {
        return bullets;
    }
    std::list<Entity*>::iterator& getItBullets() {
        return it3;
    }
    ~Wave() {
        if (!(getListBullets().empty()))
            for (getItBullets() = getListBullets().begin(); getItBullets() != getListBullets().end(); ) {
                getItBullets() = getListBullets().erase(getItBullets());
                delete(*getItBullets());
            }
        if (!(getListTowers().empty()))
        for (getItTowers() = getListTowers().begin(); getItTowers() != getListTowers().end(); ) {
                getItTowers() = getListTowers().erase(getItTowers());
                delete(*getItTowers());
        }
        if (!(getListMobs().empty())) 
        for (getItMobs() = getListMobs().begin(); getItMobs() != getListMobs().end(); ){
            getItMobs() = getListMobs().erase(getItMobs());
            delete (*getItMobs()); 
        }   
    }
};
