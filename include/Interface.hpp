/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Interface
*/

#ifndef INTERFACE_HPP_
    #define INTERFACE_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include "Raytracer.hpp"
    #include <format>

namespace Rt
{
    class Interface
    {
    private:
        sf::RenderWindow window;
        sf::Texture image_texture;
        sf::Sprite image_sprite;

        sf::RectangleShape progress_bar;
        sf::RectangleShape progress_bg;
        sf::Font font;
        sf::Text progress_text;
        sf::Vector2f bar_size = sf::Vector2f(500, 25);

        sf::Clock start_time;

        std::string getRemainTime(double progress);
        std::string getPassedTime();
        void initProgressBar();
        void drawProgressBar();

    public:
        Interface(std::size_t image_x, std::size_t image_y);
        ~Interface();

        void loop();

        static sf::Uint8 *image_pixel;
        static std::size_t image_pixel_i;
        static std::size_t image_size_x;
        static std::size_t image_size_y;
        static std::size_t nb_pixel;
    };
}

#endif /* !INTERFACE_HPP_ */
