#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
private:
	sf::Texture textureNGame, textureExit, textureBG;
	sf::Sprite spriteNGame, spriteExit, spriteBG;
	int menuNum;
	bool isMenu = true;
public:
	void setIsMenu(bool value) {
		isMenu = value;
	}
	bool getIsMenu() {
		return isMenu;
	}
	void setMenuNum(int x) {
		menuNum = x;
	}
	int getMenuNum() {
		return menuNum;
	}
	sf::Texture& getTextureBG() {
		return textureBG;
	}
	sf::Texture& getTextureNGame() {
		return textureNGame;
	}
	sf::Texture& getTextureExit() {
		return textureExit;
	}
	sf::Sprite& getSpriteBG() {
		return spriteBG;
	}
	sf::Sprite& getSpriteNGame() {
		return spriteNGame;
	}
	sf::Sprite& getSpriteExit() {
		return spriteExit;
	}
	Menu() {
		getTextureBG().loadFromFile("textures/BG.png");
		getSpriteBG().setTexture(getTextureBG());
		getTextureNGame().loadFromFile("textures/newGame.png");
		getSpriteNGame().setTexture(getTextureNGame());
		getTextureExit().loadFromFile("textures/exit.png");
		getSpriteExit().setTexture(getTextureExit());
		getSpriteBG().setOrigin(500, 500);
		getSpriteExit().setOrigin(200, 50);
		getSpriteNGame().setOrigin(200, 50);
		getSpriteBG().setPosition(500, 500);
		getSpriteNGame().setPosition(500, 400);
		getSpriteExit().setPosition(500, 700);
	}
	void openMenu(sf::RenderWindow &window) {
		while (getIsMenu()) {
			window.clear();
			if (sf::IntRect(300, 350, 400, 100).contains(sf::Mouse::getPosition(window)))
				setMenuNum(1);
			if (sf::IntRect(300, 650, 400, 100).contains(sf::Mouse::getPosition(window)))
				setMenuNum(2);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (getMenuNum() == 1)
					setIsMenu(false);
				if (getMenuNum() == 2) {
					window.close();
					setIsMenu(false);
				}
			}
			window.draw(getSpriteBG()); //	фон
			window.draw(getSpriteNGame()); //	new game надпись
			window.draw(getSpriteExit()); // exit надпись
			window.display();
		}
	}
};

