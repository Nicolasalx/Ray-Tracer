/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** camera
*/

#include "Camera.hpp"
#include <thread>

void Rt::Camera::render(const Rt::IObject &world)
{
    this->init();

    std::vector<std::thread> render_thread;

    auto render_line = [&](int start_line, int end_line) {
        for (int j = start_line; j < end_line; j++) {
            for (int i = 0; i < image_width; i++) {
                Math::Color01 pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Rt::Ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                Rt::ColorRGB(pixel_samples_scale * pixel_color).displayColor(i, j);
                if (Rt::Raytracer::end_rendering) {
                    return;
                }
            }
        }
    };

    for (size_t i = 0; i < nb_thread; ++i) {
        render_thread.emplace_back(render_line, image_height / nb_thread * i,
            (i == nb_thread - 1) ? image_height : image_height / nb_thread * (i + 1));
    }
    for (size_t i = 0; i < nb_thread; ++i) {
        render_thread[i].join();
    }
    sf::Image result_image;
    result_image.create(image_width, image_height, Rt::Interface::image_pixel);
    result_image.saveToFile("result_image.png");
}
