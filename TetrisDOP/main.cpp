#include "SFML\Graphics.hpp"
#include "Block.h"
#include "Tetromino.h"
#include "globalvars.h"
#include <vector>
#include <random>
#include <time.h>
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


int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tetris");
	window.setFramerateLimit(60);
	window.setSize(sf::Vector2u(360, 900));
	window.setPosition(sf::Vector2i(400, 0));

	Tetromino currentTetromino;
	currentTetromino = Tetromino::getRandomTetromino();

	vector<Block> blockFilledRows[24];

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
				case sf::Keyboard::Space:
					for (int i = 0; i < 4; i++) {
						//currentTetromino[i].rotate();
					}
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

		window.clear();
		
		if (frameCount >= curSpeed) {
			for (int i = 3; i >= 0; i--) {
				if (currentTetromino.blockList[i].y >= SCREEN_HEIGHT - TILE_SIZE || areBlocksColliding(currentTetromino, blockFilledRows)) {
					for (int j = 0; j < 4; j++) {
						currentTetromino.blockList[j].falling = false;

						blockFilledRows[(SCREEN_HEIGHT - currentTetromino.blockList[j].y + (TILE_SIZE)) / 24].push_back(currentTetromino.blockList[j]);
					}
					currentTetromino = Tetromino::getRandomTetromino();
				}
			}
		}
		
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < blockFilledRows[i].size(); j++) {
				blockFilledRows[i][j].update(&window);
			}
		}
		

		currentTetromino.update(&window);
		

		window.display();

		if (frameCount >= curSpeed) {
			frameCount = 0;
		}

		frameCount++;
	}

	return 0;
}



