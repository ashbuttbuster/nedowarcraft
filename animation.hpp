#include <SFML/Graphics.hpp>

#include <vector>

class Animation {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    bool loop;
    int frame;
    std::vector< sf::Rect<int> > frames;
public:
    Animation(sf::String path, std::vector< sf::Rect<int> > frames );
    Animation(sf::String path, std::vector< sf::Rect<int> > frames, bool loop);

    sf::Vector2i size();

    void next();
    void prev();
    
    void begin();
    void end();

    void render( sf::RenderWindow* win, sf::Vector2f pos, float scale );
};
