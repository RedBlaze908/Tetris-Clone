#include "window.h"

//Private
void Game::makeGrid(){

    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            grid[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setFillColor(sf::Color::Transparent);
            grid[i][j].setOutlineColor(sf::Color::White);
            grid[i][j].setOutlineThickness(1);
            grid[i][j].setPosition(sf::Vector2f(i * cellSize + (window.getSize().x / 3), j * cellSize + 10));
        }
    }
}

void Game::drawPiece() {
    if (grid[4][0].getFillColor() != sf::Color::Transparent ||
        grid[4][1].getFillColor() != sf::Color::Transparent ||
        grid[4][2].getFillColor() != sf::Color::Transparent ||
        grid[4][3].getFillColor() != sf::Color::Transparent ||
        grid[5][0].getFillColor() != sf::Color::Transparent ||
        grid[5][1].getFillColor() != sf::Color::Transparent ||
        grid[5][2].getFillColor() != sf::Color::Transparent ||
        grid[5][3].getFillColor() != sf::Color::Transparent) {

        over = true;
    }

    rotated = false;
    rotationCounter = 0;
    srand(time(NULL));
    int random = rand() % 7;
    int random2 = rand() % 5;
    switch (random) {
        case 0:
            namePiece = 'Z';
            break;
        case 1:
            namePiece = 'S';
            break;
        case 2:
            namePiece = 'J';
            break;
        case 3:
            namePiece = 'L';
            break;
        case 4:
            namePiece = 'O';
            break;
        case 5:
            namePiece = 'T';
            break;
        case 6:
            namePiece = 'I';
            break;
        default:
            break;
    }

    for (int i = 0; i < 4; ++i) {
        piece[i].x = pieces[random][i].x;
        piece[i].y = pieces[random][i].y;
        piece[i].c = colors[random2];
    }

    Game::drawNewPos();

}

void Game::clearLastPos() {
    grid[piece[0].x][piece[0].y].setFillColor(sf::Color::Transparent);
    grid[piece[1].x][piece[1].y].setFillColor(sf::Color::Transparent);
    grid[piece[2].x][piece[2].y].setFillColor(sf::Color::Transparent);
    grid[piece[3].x][piece[3].y].setFillColor(sf::Color::Transparent);
}

void Game::drawNewPos() {
    grid[piece[0].x][piece[0].y].setFillColor(piece[0].c);
    grid[piece[1].x][piece[1].y].setFillColor(piece[1].c);
    grid[piece[2].x][piece[2].y].setFillColor(piece[2].c);
    grid[piece[3].x][piece[3].y].setFillColor(piece[3].c);
}

void Game::moveDownPiece() {
    Game::clearLastPos();
    
    bool fail = false;

    for (auto& c : piece) {
        if ((c.y + 1) < rows) {
            if (grid[c.x][c.y + 1].getFillColor() != sf::Color::Transparent) {
                fail = true;
                break;
            }
        }
        else fail = true;
    }

    if (!fail) {
        for (auto& c : piece) c.y++;
        Game::drawNewPos();
    }
    else {
        Game::drawNewPos();
        Game::checkPoints();
        Game::drawPiece();
    }
}

void Game::moveRight() {
    Game::clearLastPos();

    bool fail = false;

    for (auto& c : piece) {
        if ((c.x + 1) > cols - 1) {
            fail = true;
            break;
        }
        else if (grid[c.x + 1][c.y].getFillColor() != sf::Color::Transparent) {
            fail = true;
            break;
        }
    }

    if (!fail) for (auto& c : piece) c.x++;

    Game::drawNewPos();
}

void Game::moveLeft() {
    Game::clearLastPos();

    bool fail = false;

    for (auto& c : piece) {
        if ((c.x - 1) == -1) {
            fail = true;
            break;
        }
        else if (grid[c.x - 1][c.y].getFillColor() != sf::Color::Transparent) {
            fail = true;
            break;
        }
    }

    if (!fail) for (auto& c : piece) c.x--;

    Game::drawNewPos();
}

void Game::rotatePiece() {
    std::cout << namePiece << std::endl;
    Game::clearLastPos();
    if (namePiece == 'Z') {
        if (!rotated) {
            if ((piece[0].x - 1) >= 0 && grid[piece[0].x - 1][piece[0].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[0].x -= 2;
                piece[0].y++;
            }
            else return;
            if ((piece[1].y + 1) >= 0 && grid[piece[1].x][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y++;
            }
            else return;
            rotated = true;
        }
        else {
            piece[0].x += 2;
            piece[0].y--;
            piece[1].y--;
            rotated = false;
        }
    }
    else if (namePiece == 'S') {
        if (!rotated) {
            if ((piece[0].x + 2) < 10 && grid[piece[0].x + 2][piece[0].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[0].x += 2;
                piece[0].y++;
            }
            else return;
            if ((piece[1].x + 1) < 10 && grid[piece[1].x + 1][piece[1].y].getFillColor() == sf::Color::Transparent) piece[1].x++;
            else return;
            if ((piece[3].x - 1) >= 0 && grid[piece[3].x - 1][piece[3].y].getFillColor() == sf::Color::Transparent) piece[3].x--;
            else return;
            piece[2].y++;
            rotated = true;
        }
        else {
            piece[0].y--;
            piece[0].x -= 2;
            piece[1].x--;
            piece[2].y--;
            piece[3].x++;
            rotated = false;
        }
    }
    else if (namePiece == 'J') {
        if (rotationCounter == 0) {
            if ((piece[0].x + 1) < 10 && (piece[0].y + 2) < 20 && grid[piece[0].x + 1][piece[0].y + 2].getFillColor() == sf::Color::Transparent) {
                piece[0].x++;
                piece[0].y += 2;
            }
            else return;
            if ((piece[1].y + 1) < 20 && grid[piece[1].x][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y++;
            }
            else return;
            if ((piece[2].x - 1) >= 0 && grid[piece[2].x - 1][piece[2].y].getFillColor() == sf::Color::Transparent) {
                piece[2].x--;
            }
            else return;
            if ((piece[3].y - 1) >= 0 && grid[piece[3].x][piece[3].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[3].y--;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 1) {
            if ((piece[0].x - 2) >= 0 && (piece[0].y + 1) < 20 && grid[piece[0].x - 2][piece[0].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[0].y++;
                piece[0].x -= 2;
            }
            else return;
            if ((piece[1].x - 1) >= 0 && grid[piece[1].x - 1][piece[1].y].getFillColor() == sf::Color::Transparent) {
                piece[1].x--;
            }
            else return;
            if ((piece[3].x + 1) < 10 && grid[piece[3].x + 1][piece[3].y].getFillColor() == sf::Color::Transparent) {
                piece[3].x++;
            }
            else return;
            if ((piece[2].y - 1) >= 0 && grid[piece[2].x][piece[2].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[2].y--;
            }
            else return;
            
            
            ++rotationCounter;
        }
        else if (rotationCounter == 2) {
            if ((piece[0].y - 2) >= 0 && grid[piece[0].x][piece[0].y - 2].getFillColor() == sf::Color::Transparent) {
                piece[0].y -= 2;
            }
            else return;
            if ((piece[1].x + 1) < 10 && (piece[1].y - 1) >= 0 && grid[piece[1].x + 1][piece[1].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y--;
                piece[1].x++;
            }
            else return;
            if ((piece[2].x + 2) < 10 && grid[piece[2].x + 2][piece[2].y].getFillColor() == sf::Color::Transparent) {
                piece[2].x += 2;
            }
            else return;
            if ((piece[3].x + 1) < 10 && (piece[3].y + 1) < 20 && grid[piece[3].x + 1][piece[3].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[3].x++;
                piece[3].y++;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 3) {
            if ((piece[0].x + 1) < 10 && grid[piece[0].x + 1][piece[0].y].getFillColor() == sf::Color::Transparent) {
                piece[0].x++;
            }
            else return;
            if ((piece[2].x - 1) >= 0 && (piece[2].y + 2) < 20 && grid[piece[2].x - 1][piece[2].y + 2].getFillColor() == sf::Color::Transparent) {
                piece[2].y += 2;
                piece[2].x--;
            }
            else return;
            if ((piece[3].x - 2) >= 0 && (piece[3].y + 1) < 20 && grid[piece[3].x - 2][piece[3].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[3].y++;
                piece[3].x -= 2;
            }
            else return;
            if ((piece[1].y + 1) < 10 && grid[piece[1].x][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y++;
            }
            else return;
            
            rotationCounter = 0;
        }
    }
    else if (namePiece == 'L') {
        if (rotationCounter == 0) {
            if ((piece[0].x + 1) < 10 && (piece[0].y + 1) < 20 && grid[piece[0].x + 1][piece[0].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[0].x++;
                piece[0].y++;
            }
            else return;
            if ((piece[2].x - 1) >= 0 && (piece[2].y - 1) >= 0 && grid[piece[2].x - 1][piece[2].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[2].x--;
                piece[2].y--;
            }
            else return;
            if ((piece[3].x - 2) >= 0 && grid[piece[3].x - 2][piece[3].y].getFillColor() == sf::Color::Transparent) {
                piece[3].x -= 2;
            }
            else return;
            
            
            ++rotationCounter;
        }
        else if (rotationCounter == 1) {
            if ((piece[0].y + 2) < 20 && grid[piece[2].x][piece[0].y + 2].getFillColor() == sf::Color::Transparent) {
                piece[0].y += 2;
            }
            else return;
            if ((piece[1].y + 1) < 20 && (piece[1].x + 1) < 10 && grid[piece[1].x + 1][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].x++;
                piece[1].y++;
            }
            else return;
            if ((piece[2].x + 2) < 10 && grid[piece[2].x + 2][piece[2].y].getFillColor() == sf::Color::Transparent) {
                piece[2].x += 2;
            }
            else return;
            if ((piece[3].x + 1) < 10 && (piece[3].y - 1) >= 0 && grid[piece[3].x + 1][piece[3].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[3].x++;
                piece[3].y--;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 2) {
            if ((piece[0].x - 2) >= 0 && grid[piece[0].x - 2][piece[0].y].getFillColor() == sf::Color::Transparent) {
                piece[0].x -= 2;
            }
            else return;
            if ((piece[1].x - 1) >= 0 && (piece[1].y + 1) < 20 && grid[piece[1].x - 1][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y++;
                piece[1].x--;
            }
            else return;
            if ((piece[2].y + 2) < 20 && grid[piece[2].x][piece[2].y + 2].getFillColor() == sf::Color::Transparent) {
                piece[2].y += 2;
            }
            else return;
            if ((piece[3].x + 1) < 10 && (piece[3].y + 1) < 20 && grid[piece[3].x + 1][piece[3].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[3].x++;
                piece[3].y++;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 3) {
            if ((piece[0].y - 2) >= 0 && grid[piece[0].x][piece[0].y - 2].getFillColor() == sf::Color::Transparent) {
                piece[0].y -= 2;
            }
            else return;
            if ((piece[1].x - 1) >= 0 && (piece[1].y - 1) >= 0 && grid[piece[1].x - 1][piece[1].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[1].x--;
                piece[1].y--;
            }
            else return;
            if ((piece[2].x - 2) >= 0 && grid[piece[2].x - 2][piece[2].y].getFillColor() == sf::Color::Transparent) {
                piece[2].x -= 2;
            }
            else return;
            if ((piece[3].x - 1) >= 0 && (piece[3].y - 1) >= 0 && grid[piece[3].x - 1][piece[3].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[3].y--;
                piece[3].x--;
            }
            else return;
            rotationCounter = 0;
        }
    }
    else if (namePiece == 'T') {
        if (rotationCounter == 0) {
            if ((piece[0].x - 1) >= 0 && (piece[0].y + 1) < 20 && grid[piece[0].x - 1][piece[0].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[0].x--;
                piece[0].y++;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 1) {
            if ((piece[2].x - 1) >= 0 && (piece[2].y - 1) >= 0 && grid[piece[2].x - 1][piece[2].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[2].y--;
                piece[2].x--;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 2) {
            if ((piece[2].x + 1) < 10 && (piece[2].y + 1) < 20 && grid[piece[2].x + 1][piece[2].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[2].y++;
                piece[2].x++;
            }
            else return;
            if ((piece[0].x + 1) < 10 && (piece[0].y - 1) >= 0 && grid[piece[0].x + 1][piece[0].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[0].y--;
                piece[0].x++;
            }
            else return;
            if ((piece[3].x - 1) >= 0 && (piece[3].y - 1) >= 0 && grid[piece[3].x - 1][piece[3].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[3].x--;
                piece[3].y--;
            }
            else return;
            ++rotationCounter;
        }
        else if (rotationCounter == 3) {
            if ((piece[3].x + 1) < 10 && (piece[3].y + 1) < 20 && grid[piece[3].x + 1][piece[3].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[3].y++;
                piece[3].x++;
            }
            else return;
            rotationCounter = 0;
        }
    }
    else if (namePiece == 'I') {
        if (!rotated) {
            if ((piece[0].x + 1) < 10 && (piece[0].y + 2) < 20 && grid[piece[0].x + 1][piece[0].y + 2].getFillColor() == sf::Color::Transparent) {
                piece[0].x++;
                piece[0].y += 2;
            }
            else return;
            if ((piece[1].y + 1) < 20 && (piece[1].x - 1) >= 0 && grid[piece[1].x - 1][piece[1].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[1].x--;
                piece[1].y++;
            }
            else return;
            if ((piece[3].y - 1) >= 0 && (piece[3].x - 2) >= 0 && grid[piece[3].x - 2][piece[3].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[3].x -= 2;
                piece[3].y--;
            }
            else return;
            rotated = true;
        }
        else {
            if ((piece[0].x - 1) >= 0 && (piece[0].y - 2) >= 0 && grid[piece[0].x - 1][piece[0].y - 2].getFillColor() == sf::Color::Transparent) {
                piece[0].y -= 2;
                piece[0].x--;
            }
            else return;
            if ((piece[1].y - 1) >= 0 && (piece[1].x + 1) < 10 && grid[piece[1].x + 1][piece[1].y - 1].getFillColor() == sf::Color::Transparent) {
                piece[1].y--;
                piece[1].x++;
            }
            else return;
            if ((piece[3].y + 1) < 20 && (piece[3].x + 2) < 10 && grid[piece[3].x + 2][piece[3].y + 1].getFillColor() == sf::Color::Transparent) {
                piece[3].y++;
                piece[3].x += 2;
            }
            else return;
            rotated = false;
        }
    }
    Game::drawNewPos();
}

void Game::checkPoints() {
    int counter = 0;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[j][i].getFillColor() != sf::Color::Transparent) counter++;
        }
        if (counter == 10) {
            Game::updateScore();
            for (int j = 0; j < 10; ++j) grid[j][i].setFillColor(sf::Color::Transparent);

            for (int k = i; k > 0; --k) {
                for (int j = 0; j < 10; ++j) {
                    if (grid[j][k-1].getFillColor() != sf::Color::Transparent) {
                        grid[j][k].setFillColor(grid[j][k-1].getFillColor());
                        grid[j][k - 1].setFillColor(sf::Color::Transparent);
                    }
                }
            }
        }
        counter = 0;
    }
    
}

void Game::updateScore(){
    Score += 100;
    score.setString("Score: " + std::to_string(Score));
}



//Public
Game::Game() {}

Game::~Game() {}

void Game::init() {
    window.create(sf::VideoMode(sf::Vector2u(1280, 720)), "Tetris Multiplayer | RedBlaze908");

    grid.resize(cols, std::vector<sf::RectangleShape>(rows));

    sf::Font font;
    if (!font.loadFromFile("../../../src/font/Tetris.ttf")) {
        std::cerr << "Error While Trying to load the font!" << std::endl;
        exit(EXIT_FAILURE);
    }

    score.setFont(font);
    score.setCharacterSize(38);
    score.setFillColor(sf::Color::White);
    score.setString("Score: 0");
    score.setPosition(sf::Vector2f(window.getSize().x / 2 + 200, 100));

    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

    makeGrid();
    drawPiece();

    bool timerExpired = false;

    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::moveLeft();
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::moveRight();
                btnClock.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                speedDown = 0.05f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
                btnClock.getElapsedTime().asSeconds() >= 0.1f) {

                Game::rotatePiece();
                btnClock.restart();
            }
        }

        sf::Time deltaTime = deltaClock.restart();

        if (clock.getElapsedTime().asSeconds() >= speedDown && !over) {
            Game::moveDownPiece();
            clock.restart();
            speedDown = 0.2f;
        }

        ImGui::SFML::Update(window, deltaTime);
        
        

        window.clear();

        if (!over) window.draw(score);
        else {
            score.setStyle(sf::Text::Underlined);
            window.draw(score);
        }

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 20; ++j) {
                window.draw(grid[i][j]);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}


