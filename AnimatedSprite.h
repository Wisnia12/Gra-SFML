#pragma once
#include <SFML/Graphics.hpp>

#include <string>


class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite() : sf::Sprite()
    {
    }
    void add_animation_frame(const sf::IntRect& frame);
    void step(const sf::Time& elapsed);
    void setSpeed(int speed_x, int speed_y);
    void animate(const sf::Time& elapsed);


private:
    std::vector<sf::IntRect> frames_;
    std::vector<sf::IntRect>::iterator current_frame_ = frames_.begin();
    //    size_t current_frame_ = 0;
    float elapsed_accumulator_ = 0;
    float fps = 10;
    int speed_x_ = 0;
    int speed_y_ = 0;
};

sf::Texture loadTexture(const std::string& filename_with_path);
