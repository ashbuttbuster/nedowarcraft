#include "map.hpp"

#include <iostream>

Map::Map( sf::Vector2i size, std::map< std::string, std::string > params, Tile** tiles) {
    this->size = size;

    this->params = params;

    this->tiles = new Tile*[size.y];

    for ( int i = 0; i < size.y; i++ ) {
        this->tiles[i] = new Tile[size.x];

        for ( int j = 0; j < size.x; j++ )
            this->tiles[i][j] = tiles[i][j];
    }

    this->review_range = sf::Rect<int>( 64, 64, (size.x - 2) * 64, (size.y - 2) * 64 );
}

sf::Vector2i Map::getSize() {
    return this->size;
}

Unit Map::addUnit( std::string name, sf::Vector2f pos, int angle) {
    Unit unit("data/units/" + name + ".xml", pos, angle);
    
    std::string id(name);

    for ( int i = 0; i < id.size() - 1; i++ )
        if( id[i] == '/')
            id.replace(i,1,"_");

    this->units[id + "_" + std::to_string(this->units.size())] = unit;

    return unit;
}

void Map::removeUnit( std::string id ) {
    this->units.erase(id);
}

void Map::action( sf::Vector2f point, Camera* camera ) {
    for ( auto it = this->units.begin(); it != this->units.end(); it++ ) {
        if ( it->second.hasSelected() )
            it->second.moveTo( point / camera->getScale() - camera->getPosition() );
    }
}

void Map::update( float d ) {
    for( auto it = this->units.begin(); it != this->units.end(); it++ )
        it->second.update( d );
}

void Map::select( sf::Vector2f point, Camera* camera ) {
    for( auto it = this->units.begin(); it != this->units.end(); it++ ) {
        sf::FloatRect rect(
            ( it->second.pos().x + camera->getPosition().x ) * camera->getScale(),
            ( it->second.pos().y + camera->getPosition().y ) * camera->getScale(),
            it->second.size().x * camera->getScale(),
            it->second.size().y * camera->getScale()
        );

        if ( Collision::point2rect( point, rect ))
            it->second.select();
        else
            it->second.deselect();
    }
}

void Map::render( sf::RenderWindow* win, Camera* camera ) {
    float size = 64 * camera->getScale();

    sf::RectangleShape tile( sf::Vector2f( size, size ) );
    tile.setFillColor( sf::Color( 0, 80, 20, 255 ) );
    
    for( int i = 0; i < this->size.y; i++ )
        for( int j = 0; j < this->size.y; j++ ) {
            tile.setPosition( size * j + camera->getPosition().x * camera->getScale(), size * i + camera->getPosition().y * camera->getScale() );
            win->draw(tile);
        }
    
    for ( auto it = this->units.begin(); it != this->units.end(); it++ ) {
        it->second.render(win,camera);
    }
}
