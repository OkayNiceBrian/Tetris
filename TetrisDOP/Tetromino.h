#pragma once
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "globalvars.h"

struct Tetromino {

	int type;
	int curForm;
	Block blockList[4];

	Tetromino(int type) {
		this->type = type;
		curForm = 0;
		// set the default blocks
		int index = 0;
		while (index < 4) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (tetForm[this->type][0][j][i] == 1) {
						blockList[index] = Block((SCREEN_WIDTH / 2 - TILE_SIZE * 2) + (i * TILE_SIZE), SCREEN_HEIGHT - (TILE_SIZE * 24) + (j * TILE_SIZE), i, j, this->type);
						index++;
					}
				}
			}
		}
	}

	Tetromino() = default;

	void update(sf::RenderWindow * window) {
		for (int i = 3; i >= 0; i--) {
			blockList[i].update(window);
		}
	}

	void rotateRight() {
		curForm++;
		if (curForm > 3) {
			curForm = 0;
		}

		int index = 0;
		while (index < 4) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (tetForm[this->type][curForm][j][i] == 1) {
						// set the block coords
						Block *temp = &blockList[index];
						temp->setPosition(temp->x + ((i - temp->relativeX) * TILE_SIZE), temp->y + ((j - temp->relativeY) * TILE_SIZE));
						temp->relativeX = i;
						temp->relativeY = j;
						index++;
					}
				}
			}
		}
	}

	void rotateLeft() {
		curForm--;
		if (curForm < 0) {
			curForm = 3;
		}

		int index = 0;
		while (index < 4) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (tetForm[this->type][curForm][j][i] == 1) {
						// set the block coords
						Block *temp = &blockList[index];
						temp->setPosition(temp->x + ((i - temp->relativeX) * TILE_SIZE), temp->y + ((j - temp->relativeY) * TILE_SIZE));
						temp->relativeX = i;
						temp->relativeY = j;
						index++;
					}
				}
			}
		}
	}

	void right(vector<Block> blockFilledRows[24]) {
		bool move = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 24; j++) {
				for (int k = 0; k < blockFilledRows[j].size(); k++) {
					if (blockList[i].x + TILE_SIZE == blockFilledRows[j][k].x && blockList[i].y == blockFilledRows[j][k].y) {
						move = false;
					}
				}
			}
			if (blockList[i].x + TILE_SIZE == SCREEN_WIDTH) {
				move = false;
			}
		}
		if (move) {
			for (int i = 0; i < 4; i++) {
				blockList[i].right();
			}
		}
	}
	void left(vector<Block> blockFilledRows[24]) {
		bool move = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 24; j++) {
				for (int k = 0; k < blockFilledRows[j].size(); k++) {
					if (blockList[i].x - TILE_SIZE == blockFilledRows[j][k].x && blockList[i].y == blockFilledRows[j][k].y) {
						move = false;
					}
				}
			}
			if (blockList[i].x == 0) {
				move = false;
			}
		}
		if (move) {
			for (int i = 0; i < 4; i++) {
				blockList[i].left();
			}
		}
	}

	static Tetromino getRandomTetromino() {
		int randomTetInt = rand() % 7;

		return Tetromino(randomTetInt);
	}
};