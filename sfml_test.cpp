#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>
#include "AnimatedSprite.h"

int main()
{

    sf::Texture texture_gradient = loadTexture("gradient.png");
    texture_gradient.setRepeated(true);
    sf::Texture texture_bg3 = loadTexture("bg3.png");
    texture_bg3.setRepeated(true);
    sf::Texture texture_bird = loadTexture("bird.png");
    sf::Texture texture_water = loadTexture("water2.png");
    texture_water.setRepeated(true);
    sf::Texture texture_tree1 = loadTexture("tree_4.png");
    texture_tree1.setRepeated(true);
    sf::Texture texture_tree2 = loadTexture("tree_6.png");
    texture_tree2.setRepeated(true);
    sf::Texture texture_fish = loadTexture("fish.png");

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
    {
        std::cerr << "File Arial.ttf not found !" << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(900, 600), "Lab 9");
    window.setFramerateLimit(60);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(48);
    text.setStyle(sf::Text::Bold);
    text.setPosition(820, 30);

    const int velocity = 40;

    std::vector<sf::Sprite> landscape;

    sf::Sprite gradient;
    gradient.setTexture(texture_gradient);
    gradient.setPosition(0, 0);
    gradient.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    landscape.emplace_back(gradient);

    sf::Sprite bg3;
    bg3.setTexture(texture_bg3);
    bg3.setPosition(0, 250);
    bg3.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 180));
    landscape.emplace_back(bg3);

    sf::Sprite tree1;
    tree1.setTexture(texture_tree1);
    tree1.setPosition(0, 100);
    tree1.setTextureRect(sf::IntRect(0, 0, 275, 280));
    landscape.emplace_back(tree1);

    sf::Sprite tree2;
    tree2.setTexture(texture_tree2);
    tree2.setPosition(620, 220);
    tree2.setTextureRect(sf::IntRect(0, 0, 127, 120));
    landscape.emplace_back(tree2);

    sf::Sprite water;
    water.setTexture(texture_water);
    water.setPosition(0, 400);
    water.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 200));
    landscape.emplace_back(water);

    AnimatedSprite bird;
    bird.setTexture(texture_bird);
    bird.setPosition(60, 60);
    bird.setSpeed(160, 0);

    std::srand(std::time(NULL));
    int fish_x = rand() % 600 + 150;
    
    AnimatedSprite fish;
    fish.setTexture(texture_fish);
    fish.setPosition(fish_x, 530);
    fish.setSpeed(80, 0);

    for (int i = 0; i < (4 * 48); i += 48)
    {
        bird.add_animation_frame(sf::IntRect(i, 0, 48, 48));
    }
    int bird_face = 0;
    int score = 0;
    int fish_exist = 1;

    sf::Clock clock;
    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Closing the window" << std::endl;
                window.close();
            }
        }

        // LOGIC
        const sf::Time elapsed = clock.restart();

        bird.step(elapsed);
        bird.animate(elapsed);
        fish.step(elapsed);
        fish.animate(elapsed);

        

        window.display();
        if (fish.getPosition().x > 852)
        {
            fish.setSpeed(-80, 0);
            fish.scale(-1.f, 1.f);
        }
        else if (fish.getPosition().x < 48)
        {
            fish.setSpeed(80, 0);
            fish.scale(-1.f, 1.f);
        }
        if (bird.getPosition().x < 48)
        {
            bird.setPosition(49, 60);
        }
        if (bird.getPosition().x > 852)
        {
            bird.setPosition(851, 60);
        }
        if (bird.getPosition().y > 552)
        {
            score -= 1;
            bird.setPosition(60, 60);
            bird.setSpeed(160, 0);
            if (bird_face == 1)
            {
                bird.scale(-1.f, 1.f);
                bird_face = 0;
                
            }
        }
        sf::FloatRect fish_bounds = fish.getGlobalBounds();
        if (bird.getGlobalBounds().intersects(fish_bounds))
        
        {
            score += 1;
            bird.setPosition(60, 60);
            bird.setSpeed(160, 0);
            if (bird_face == 1)
            {
                bird.scale(-1.f, 1.f);
                bird_face = 0;

            }  
            clock.restart();
            while (clock.getElapsedTime().asSeconds() < 3)
            {
                fish_exist = 0;
                std::cout << clock.getElapsedTime().asSeconds() << std::endl;
            }
            fish_exist = 1;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left)
            {
                bird.setSpeed(-160, 0);
                if (bird_face == 0)
                {
                    bird.scale(-1.f, 1.f);
                    bird_face = 1;
                }
               

            }
            if (event.key.code == sf::Keyboard::Right)
            {
                bird.setSpeed(160, 0);
                if (bird_face == 1)
                {
                    bird.scale(-1.f, 1.f);
                    bird_face = 0;
                }
                

            }
            if (event.key.code == sf::Keyboard::Down)
            {
                if (bird_face == 0)
                {
                  
                  bird.setSpeed(160, 200);
                       
                    
                }
                else
                {
               
                    bird.setSpeed(-160, 200);
                  
                }
            }
           
        }
        text.setString(std::to_string(score));
        // DRAW
        window.clear(sf::Color::Black);

        for (const auto& l : landscape) {
            window.draw(l);
        }

        if (fish_exist == 1)
        {
            window.draw(fish);
        }
        window.draw(bird);
        window.draw(text);
        
    }

    return 0;
}