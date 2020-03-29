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
						blockList[index] = Block((SCREEN_WIDTH / 2 - TILE_SIZE * 2) + (i * TILE_SIZE), SCREEN_HEIGHT - (TILE_SIZE * 20) + (j * TILE_SIZE), i, j, this->type);
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

	void rotate(vector<Block> blockFilledRows[24], int dir) {
		// dir: 1 = clockwise, -1 = counterclockwise
		int desiredForm = curForm + dir;
		if (desiredForm > 3) {
			desiredForm = 0;
		}
		else if (desiredForm < 0) {
			desiredForm = 3;
		}

		// initial block list
		Block IBL[4] = {blockList[0], blockList[1], blockList[2], blockList[3]};
		// initial rotation block list
		Block IRBL[4] = {Block(), Block(), Block(), Block()};

		int index = 0;
		while (index < 4) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (tetForm[this->type][desiredForm][j][i] == 1) {
						// set the block coords
						Block *temp = &blockList[index];
						temp->setPosition(temp->x + ((i - temp->relativeX) * TILE_SIZE), temp->y + ((j - temp->relativeY) * TILE_SIZE));
						temp->relativeX = i;
						temp->relativeY = j;
						index++;

						IRBL[index - 1] = blockList[index - 1];
					}
				}
			}
		}

		// WALL KICK IMPLEMENTATION
		
		for (int i = 1; i <= 5; i++) {
			bool okay = true;
			for (int j = 0; j < 4; j++) {
				int blockFilledIndex = (SCREEN_HEIGHT - (blockList[j].y + TILE_SIZE)) / TILE_SIZE;
				if (blockList[j].x >= SCREEN_WIDTH || blockList[j].x < 0 || blockList[j].y >= SCREEN_HEIGHT) {
					okay = false;
				}
				else for (int k = 0; k < blockFilledRows[blockFilledIndex].size(); k++) {
					if ((blockList[j].x == blockFilledRows[blockFilledIndex][k].x && blockList[j].y == blockFilledRows[blockFilledIndex][k].y) ) {
						okay = false;
					}
				}
			}
			if (okay) {
				curForm = desiredForm;
				return;
			}
			else if (i < 5) {
				WallKickOffset transform = wkOffsets[type][curForm][i].getOffset(wkOffsets[type][desiredForm][i]);
				int xOffset = transform.x * TILE_SIZE;
				int yOffset = transform.y * TILE_SIZE;
				for (int j = 0; j < 4; j++) {
					blockList[j] = IRBL[j];
					blockList[j].x += xOffset;
					blockList[j].y -= yOffset;
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					blockList[j] = IBL[j];
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