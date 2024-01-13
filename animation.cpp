#include "animation.hpp"

Animation::Animation(sf::String path, std::vector< sf::Rect<int> > frames ) {
    this->texture.loadFromFile(path);
    this->sprite.setTexture(this->texture);

    this->frames = frames;

    this->loop = false;
    this->frame = 0;
}

Animation::Animation(sf::String path, std::vector< sf::Rect<int> > frames, bool loop ) {
    this->texture.loadFromFile(path);
    this->sprite.setTexture(this->texture);

   this->frames = frames;

    this->loop = loop;
    this->frame = 0;
}

sf::Vector2i Animation::size() {
    return this->frames[this->frame].getSize();
}

void Animation::next() {
    if ( this->frame < this->frames.size() - 1 )
        this->frame++;
    else if ( loop )
        this->frame = 0;
}

void Animation::prev() {
    if ( this->frame > 0 )
        this->frame--;
    else if ( loop )
        this->frame = this->frames.size() - 1;
}

void Animation::begin() { this->frame = 0; }

void Animation::end() { this->frame = this->frames.size() - 1; }

void Animation::render(sf::RenderWindow* win, sf::Vector2f pos, float scale ) {
    sf::Rect<int> current = this->frames[this->frame];
    this->sprite.setTextureRect(current);
    this->sprite.setPosition(pos);
    this->sprite.setScale( scale, scale );
    win->draw(this->sprite);
}
