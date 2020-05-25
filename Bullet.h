#pragma once
class Bullet :
	public Entity
{
private:
	float tmp;
public:
	void setTmp(float x) {
		tmp = x;
	}
	float getTmp() {
		return tmp;
	}
	Bullet(float speed, float time, int x, int y, float angle, int damage) {
		setLife(true);
		setDamage(damage);
		setAngle(angle);
		setX(x); setY(y); // координаты появления спрайта
		setW(20); setH(20); // ширина и высота
		setSpeed(0.1); setHealth(3); setDX(0); setDY(0);
		imageLoadFromFile("bullet.png");
		textureLoadFromImage(getImage());
		spriteSetTexture(getTexture());
		setOrigin(getW(), getH());
	}
	void move(float speed, float time) {
		diagMove(speed, time);
		spriteSetPosition(getX(), getY());
	}
	void diagMove(float speed, float time) {
		setDistance(speed * time);	//считает сколько бы пролетела пуля, летя она по прямой
		if (getAngle() > 270 && getAngle() < 360) {				//2 четверть
			setTmp(getAngle() - 270);
			setX(getX() - fabs((getDistance() * (cosf(getTmp() * 3.1415926 / 180)))));
			setY(getY() - fabs((getDistance() * (sinf(getTmp() * 3.1415926 / 180)))));
		}
		else if (getAngle() > 180 && getAngle() < 270) {		//3 четверть
			setTmp(getAngle() + 270);
			setX(getX() - fabs((getDistance() * (cosf(getTmp() * 3.1415926 / 180)))));
			setY(getY() + fabs((getDistance() * (sinf(getTmp() * 3.1415926 / 180)))));
		}
		else if (getAngle() > 90 && getAngle() < 180) {		//4 четверть
			setTmp(getAngle() - 90);
			setX(getX() + fabs((getDistance() * (cosf(getTmp() * 3.1415926 / 180)))));
			setY(getY() + fabs((getDistance() * (sinf(getTmp() * 3.1415926 / 180)))));
		}
		else if (getAngle() > 0 && getAngle() < 90) {		//1 четверть
			setTmp(getAngle() + 90);
			setX(getX() + fabs((getDistance() * (cosf(getTmp() * 3.1415926 / 180)))));
			setY(getY() - fabs((getDistance() * (sinf(getTmp() * 3.1415926 / 180)))));
		}
	}
	sf::String getClass() {
		return "Bullet";
	}
};

