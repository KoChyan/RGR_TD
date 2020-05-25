#pragma once

 class Entity
{
private:
	float angle, distance; // угол поворота спрайта
	float dx, dy, x, y, speed; // координаты, скорость
	int w, h, health, direction = 0; // направление, ширина и высота, здоровье
	bool life;
	sf::String F;//путь к файлу
	sf::Image image; //sfml изображение
	sf::Texture texture; //sfml текстура
	sf::Sprite sprite; //sfml спрайт
	int CurrentFrame; // фреймы анимаций
	int damage, range;// урон, дальность стрельбы
	int delay; //задержка выстрелов
public:
	bool checkOut() {
		if (getX() > 1000 || getX() < 0 || getY() > 1000 || getY() < 0)
			return true;
		else return false;
	}
	bool checkCollision(sf::Sprite planeSprite){
		if (planeSprite.getGlobalBounds().contains(getX(), getY()))
			return true;
		else return false;
	}
	virtual void shot(std::list<Entity*>& entity, float speed, float time) {;}
	void setDelay(int value) {
		delay = value;
	}
	int getDelay() {
		return delay;
	}
	float getRange() {
		return range;
	}
	void setRange(float value) {
		range = value;
	}
	void setDistance(float x) {
		distance = x;
	}
	float getDistance() {
		return distance;
	}
	void setDamage(int damage) {
		this->damage = damage;
	}
	int getDamage() const{
		return damage;
	}
	void setAngle(float value) {
		angle = value;
	}
	float getAngle() const{
		return angle;
	}
	void spriteSetPosition(float x, float y) {
		sprite.setPosition(x, y);
	}
	void setLife(bool value) {
		life = value;
	}
	bool getLife()const {
		return life;
	}
	void imageLoadFromFile(sf::String F) {
		image.loadFromFile("images/"+F);
	}
	sf::Image &getImage() {
		return image;
	}
	void setDX(float dx) {
		this->dx = dx;
	}
	float getDX()const {
		return dx;
	}
	void setDY(float dy) {
		this->dy = dy;
	}
	float getDY()const {
		return dy;
	}
	void setHealth(int value) {
		health = value;
	}
	int getHealth() const{
		return health;
	}
	void setOrigin(float w, float h) { //точка, относительно которой вращается спрайт
		sprite.setOrigin(w/2, h/2);
	}
	void moveLeft(float speed, float time) {
		setDirection(1);
		setSpeed(speed);
		setAngle(-90);
		spriteSetRotation(getAngle());
	}
	void moveRight(float speed, float time) {
		setDirection(0);
		setSpeed(speed);
		setAngle(90);
		spriteSetRotation(getAngle());
	}
	void moveUp(float speed, float time) {
		setDirection(3);
		setSpeed(speed);
		setAngle(0);
		spriteSetRotation(getAngle());
	}
	void moveDown(float speed, float time) {
		setDirection(2);
		setSpeed(speed);
		setAngle(180);
		spriteSetRotation(getAngle());
	}
	void setX(float X) {
		this->x = X;
	}
	float getX() const {
		return x;
	}
	void setY(float Y) {
		this->y = Y;
	}
	float getY() const {
		return y;
	}
	void setW(int width) {
		w = width;
	}
	int getW() const {
		return w;
	}
	void setH(int height) {
		h = height;
	}
	int getH() const {
		return h;
	}
	void setSpeed(float value) {
		speed = value;
	}
	float getSpeed() const {
		return speed;
	}
	void setDirection(int value) {
		direction = value;
	}
	int getDirection() const {
		return direction;
	}
	void setCurrentFrame(int x) {
		CurrentFrame = x;
	}
	int getCurrentFrame()const {
		return CurrentFrame;
	}
	void textureLoadFromImage(sf::Image image) {
		texture.loadFromImage(image);
	}
	void textureLoadFromFile(sf::String F) {
		texture.loadFromFile("textures/plane.png");
	}
	sf::Texture & getTexture(){  
		return texture;
	}
	void spriteSetTexture(sf::Texture &texture) {
		sprite.setTexture(texture);
	}
	void spriteSetTextureRect(int W, int H) {
		sprite.setTextureRect(sf::IntRect(0, 0, W, H));
	}
	void spriteSetTextureRect(int CurrentFrame, float W, float H) {
		sprite.setTextureRect(sf::IntRect(W * int(CurrentFrame), 0, W, H));
	}
	void spriteSetRotation(float value) {
		sprite.setRotation(value);
	}
	sf::Sprite getSprite() const {
		return sprite;
	}
	virtual void move(float time, float speed) { ; }
	virtual void update(float time) { ; }
	virtual void update(float x, float y) { ; }
	virtual sf::String getClass() = 0;
};

