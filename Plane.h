#pragma once
#include "Entity.h"
class Plane :
	public Entity
{
public:
	sf::String getClass(){
		return "Plane";
	}
	Plane(sf::String F, int X, int Y, int Width, int Height) {
		setDamage(5);
		setLife(true);
		setX(X); setY(Y); // координаты появления спрайта
		setW(Width); setH(Height); // ширина и высота
		setSpeed(0); setHealth(3); setDX(0); setDY(0);
		imageLoadFromFile(F);
		textureLoadFromImage(getImage());
		spriteSetTexture(getTexture());
		spriteSetTextureRect(getW(), getH());
		setOrigin(getW(), getH());
	}
	Plane() {
		setDamage(5);
		setLife(true);
		setSpeed(0); setHealth(3); setDX(0); setDY(0);
		imageLoadFromFile("plane.png");
		textureLoadFromImage(getImage());
		spriteSetTexture(getTexture());
		setX(150); setY(10); // координаты появления спрайта
		setW(50); setH(55); // ширина и высота
		spriteSetTextureRect(getW(), getH());
		setOrigin(getW(), getH());
	}
	void move(float time, float speed){
			if (getX() == 150 && getY() < 850) {
				moveDown(speed, time);
			}
			else if (getX() < 350 && getY() > 850) {
				moveRight(speed, time);
			}
			else if (getX() > 350 && getX() < 550 && getY() > 150) {
				moveUp(speed, time);
			}
			else if (getX() < 550  && getY() < 150) {
				moveRight(speed, time);	
			}
			else if (getX() > 550 && getX() < 750 && getY() < 850) {
				moveDown(speed, time);
			}
			else if (getX() < 750 && getY() > 850) {
				moveRight(speed, time);
			}
			else if (getX() > 750 && getY() > 150) {
				moveUp(speed, time);
			}
			else if (getX() < 1000 && getY() < 150) {
				moveRight(speed, time);
			}	
			return;
	}
	void update(float time) {
		switch (getDirection()) { // направление движение
			case 0: setDX(getSpeed()); setDY(0); break;
			case 1: setDX(-getSpeed()); setDY(0); break;
			case 2: setDX(0); setDY(getSpeed()); break;
			case 3: setDX(0); setDY(-getSpeed()); break;
		}
		setX(getX()+getDX() * time); // изменение координат
		setY(getY()+getDY() * time);
		spriteSetTextureRect(3-getHealth(), getW(), getH());
		spriteSetPosition(getX(), getY());
	}
};
