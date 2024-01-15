#include "collision.hpp"

bool Collision::point2rect( sf::Vector2f point, sf::FloatRect rect ) {
    return ( point.x > rect.left ) &&
           ( point.x < rect.left + rect.width ) &&
           ( point.y > rect.top ) &&
           ( point.y < rect.top + rect.height );
}

bool Collision::rect2rect( sf::FloatRect rect1, sf::FloatRect rect2 ) {
    sf::Vector2f A( rect1.left, rect1.top );
    sf::Vector2f B( rect1.left + rect1.width, rect1.top );
    sf::Vector2f C( rect1.left + rect1.width, rect1.top + rect1.height );
    sf::Vector2f D( rect1.left, rect1.top + rect1.height );

    return point2rect( A, rect2 ) ||
           point2rect( B, rect2 ) ||
           point2rect( C, rect2) ||
           point2rect( D, rect2);
}
