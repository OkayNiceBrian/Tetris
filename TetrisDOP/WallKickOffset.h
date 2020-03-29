#pragma once

struct WallKickOffset {
	
	int x;
	int y;
	
	WallKickOffset() = default;

	WallKickOffset(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
