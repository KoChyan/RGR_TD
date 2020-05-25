#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <iostream>
#include "Wave.h"

class Player
{
private:
	//свободна ли клетка (можно ставить вышку или нет) p.s. 1 - ставить можно, а 0 и 2 - нельзя
	int availablePoints[10][10] = {
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{1, 0, 0, 0, 1, 0, 0, 0, 1 ,0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	};
	bool isShopOpen, isPause, life, isSelection, isUpRange, isUpDamage; //Selection - когда активна, то выбирается место для установки вышки и ресуется красный крестик
	sf::Font font;
	sf::Text myHealths;
	sf::Text myCoins;
	int coin, health, posX, posY, x, y;		//координаты курсора относительно гл. спрайта, x и y - координаты в массиве (0...9)
	std::ostringstream playerCoin;
	std::ostringstream playerHealth;
	sf::Vector2i cursorPosition;
	float shopX = 500, shopY = 500;		// координаты центра магазина относительно гл. спрайта
	sf::Sprite spriteShop;
	sf::Texture textureShop;
	sf::Sprite xMarkSprite;
	sf::Texture xMarkTexture;  
	int towers = 0;	//счетчик
public:
	void checkDeath() {
		if (getHealth() <= 0)
			setLife(false);
	}
	int centering(int x) {
		//число сотен
		x /= 100;
		//переводим в сотни без "хвоста" десятков и едениц
		x *= 100;
		//центрируем
		x += 49;
		return x;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setIsSelection(bool value) {
		isSelection = value;
	}
	bool getIsSelection()const {
		return isSelection;
	}
	void setIsUpDamage(bool value) {
		isUpDamage = value;
	}
	bool getIsUpDamage()const {
		return isUpDamage;
	}
	void setIsUpRange(bool value) {
		isUpRange = value;
	}
	bool getIsUpRange()const {
		return isUpRange;
	}
	void drawInf(sf::RenderWindow& window, sf::Event& event) {
		openShop(window, event);
		drawHealth(window);
		drawMark(window);
	}
	void drawMark(sf::RenderWindow& window) {
		if (getIsSelection()) {
			getSpriteXMark().setPosition(getPosX(), getPosY());
			window.draw(getSpriteXMark());
		}
	}
	sf::Sprite & getSpriteShop() {
		return spriteShop;
	}
	sf::Sprite & getSpriteXMark() {
		return xMarkSprite;
	}
	void setShopX(int X) {
		shopX = X;
	}
	int getShopX() const{
		return shopX;
	}
	void setShopY(int Y) {
		shopY = Y;
	}
	int getShopY()const {
		return shopY;
	}
	void openShop(sf::RenderWindow& window, sf::Event& event) {
		while (getIsShopOpen()) {
			checkCLoseShop(event);
			window.draw(getSpriteShop());
			window.draw(getTextPlayerCoins());
			return;
		}
	}
	void checkCLoseShop(sf::Event& event) {
		//проверка клика на крестик
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			if (getPosX() > (getShopX() + 160) && getPosX() < (getShopX() + 200) && getPosY() > (getShopY() - 200) && getPosY() < (getShopY() - 160)){
				setIsShopOpen(false);
			}		
	}
	Player() {
		textureShop.loadFromFile("textures/shop.png");
		spriteShop.setTexture(textureShop);
		getSpriteShop().setOrigin(200, 200);
		getSpriteShop().setPosition(getShopX(), getShopY());
		xMarkTexture.loadFromFile("textures/Xmark.png");
		xMarkSprite.setTexture(xMarkTexture);
		getSpriteXMark().setOrigin(10, 10);
		setIsShopOpen(false);
		setLife(true);
		setCoin(40);
		setHealth(100);
		myCoins.setCharacterSize(45);
		myCoins.setFont(font);
		myCoins.setStyle(sf::Text::Bold);
		myHealths.setCharacterSize(45);
		myHealths.setFont(font);
		myHealths.setStyle(sf::Text::Bold);
		font.loadFromFile("fonts/AireExterior.ttf");
		updateInf();
	}
	void setPosX(int x) {
		posX = x;
	}
	void setPosY(int y) {
		posY = y;
	}
	int getPosX() const{
		return posX;
	}
	int getPosY()const {
		return posY;
	}
	void setCursorPosition(sf::RenderWindow &window) {
		sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);
		setPosX(cursorPosition.x);
		setPosY(cursorPosition.y);
	}
	void checkButtonPressed(sf::Event &event, Wave &wave) {
		checkGeneralButtonPressed(event, wave);
		checkShopButtonPressed(event, wave);
	}
	void setIsShopOpen(bool value) {
		isShopOpen = value;
	}
	bool getIsShopOpen() const{
		return isShopOpen;
	}
	void setIsPause(bool value) {
		isPause = value;
	}
	bool getIsPause()const {
		return isPause;
	}
	void setPlayerCoin() {
		playerCoin << getCoin();
	}
	void setPlayerHealth() {
		playerHealth << getHealth();
	}
	void getDamage(int value) {
		setHealth(getHealth() - value);
	}
	void setCoin(int value) {
		coin = value;
	}
	int getCoin()const {
		return coin;
	}
	void addCoin(int value) {
		coin += value;
	}
	void spendCoin(int cost) {
		setCoin(getCoin() - cost);
	}
	void setLife(bool value) {
		life = value;
	}
	bool getLife()const {
		return life;
	}
	void setHealth(int value) {
		health = value;
	}
	int getHealth()const {
		return health;
	}
	void updateInf() {
		setPlayerCoin();
		setPlayerHealth();
		myCoins.setString("COINS:    " + playerCoin.str());
		myCoins.setPosition(getShopX() - 100, getShopY() + 100);
		myHealths.setString(playerHealth.str());
		myHealths.setPosition(940, 150);
		clearStrings();
	}
	void clearStrings() {
		playerCoin.str("");
		playerCoin.clear();
		playerHealth.str("");
		playerHealth.clear();
	}
	sf::Text getTextPlayerHealths()const{
		return myHealths;
	}
	sf::Text getTextPlayerCoins()const {
		return myCoins;
	}
	void drawHealth(sf::RenderWindow& window) {
		window.draw(getTextPlayerHealths());
	}
	void buyTower(sf::Event &event, Wave &wave) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			//если клетка свободна
			if(isAvailable()){
				wave.createTower(centering(getPosX()), centering(getPosY()));
				setTowers(getTowers() + 1);
				setIsSelection(false);
			}
	}
	void upgradeDamage(sf::Event& event, Wave& wave) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			//есть ли на месте клика вышка
			if (isTowerHere()) {
				for (wave.getItTowers() = wave.getListTowers().begin(); wave.getItTowers() != wave.getListTowers().end(); wave.getItTowers()++)
					// если мы кликнули по спрайту
					if ((*wave.getItTowers())->getSprite().getGlobalBounds().contains(getPosX(), getPosY())) {
						(*wave.getItTowers())->setDamage((*wave.getItTowers())->getDamage() + 1);
						setIsSelection(false);
						setIsUpDamage(false);
					}
			}
	}
	void upgradeRange(sf::Event& event, Wave& wave) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			//есть ли на месте клика вышка
			if (isTowerHere()) {
				for (wave.getItTowers() = wave.getListTowers().begin(); wave.getItTowers() != wave.getListTowers().end(); wave.getItTowers()++)
					// если мы кликнули по спрайту
					if ((*wave.getItTowers())->getSprite().getGlobalBounds().contains(getPosX(), getPosY())) {
						(*wave.getItTowers())->setRange((*wave.getItTowers())->getRange() + 50);
						setIsSelection(false);
						setIsUpRange(false);
					}
			}
	}
	void cleanLists(Wave& wave) {
		//убиваем всех мобов в списке
		for (wave.getItMobs() = wave.getListMobs().begin(); wave.getItMobs() != wave.getListMobs().end(); wave.getItMobs()++)
			(*wave.getItMobs())->setLife(false);
		//убиваем все вышки в списке
		for (wave.getItTowers() = wave.getListTowers().begin(); wave.getItTowers() != wave.getListTowers().end(); wave.getItTowers()++)
			(*wave.getItTowers())->setLife(false);
		//убиваем все пули в списке
		for (wave.getItBullets() = wave.getListBullets().begin(); wave.getItBullets() != wave.getListBullets().end(); wave.getItBullets()++)
			(*wave.getItBullets())->setLife(false);
	}
	void checkShopButtonPressed(sf::Event& event, Wave &wave) {
		//если магазин закрыт и Selection == true (ожидается клик по вышке\карте для апгерйда\постройки
		if (!getIsShopOpen()) {
			if (getIsSelection()) {
				if (getIsUpDamage()) 
					upgradeDamage(event, wave);
				else if (getIsUpRange())
					upgradeRange(event, wave);
				else  
					buyTower(event, wave);
			}	
		}

		//Если магазин открыт
		if(getIsShopOpen())
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				//если выбрали покупку новой вышки
			if (!getIsSelection()) {	//если сейчас не выбирается место установки вышки/вышка для апгрейда
				//если выбрали покупку вышки
				if (getPosX() > (getShopX() - 150) && getPosX() < (getShopX() - 50) && getPosY() > (getShopY() + 50) && getPosY() < (getShopY() + 100))
					if (getCoin() >= 10) {
						spendCoin(10);
						setIsSelection(true);
						setIsShopOpen(false);
					}
				//если выбрали апгрейд урона вышки, если есть на карте хотя бы 1 вышка				
				 if (getPosX() > (getShopX() - 50) && getPosX() < (getShopX() + 50) && getPosY() > (getShopY() + 50) && getPosY() < (getShopY() + 100))
					if (getCoin() >= 20 && getTowers() >= 1){
						spendCoin(20);
						setIsUpDamage(true);
						setIsSelection(true);
						setIsShopOpen(false);
				}
				//если выбрали апгрейд радиуса атаки вышки, если есть на карте хотя бы 1 вышка
				 if (getPosX() > (getShopX() + 50) && getPosX() < (getShopX() + 150) && getPosY() > (getShopY() + 50) && getPosY() < (getShopY() + 100))
					 if (getCoin() >= 20 && getTowers() >= 1){
						 spendCoin(20);
						setIsUpRange(true);
						setIsSelection(true);
						setIsShopOpen(false);
				}
				//апдейт денег игрока после их траты
				updateInf();
			}
	}
	void setTowers(int x) {
		towers = x;
	}
	int getTowers() {
		return towers;
	}
	void checkGeneralButtonPressed(sf::Event& event, Wave &wave) {
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			//проверка открытия магазина
			if (getPosX() > 920 && getPosX() < 1000 && getPosY() > 400 && getPosY() < 440)
			{
				if (!getIsShopOpen()) {
					setIsShopOpen(true);
				}
				else
					setIsShopOpen(false);
			}
		//проверка паузы
			else if (getPosX() > 920 && getPosX() < 1000 && getPosY() > 440 && getPosY() < 480) {
				if (!getIsPause())
				{
					setIsPause(true);
				}
				else { setIsPause(false); }
			}
		//проверка рестарта
			else if ((getPosX() > 920 && getPosX() < 1000 && getPosY() > 480 && getPosY() < 520)) {
					restart(wave);
			}
	}
	void cleanMap() {
		for(int i = 0; i <10; i++)
			for (int j = 0; j < 10; j++) {
				if (availablePoints[i][j] == 2)
					availablePoints[i][j] = 1;
			}
	}
	void checkKill(Wave &wave) {
		for (wave.getItMobs() = wave.getListMobs().begin(); wave.getItMobs() != wave.getListMobs().end(); wave.getItMobs()++) {
			if ((*wave.getItMobs())->getHealth() <= 0) {
				(*wave.getItMobs())->setLife(false);
				addCoin(1);
			}
			else if ((*wave.getItMobs())->checkOut()) {
				(*wave.getItMobs())->setLife(false);
				getDamage(5);
			}
		}
		updateInf();
	}
	bool isAvailable() {
		//перевод координат курсора в координаты массива
		setX(getPosX() / 100);
		setY(getPosY() / 100);
		if (availablePoints[y][x] == 1) {
			//блокируем клетку, помечаем, что там находится вышка
			availablePoints[y][x] = 2;
			return true;
		}
		 return false;
	}		
	bool isTowerHere() {
		setX(getPosX() / 100);
		setY(getPosY() / 100);
		if (availablePoints[y][x] == 2)
			return true;
		return false;
	}
	void restart(Wave &wave) {
		//сбрасываем информацию о доступных местах для установки вышек на карте
		cleanMap();
		//очищаем списки мобов, вышек, пуль
		cleanLists(wave);
		
		//сбрасываем информацию прошедших волн, денег и жизней игрока
		wave.setTimer(0);
		wave.setIterator(0);
		wave.setNumWave(0);
		setHealth(100);
		setCoin(40);
	}
};

