#pragma once
#include "../Coordinate/Coordinate.h"

class Tile
{
private:
	Coordinate m_coord;
	int m_digit;

public:
	Tile(Coordinate coordinate, int digit) : m_coord{ coordinate }, m_digit{ digit } {}

	Coordinate get_coord() { return m_coord; }
	int& get_digit_ref() { return m_digit; }
	int get_digit() { return m_digit; }
	void set_coord(Coordinate coordinate) { m_coord = coordinate; }
	void set_digit(int new_digit) { m_digit = new_digit; }
};