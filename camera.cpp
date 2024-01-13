#include "camera.hpp"

Camera::Camera( sf::Vector2f pos, float scale ) {
    this->pos = pos;

    this->scale = scale;

    this->scrolling = false;
    this->angle = 0;
}

Camera::Camera( sf::Vector2f pos ) {
    this->pos = pos;

    this->scale = 1.0;

    this->scrolling = false;
    this->angle = 0;
}

sf::Vector2f Camera::getPosition() {
    return this->pos;
}

void Camera::moveTo( sf::Vector2f pos ) {
    this->pos = pos;
}

void Camera::startScrolling( int angle ) {
    this->angle = angle;
    this->scrolling = true;
}

void Camera::stopScrolling() {
    this->scrolling = false;
}

float Camera::getScale() {
    return this->scale;
}

void Camera::setScale( float scale ) {
    if ( this->scale < MIN_SCALE )
        this->scale = MIN_SCALE;
    else if ( this->scale > MAX_SCALE )
        this->scale = MAX_SCALE;
    else
        this->scale = scale;
}

void Camera::scaling( float delta ) {
    if ( this->scale < MIN_SCALE )
        this->scale = MIN_SCALE;
    else if ( this->scale > MAX_SCALE )
        this->scale = MAX_SCALE;
    else
        this->scale += delta;
}

void Camera::update( float d, float v ) {
    float rad = this->angle * M_PI / 180;

    sf::Vector2f velocity(
        std::cos(rad) * v * d,
        std::sin(rad) * v * d
    );

    if ( this->scrolling ) {
        this->pos += velocity / this->getScale();
    }
}
