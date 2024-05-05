/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** progressBar
*/

#include "Interface.hpp"
#include "my_log.hpp"

void Rt::Interface::initProgressBar()
{
    progress_bg.setPosition((window.getSize().x - bar_size.x) / 2.0, 0);
    progress_bg.setFillColor(sf::Color(0, 0, 0, 50));
    progress_bg.setOutlineColor(sf::Color(255, 255, 255, 50));
    progress_bg.setOutlineThickness(1);
    progress_bg.setSize(bar_size);
    progress_bar.setPosition((window.getSize().x - bar_size.x) / 2.0, 0);
    progress_bar.setFillColor(sf::Color(255, 255, 255, 50));
    if (!font.loadFromFile("./assets/font/DroidSansMono.ttf")) {
        my::log::warning("Failed to load interface font.");
        return;
    }
    progress_text.setFont(font);
    progress_text.setCharacterSize(20);
    progress_text.setFillColor(sf::Color::Red);
    progress_text.setString("           0.00 %");
    sf::FloatRect text_rect = progress_text.getLocalBounds();
    progress_text.setOrigin(text_rect.left + text_rect.width / 2.0, text_rect.top + text_rect.height / 2.0);
    progress_text.setPosition((window.getSize().x - bar_size.x) / 2.0 + bar_size.x / 2.0, bar_size.y / 2.0);
    start_time.restart();
}

std::string Rt::Interface::getRemainTime(double progress)
{
    int second = start_time.getElapsedTime().asSeconds() / progress * (1.0 - progress);
    return std::format("{0:0>2}:{1:0>2}:{2:0>2}",
        (second / 3600), ((second % 3600) / 60), ((second % 3600) % 60));
}

std::string Rt::Interface::getPassedTime()
{
    int second = start_time.getElapsedTime().asSeconds();
    return std::format("{0:0>2}:{1:0>2}:{2:0>2}",
        (second / 3600), ((second % 3600) / 60), ((second % 3600) % 60));
}

void Rt::Interface::drawProgressBar()
{
    double pourcentage = 0;

    if (progress_bar.getSize().x != this->bar_size.x) {
        pourcentage = this->image_pixel_i / static_cast<double>(this->nb_pixel);
        progress_bar.setSize(sf::Vector2f(bar_size.x * pourcentage, bar_size.y));
        progress_text.setString(std::format("      {0:.2f} %\n{1} {2}",
            pourcentage * 100,
            getPassedTime(), getRemainTime(pourcentage)));
    }
    window.draw(progress_bg);
    window.draw(progress_bar);
    window.draw(progress_text);
}
