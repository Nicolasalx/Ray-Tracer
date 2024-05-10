/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** interface
*/

#include "Interface.hpp"

std::size_t Rt::Interface::image_pixel_i = 0;
sf::Uint8 *Rt::Interface::image_pixel = nullptr;

std::size_t Rt::Interface::image_size_x = 0;
std::size_t Rt::Interface::image_size_y = 0;
std::size_t Rt::Interface::nb_pixel = 1;

Rt::Interface::Interface(std::size_t image_x, std::size_t image_y)
{
    Rt::Interface::image_size_x = image_x;
    Rt::Interface::image_size_y = image_y;
    Rt::Interface::nb_pixel = image_x * image_y;
    double scale = std::min(
        1920.0 / static_cast<double>(image_x),
        1080 / static_cast<double>(image_y));

    window.create(sf::VideoMode(1920, 1080), "RayTracer");
    window.setFramerateLimit(30);

    image_texture.create(image_x, image_y);
    image_pixel = new sf::Uint8[image_x * image_y * 4];

    image_sprite.setTexture(image_texture);
    image_sprite.setScale(sf::Vector2f(scale, scale));
    image_sprite.setOrigin(
        image_sprite.getLocalBounds().width / 2,
        image_sprite.getLocalBounds().height / 2);
    image_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    this->initProgressBar();
}

Rt::Interface::~Interface()
{
    delete image_pixel;
}

void Rt::Interface::loop()
{
    while (window.isOpen() && !Rt::Raytracer::close_window) {
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
        this->drawProgressBar();
        window.display();
    }
}
