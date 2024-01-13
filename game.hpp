#include <SFML/Graphics.hpp>

#include <vector>

#include "map.hpp"

class Game {
private:
    sf::RenderWindow* win;
    sf::Event event;
    sf::Clock clock;

    Camera* camera;
    Map test;
public:
    Game();

    const bool running() const;

    void render();
    void pollEvents();
    void update();
};
