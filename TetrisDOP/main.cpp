#include "SFML\Graphics.hpp"
#include "Block.h"
#include "globalvars.h"
#include <vector>
#include <random>
#include <time.h>
using namespace std;

Block * getRandomTetromino() {

	static Block toReturn[4];

	int randomTetInt = rand() % 7;

	int index = 0;
	while (index < 4) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (tetForm[randomTetInt][0][j][i] == 1) {
					toReturn[index] = Block((SCREEN_WIDTH / 2 - TILE_SIZE) + (i * TILE_SIZE), SCREEN_HEIGHT - (TILE_SIZE * 24) + (j * TILE_SIZE), randomTetInt);
					index++;
				}
			}
		}
	}

	return toReturn;
}

bool areBlocksColliding(Block * currentTetromino, vector<Block> * blockFilledRows) {
	bool collide = false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 24; j++) {
			for (int k = 0; k < blockFilledRows[j].size(); k++) {

				if (currentTetromino[i].x == blockFilledRows[j][k].x && currentTetromino[i].y + TILE_SIZE == blockFilledRows[j][k].y) {
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

	Block *currentTetromino;
	currentTetromino = getRandomTetromino();

	vector<Block> blockFilledRows[24];

	while (window.isOpen())
	{
		bool move;

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
					move = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 24; j++) {
							for (int k = 0; k < blockFilledRows[j].size(); k++) {
								if (currentTetromino[i].x + TILE_SIZE == blockFilledRows[j][k].x && currentTetromino[i].y == blockFilledRows[j][k].y) {
									move = false;
								}
							}
						}
						if (currentTetromino[i].x == SCREEN_WIDTH) {
							move = false;
						}
					}
					if (move) {
						for (int i = 0; i < 4; i++) {
							currentTetromino[i].right();
						}
					}
					break;
				case sf::Keyboard::Left: 
					move = true;
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 24; j++) {
							for (int k = 0; k < blockFilledRows[j].size(); k++) {
								if (currentTetromino[i].x - TILE_SIZE == blockFilledRows[j][k].x && currentTetromino[i].y == blockFilledRows[j][k].y) {
									move = false;
								}
							}
						}
						if (currentTetromino[i].x - TILE_SIZE == 0) {
							move = false;
						}
					}
					if (move) {
						for (int i = 0; i < 4; i++) {
							currentTetromino[i].left();
						}
					}
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
				if (currentTetromino[i].y >= SCREEN_HEIGHT - TILE_SIZE || areBlocksColliding(currentTetromino, blockFilledRows)) {
					for (int j = 0; j < 4; j++) {
						currentTetromino[j].falling = false;

						blockFilledRows[(SCREEN_HEIGHT - currentTetromino[j].y + (TILE_SIZE)) / 24].push_back(currentTetromino[j]);
					}
					currentTetromino = getRandomTetromino();
				}
			}
		}
		
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < blockFilledRows[i].size(); j++) {
				blockFilledRows[i][j].update(&window);
			}
		}
		for (int i = 3; i >= 0; i--) {
			currentTetromino[i].update(&window);
		}
		

		window.display();

		if (frameCount >= curSpeed) {
			frameCount = 0;
		}

		frameCount++;
	}

	return 0;
}



