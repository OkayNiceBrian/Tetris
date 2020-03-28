#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Block.h"
#include "Tetromino.h"
#include "globalvars.h"
#include <vector>
#include <random>
#include <time.h>
#include <iostream>
using namespace std;

bool areBlocksColliding(Tetromino currentTetromino, vector<Block> * blockFilledRows) {
	bool collide = false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < blockFilledRows[j].size(); k++) {

				if (currentTetromino.blockList[i].x == blockFilledRows[j][k].x && currentTetromino.blockList[i].y + TILE_SIZE == blockFilledRows[j][k].y) {
					collide = true;
				}
				
			}
		}
	}

	return collide;
}

void gameOver(vector<Block> *blockFilledRows) {
	for (int i = 0; i < 24; i++) {
		blockFilledRows[i].clear();
	}
}


int main()
{
	int frames = 0;
	sf::Clock clock;

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris");
	window.setFramerateLimit(60);
	window.setSize(sf::Vector2u(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2));
	window.setPosition(sf::Vector2i(400, 0));

	sf::Texture background;
	background.loadFromFile("tetrisBackground.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);
	backgroundSprite.setPosition(0, 0);

	sf::Music music;
	music.openFromFile("tetrisMusicLoop.ogg");
	music.play();
	music.setLoop(true);

	Tetromino currentTetromino;
	currentTetromino = Tetromino::getRandomTetromino();

	vector<Block> blockFilledRows[24];

	clock.restart();

	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed: 
				window.close(); 
				break;
			case sf::Event::KeyPressed: 
				switch (event.key.code) {
				case sf::Keyboard::Right: 
					currentTetromino.right(blockFilledRows);
					break;
				case sf::Keyboard::Left: 
					currentTetromino.left(blockFilledRows);
					break;
				case sf::Keyboard::Down:
					curSpeed = maxSpeed;
					break;
				case sf::Keyboard::X:
					currentTetromino.rotateRight();	
					break;
				case sf::Keyboard::Z:
					currentTetromino.rotateLeft();
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code) {
				case sf::Keyboard::Down:
					curSpeed = gameSpeed;
					break;
				}
			}
		}

		window.clear(sf::Color::Black);

		window.draw(backgroundSprite);
		
		if (frameCount >= curSpeed) {
			for (int i = 3; i >= 0; i--) {
				if (currentTetromino.blockList[i].y >= SCREEN_HEIGHT - TILE_SIZE || areBlocksColliding(currentTetromino, blockFilledRows)) {
					for (int j = 0; j < 4; j++) {
						currentTetromino.blockList[j].falling = false;

						if ((SCREEN_HEIGHT - currentTetromino.blockList[j].y + (TILE_SIZE)) / TILE_SIZE >= 20) {
							gameOver(blockFilledRows);
							break;
						}

						blockFilledRows[(SCREEN_HEIGHT - currentTetromino.blockList[j].y - TILE_SIZE) / TILE_SIZE].push_back(currentTetromino.blockList[j]);
					}
					currentTetromino = Tetromino::getRandomTetromino();
				}
			}
		}
		
		for (int i = 0; i < 24; i++) {

			if (blockFilledRows[i].size() >= 10) {
				for (int j = i; j < 23; j++) {
					for (int k = 0; k < blockFilledRows[j + 1].size(); k++) {
						blockFilledRows[j + 1][k].y += TILE_SIZE;
					}
					blockFilledRows[j] = blockFilledRows[j + 1];
				}
			}

			for (int j = 0; j < blockFilledRows[i].size(); j++) {
				blockFilledRows[i][j].update(&window);
			}
		}
		

		currentTetromino.update(&window);
		
		if (frameCount >= curSpeed) {
			frameCount = 0;
		}

		frames++;

		window.display();

		if (clock.getElapsedTime().asMilliseconds() >= 1000) {
			std::cout << "framerate: " << frames << "\n";
			frames = 0;
			clock.restart();
		}

		frameCount++;
	}

	return 0;
}



