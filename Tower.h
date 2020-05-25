#pragma once
#include "Bullet.h"

class Tower : 
	public Entity
{
private:
	float distanceTMP;
	float distance;
public:
	void shot(std::list<Entity*>& bullets, float speed, float time) {
		bullets.push_front(new Bullet(speed, time, getX(), getY(), getAngle(), getDamage()));
	}
	void setDistanceTMP(float x) {
		distanceTMP = x;
	}
	float getDistanceTMP() {
		return distanceTMP;
	}
	sf::String getClass(){
		return "Tower";
	}
	Tower(sf::String F, int X, int Y, int Width, int Height) {
		setLife(true);
		setHealth(11);
		setDamage(1);
		setDelay(0);
		setDistance(1000);
		setRange(220);
		setAngle(0);
		setX(X); setY(Y); // координаты появления спрайта
		setW(Width); setH(Height); // ширина и высота;
		imageLoadFromFile(F);
		textureLoadFromImage(getImage());
		spriteSetTexture(getTexture());
		setOrigin(getW(), getH());
	}
	Tower() {
		setLife(true);
		setHealth(11);
		setDamage(1);
		setDelay(0);
		setDistance(1000);
		setRange(220);
		setAngle(0);
		imageLoadFromFile("tower.png");
		textureLoadFromImage(getImage());
		spriteSetTexture(getTexture());
		setX(250); setY(450); // координаты появления спрайта
		setW(50); setH(50); // ширина и высота
		setOrigin(getW(), getH());
	}
	void update(float mobX, float mobY){
		calculate(mobX, mobY);
		spriteSetPosition(getX(), getY());
		spriteSetRotation(getAngle());
	}
	void calculate(float mobX, float mobY) {
		setDX(fabs(getX() - mobX)); // разница по х
		setDY(fabs(getY() - mobY)); // разница по y

	// если найденное расстояние < текущего, то запишем новое значение
		setDistanceTMP(sqrtf(getDX() * getDX() + getDY() * getDY()));
		if (getDistance() > getDistanceTMP()){
			setDistance(getDistanceTMP());
			
			// высчитаем угол angle поворота башни
			if (getDY() != 0)
				setAngle(asin(getDY() / getDistanceTMP()) * 180.0 / 3.1415926);
			else
			{
				setAngle(acos(getDX() / getDistance()) * 180.0 / 3.1415926);
			}
			////////////////////////////////////корректировка угла по четвертям
			if (getX() > mobX && getY() > mobY)// 2 четверть
				setAngle(270 + getAngle());
			else if (getX() > mobX && getY() < mobY)// 3 четверть
				setAngle(270 - getAngle());
			else if (getX() < mobX && getY() < mobY)// 4 четверть
				setAngle(90 + getAngle());
			else if (getX() < mobX && getY() > mobY)// 1 четверть
				setAngle(90 - getAngle());
		}
	}	
};

