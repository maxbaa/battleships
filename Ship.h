#ifndef SHIP_H
#define SHIP_H

#include <vector>

class Ship {
public:
	Ship(int size);
	bool isSunk() const;
	void hit();

private:
	int size;
	int hits;
	std::vector<std::pair<int, int>> coordinates;
};
#endif
