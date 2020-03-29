#pragma once

struct WallKickOffset {
	
	int x;
	int y;
	
	WallKickOffset() = default;

	WallKickOffset(int x, int y) {
		this->x = x;
		this->y = y;
	}

	WallKickOffset getOffset(WallKickOffset that) {
		WallKickOffset toReturn = WallKickOffset(this->x - that.x, this->y - that.y);
		return toReturn;
	}
};
