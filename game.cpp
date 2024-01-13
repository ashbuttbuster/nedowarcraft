#include "game.hpp"
#include <SFML/System/Time.hpp>

#include <iostream>

Game::Game() {
    this->win = new sf::RenderWindow(sf::VideoMode(1024,768),"NedoWarCraft");
    
    std::map< std::string, std::string > params;
    
    Tile** tiles = new Tile*[32];

    for ( int i = 0; i < 32; i++ )
    {
        tiles[i] = new Tile[32];
        for ( int j = 0; j < 32; j++ )
            tiles[i][j] = Tile{0, false, false, false, 0};
    }

    this->camera = new Camera(sf::Vector2f( 0, 0 ));
    this->test = Map(sf::Vector2i(32,32), params, tiles );

    this->test.addUnit("human/knight", sf::Vector2f(500,500),90);
    this->test.addUnit("human/knight", sf::Vector2f(600,500),180);
}

const bool Game::running() const {
    return this->win->isOpen();
}

void Game::render() {
    sf::Font font;
    font.loadFromFile( "data/fonts/main.ttf" );

    this->win->clear( sf::Color::Black );

    //Прорисовка объектов
    this->test.render( this->win, this->camera );

    this->win->display();
}

void Game::pollEvents() {
    this->win->pollEvent(this->event);

    if ( this->event.type == sf::Event::Closed )
        this->win->close();
    
    if ( this->event.type == sf::Event::KeyPressed ) {
            if( this->event.key.code == sf::Keyboard::Up )
                this->camera->startScrolling(90);
            if( this->event.key.code == sf::Keyboard::Down )
                this->camera->startScrolling(270);
            if( this->event.key.code == sf::Keyboard::Left )
                this->camera->startScrolling(0);
            if( this->event.key.code == sf::Keyboard::Right )
                this->camera->startScrolling(180);
    }

    if ( this->event.type == sf::Event::KeyReleased ) {
            if( this->event.key.code == sf::Keyboard::Up )
                this->camera->stopScrolling();
            if( this->event.key.code == sf::Keyboard::Down )
                this->camera->stopScrolling();
            if( this->event.key.code == sf::Keyboard::Left )
                this->camera->stopScrolling();
            if( this->event.key.code == sf::Keyboard::Right )
                this->camera->stopScrolling();
    }


    if ( this->event.type == sf::Event::MouseButtonReleased ) {
        if ( this->event.mouseButton.button == sf::Mouse::Left ) {
        }
        else if ( this->event.mouseButton.button == sf::Mouse::Right ) {
        }
    }

    if ( this->event.type == sf::Event::MouseWheelMoved ) {
        this->camera->scaling( this->event.mouseWheel.delta * 0.05 );
    }
}

void Game::update() {
    if( this->clock.getElapsedTime() >= sf::milliseconds(1000 / 25) ) {
        this->test.update( 1.0 / 25.0 );
        this->camera->update( 1.0 / 25.0, 100.0 );
        this->clock.restart();
    }

    this->pollEvents();
}
