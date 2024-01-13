#include <SFML/Graphics.hpp>
#include <pugixml.hpp>

#include <map>
#include <math.h>

#include "animation.hpp"
#include "camera.hpp"

class Unit {
private:
    sf::Vector2f position;
    int angle;
    
    sf::Vector2f target;

    bool selected;
    bool moving;

    std::string currentAnimation;

    int player;

    std::map< std::string, Animation* > animations;
    std::map< std::string, std::string > params;

    sf::Vector2f offset();

    void move();
    void turn(int angle);
    void stop();
public:
    Unit(std::string path, sf::Vector2f pos, int angle);
    Unit() {};
    
    sf::Vector2i size();
    sf::Vector2f pos();

    void moveTo(sf::Vector2f pos);
    
    void select();
    void deselect();
    
    bool hasSelected();

    void update(float d);

    void render(sf::RenderWindow* win, Camera* camera);
};
