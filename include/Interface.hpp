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
        Interface(int image_x, int image_y)
        {
            window.create(sf::VideoMode(1920, 1080), "RayTracer");
            window.setFramerateLimit(30);
            double scale = 1920 / double(image_x);
            if (1920 / image_x > 1080 / double(image_y)) {
                scale = 1080 / double(image_y);
            }
            image_texture.create(image_x, image_y);
            image_pixel = new sf::Uint8[image_x * image_y * 4];

            image_sprite.setTexture(image_texture);
            image_sprite.setScale(sf::Vector2f(scale, scale));

            image_size_x = image_x;
            image_size_y = image_y;
        }
        ~Interface()
        {
            delete image_pixel;
        }

        void loop()
        {
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                window.clear();

                Rt::Raytracer::mutex.lock();
                image_texture.update(Rt::Interface::image_pixel);
                Rt::Raytracer::mutex.unlock();

                window.draw(image_sprite);

                window.display();
            }

        }

        static sf::Uint8 *image_pixel;
        static std::size_t image_pixel_i;
        static std::size_t image_size_x;
        static std::size_t image_size_y;
    };
}

#endif /* !INTERFACE_HPP_ */
