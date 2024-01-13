#include "unit.hpp"

#include <SFML/Graphics.hpp>

#include <pugixml.hpp>
#include <string>
#include <vector>

struct Tile {
    int height;
    
    bool wall_ground;
    bool wall_air;
    bool wall_water;

    int texture_id;
};

class Map {
private:
    sf::Vector2i size;
    sf::Rect<int> review_range;

    Tile** tiles;
    
    std::map< std::string, Unit > units;

    std::map< std::string, std::string > params;
public:
    Map( sf::Vector2i size, std::map< std::string, std::string > params , Tile** tiles );
    Map() {};
    
    sf::Vector2i getSize();

    Unit addUnit( std::string name, sf::Vector2f pos, int angle );
    void removeUnit( std::string id );
    
    void update( float d );

    void render( sf::RenderWindow* win, Camera* camera );
};
