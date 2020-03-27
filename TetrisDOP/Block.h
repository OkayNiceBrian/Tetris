#pragma once

#include "SFML\Graphics.hpp"
#include "globalvars.h"
struct Block {
	int x;
	int y;
	int relativeX;
	int relativeY;
	int type; // 0 -> 6 for sprite
	bool falling;

	int frames;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape rect;

	Block() = default;

	Block(int x, int y, int relativeX, int relativeY, int type) {
		this->x = x;
		this->y = y;
		this->relativeX = relativeX;
		this->relativeY = relativeY;
		this->type = type;
		falling = true;

		frames = 0;

		texture.loadFromFile(blockTextureNames[this->type]);
		texture.setSmooth(false);
		sprite = sf::Sprite(texture);
		sprite.setOrigin(0, 24.f);
		sprite.setTexture(texture);
		setPosition(this->x, this->y);
		
	}

	void update(sf::RenderWindow * window) {
		
		if (falling) {
			if (frameCount >= curSpeed) {
				fall();
			}
		}
		
		setPosition(x, y);

		draw(window);

		frames++;
	}

	void fall() {
		setPosition(x, y + TILE_SIZE);
	}

	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
		sprite.setPosition(this->x, this->y);
	}

	void draw(sf::RenderWindow * window) {
		sprite.setTexture(texture);
		(*window).draw(sprite);
	}

	void right() {
		setPosition(x + TILE_SIZE, y);
	}

	void left() {
		setPosition(x - TILE_SIZE, y);
	}
};
