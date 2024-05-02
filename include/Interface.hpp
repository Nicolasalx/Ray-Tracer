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

namespace Rt
{
    class Interface
    {
    private:
        sf::RenderWindow window;
        sf::Texture image_texture;
        sf::Sprite image_sprite;

    public:
        Interface(std::size_t image_x, std::size_t image_y);
        ~Interface();

        void loop();

        static sf::Uint8 *image_pixel;
        static std::size_t image_pixel_i;
        static std::size_t image_size_x;
        static std::size_t image_size_y;
    };
}

#endif /* !INTERFACE_HPP_ */
