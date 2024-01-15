#include <SFML/Graphics.hpp>

namespace Collision {
    bool point2rect( sf::Vector2f point, sf::FloatRect rect );
    bool rect2rect( sf::FloatRect rect1, sf::FloatRect rect );
}
