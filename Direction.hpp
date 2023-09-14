#pragma once

namespace ariel {
	// Defines a direction of a message on the board
	enum class Direction {
		Horizontal,
		Vertical	
	};

    void write(int page, int row, int column, Direction direction, std::string content);

    void read(int page, int row, int column, Direction direction, int length);

    void erase(int page, int row, int column, Direction direction, int length);
}
