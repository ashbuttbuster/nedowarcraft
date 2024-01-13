#include "unit.hpp"

Unit::Unit(std::string path, sf::Vector2f pos, int angle) {
    std::vector< sf::Rect<int> > frames;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path.data());
    
    pugi::xml_node xUnit = doc.child("unit");

    for( pugi::xml_node property = xUnit.child("property"); property; property = property.next_sibling("property") )
        this->params[ property.attribute("name").value() ] = property.attribute("value").value();

    for( pugi::xml_node animation = xUnit.child("animation"); animation; animation = animation.next_sibling("animation") ) {
        frames.clear();

        for ( pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling( "frame" ) ) {
            frames.push_back( sf::Rect<int>(
                std::stoi( frame.attribute("x").value() ),
                std::stoi( frame.attribute("y").value() ),
                std::stoi( frame.attribute("w").value() ),
                std::stoi( frame.attribute("h").value() )
            ) );
        }
        
        this->animations[ animation.attribute("name").value() ] = new Animation( animation.attribute("src").value(), frames, animation.attribute("loop").value() );
    }
    
    this->position = pos;
    this->target = pos;
    this->angle = angle;

    this->player = 0;
    this->selected = false;
    this->moving = false;
}

sf::Vector2f Unit::offset() {
    if (this->currentAnimation.length() == 0)
        return sf::Vector2f(0,0);
    else
        return sf::Vector2f(
            std::stof( this->params["center_x"] ) * (float)this->size().x,
            std::stof( this->params["center_y"] ) * (float)this->size().y
        );
}

sf::Vector2f Unit::pos() {
    return this->position;
}

sf::Vector2i Unit::size() {
    return this->animations[this->currentAnimation]->size();
}

void Unit::moveTo(sf::Vector2f pos) { this->target = pos; }

void Unit::move() { this->moving = true; }

void Unit::stop() { this->moving = false; }

void Unit::turn( int angle ) { this->angle = angle; }

void Unit::select() { this->selected = true; }

void Unit::deselect() { this->selected = false; }

bool Unit::hasSelected() { return this->selected; }

void Unit::update( float d ) {
    sf::Vector2f dpos = ( this->target - ( this->position + this->offset() ) );
    float dist = std::sqrt( dpos.x * dpos.x + dpos.y * dpos.y );

    if ( dist > 10 ) {
        this->turn( std::atan2( dpos.y, dpos.x ) * 180 / M_PI + 360 );
        this->move();
    }
    else
        this->stop();

    if (this->moving)
    {
        float velocity_module = std::stof( this->params["speed"] );
        float radians = (float)this->angle * M_PI / 180;
        sf::Vector2f velocity( 
            std::cos( radians ) * velocity_module * d,
            std::sin( radians ) * velocity_module * d
        );

        this->position += velocity;
    }
    
    std::string anim;
    if ( this->moving )
        anim = "walk";
    else
        anim = "stand";
    
    int da = 360 / std::stoi( this->params["directions"] );
    int angle = ( this->angle + da / 2 ) % 360;
    int danim = angle / da * da;
    
    if (this->currentAnimation != ( anim + "_" + std::to_string(danim) ) ) {
        this->currentAnimation = anim + "_" + std::to_string(danim);
        this->animations[this->currentAnimation]->begin();
    }
    else
        this->animations[this->currentAnimation]->next();
}

void Unit::render( sf::RenderWindow* win, Camera* camera ) {
    sf::RectangleShape selectionFrame((sf::Vector2f)this->size());
    
    selectionFrame.setPosition((this->position + camera->getPosition()) * camera->getScale() );
    selectionFrame.setFillColor(sf::Color::Transparent);
    selectionFrame.setOutlineColor(sf::Color::Green);
    selectionFrame.setOutlineThickness(2);

    this->animations[this->currentAnimation]->render(win, (this->position + camera->getPosition()) * camera->getScale(), camera->getScale());

    if (this->selected) {
        win->draw(selectionFrame);
    }
}
