#include <SFML/System/Vector2.hpp>

#include <math.h>

class Camera {
private:
    sf::Vector2f pos;

    float scale;
    const float MAX_SCALE = 2.0;
    const float MIN_SCALE = 1.0;

    bool scrolling;

    int angle;

public:
    Camera( sf::Vector2f pos, float scale );
    Camera( sf::Vector2f pos );
    Camera() {};

    sf::Vector2f getPosition();
    void moveTo( sf::Vector2f target );

    void startScrolling( int angle );
    void stopScrolling();

    float getScale();
    void setScale( float scale );
    void scaling( float delta );

    void update( float d, float v );
};
