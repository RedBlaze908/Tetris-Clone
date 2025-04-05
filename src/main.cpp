#include "window/window.h"

int main() {

    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->init();

    return 0;
}