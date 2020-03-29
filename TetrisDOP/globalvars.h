#pragma once
#include "SFML\Graphics.hpp"
#include "WallKickOffset.h"
#include <string>
using namespace std;

const int SCREEN_WIDTH = 240;
// 427 = 16: 9
// 504 = like 21 rows
const int SCREEN_HEIGHT = 427;
const int TILE_SIZE = 24;

int frameCount = 0;
int gameSpeed = 30;
int maxSpeed = 5;
int curSpeed = 30;

string blockTextureNames[7] = {
	"redBlockSprite.png", // Z
	"yellowBlockSprite.png", // o
	"lightBlueBlockSprite.png", // i
	"orangeBlockSprite.png", // L
	"greenBlockSprite.png", // s
	"purpleBlockSprite.png", // t
	"darkBlueBlockSprite.png" // j
};

WallKickOffset wkOffsets[7][4][5] = {
	// Z
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(1, 0), WallKickOffset(1, -1), WallKickOffset(0, 2), WallKickOffset(1, 2)},
	 {WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(-1, -1), WallKickOffset(0, 2), WallKickOffset(-1, 2)}},
	// O
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, -1), WallKickOffset(0, -1), WallKickOffset(0, -1), WallKickOffset(0, -1), WallKickOffset(0, -1)},
	 {WallKickOffset(-1, -1), WallKickOffset(-1, -1), WallKickOffset(-1, -1), WallKickOffset(-1, -1), WallKickOffset(-1, -1)},
	 {WallKickOffset(-1, 0), WallKickOffset(-1, 0), WallKickOffset(-1, 0), WallKickOffset(-1, 0), WallKickOffset(-1, 0)}},
	// I
	{{WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(2, 0), WallKickOffset(-1, 0), WallKickOffset(2, 0)},
	 {WallKickOffset(-1, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 1), WallKickOffset(0, -2)},
	 {WallKickOffset(-1, 1), WallKickOffset(1, 1), WallKickOffset(-2, 1), WallKickOffset(1, 0), WallKickOffset(2, 0)},
	 {WallKickOffset(0, 1), WallKickOffset(0, 1), WallKickOffset(0, 1), WallKickOffset(0, -1), WallKickOffset(0, 2)}},
	// L
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(1, 0), WallKickOffset(1, -1), WallKickOffset(0, 2), WallKickOffset(1, 2)},
	 {WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(-1, -1), WallKickOffset(0, 2), WallKickOffset(-1, 2)}},
	// S
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(1, 0), WallKickOffset(1, -1), WallKickOffset(0, 2), WallKickOffset(1, 2)},
	 {WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(-1, -1), WallKickOffset(0, 2), WallKickOffset(-1, 2)}},
	// T
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(1, 0), WallKickOffset(1, -1), WallKickOffset(0, 2), WallKickOffset(1, 2)},
	 {WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(-1, -1), WallKickOffset(0, 2), WallKickOffset(-1, 2)}},
	// J
	{{WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(1, 0), WallKickOffset(1, -1), WallKickOffset(0, 2), WallKickOffset(1, 2)},
	 {WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0), WallKickOffset(0, 0)},
	 {WallKickOffset(0, 0), WallKickOffset(-1, 0), WallKickOffset(-1, -1), WallKickOffset(0, 2), WallKickOffset(-1, 2)}}
};

constexpr int tetForm[7][4][4][4] = {

	// Z

{ { { 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 } },

  { { 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 0, 0, 0 } },

  { { 0, 0, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 0, 0, 0 } },

  { { 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 0 } } },

		// O

			{ { { 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } } },

			// I

		{ { { 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 } },

		  { { 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 } },

		  { { 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 } },

		  { { 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 } } },

			// L

			  { { { 0, 0, 1, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 1, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 1, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } } }, 

			// S

			  { { { 0, 1, 1, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 1, 0, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } } },

			// T

			{ { { 0, 1, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } } },

			// J

			{ { { 1, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 1, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 } },

			  { { 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 0, 0, 0 } } } };