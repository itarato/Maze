#include "types.h"

uint_t opposite_direction(uint_t dir) {
	switch (dir) {
	case CELL_UP: return CELL_DOWN;
	case CELL_DOWN: return CELL_UP;
	case CELL_LEFT: return CELL_RIGHT;
	case CELL_RIGHT: return CELL_LEFT;
	default:
		std::cerr << "Invalid direction mask:" << dir << std::endl;
		exit(1);
	}
}
