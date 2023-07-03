#include "AnimatedSprite.h"

#include <iostream>


void AnimatedSprite::add_animation_frame(const sf::IntRect& frame) {
    frames_.emplace_back(frame);
    current_frame_ = frames_.begin();
}

void AnimatedSprite::step(const sf::Time& elapsed) {
    elapsed_accumulator_ += elapsed.asSeconds();
    while (elapsed_accumulator_ >= 1.0 / fps) {
        elapsed_accumulator_ -= 1.0 / fps;
        if (!frames_.empty()) {
            //                setTextureRect(frames_[current_frame_]);
            //                current_frame_ = (current_frame_ + 1) % frames_.size();
            setTextureRect(*current_frame_);
            current_frame_++;
            if (current_frame_ == frames_.end())
            {
                current_frame_ = frames_.begin();
            }
        }
    }
}

void AnimatedSprite::setSpeed(
    int speed_x, int speed_y
)

{
    speed_x_ = speed_x;
    speed_y_ = speed_y;
}

void AnimatedSprite::animate(const sf::Time& elapsed) {
    move(speed_x_ * elapsed.asSeconds(), speed_y_ * elapsed.asSeconds());
}


sf::Texture loadTexture(const std::string& filename_with_path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename_with_path)) {
        std::cerr << "Could not load texture" << std::endl;
    }
    return texture;
}
