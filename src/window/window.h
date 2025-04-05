#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include <iostream>
#include <string>
#include <vector>

const float cellSize = 35.f;
const int cols = 10;
const int rows = 20;

// [4-0][5-0]
// [4-1][5-1]
// [4-2][5-2]
// [4-3][5-3]

struct block {
	int x;
	int y;
	sf::Color c;
};

class Game {
	std::vector<std::vector<sf::RectangleShape>> grid;
	sf::RenderWindow window;

	sf::Clock deltaClock;
	sf::Clock clock;
	sf::Clock btnClock;
	sf::Event event;
	sf::Text score;
	int Score = 0;
	bool over = false;

	float speedDown = 0.2f;

	sf::Color colors[5] = {sf::Color::Red, sf::Color::Yellow, sf::Color::Green,
						   sf::Color::Blue, sf::Color::Magenta};
	char namePiece = NULL;
	bool rotated = false;
	int rotationCounter = 0;

	std::vector<std::vector<block>> pieces = {
		{ {5,0}, {5,1}, {4,1}, {4,2} }, // Z
		{ {4,0}, {4,1}, {5,1}, {5,2} }, // S
		{ {5,0}, {5,1}, {5,2}, {4,2} }, // J
		{ {4,0}, {4,1}, {4,2}, {5,2} }, // L
		{ {4,0}, {5,0}, {4,1}, {5,1} }, // O
		{ {4,0}, {4,1}, {5,1}, {4,2} }, // T
		{ {4,0}, {4,1}, {4,2}, {4,3} }  // I 
	};

	block piece[4];


	void makeGrid();
	void drawPiece();
	void clearLastPos();
	void drawNewPos();

	void moveDownPiece();
	void moveRight();
	void moveLeft();
	void rotatePiece();

	void checkPoints();
	void updateScore();

public:
	Game();
	~Game();

	void init();
	
};