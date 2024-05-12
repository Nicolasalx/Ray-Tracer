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
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
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
    if (quit_after_render) {
        Rt::Raytracer::close_window = true;
    }
}

void Rt::Camera::init()
{
    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    double focal_length = (lookfrom - lookat).length();
    double viewport_height = 2.0 * std::tan((fov * std::numbers::pi / 180.0) / 2.0) * focal_length;
    double viewport_width = viewport_height * (double(image_width)/image_height);

    w = (lookfrom - lookat).unit_vector();
    u = vup.cross(w).unit_vector();
    v = w.cross(u);

    Math::Vector3D viewport_u = viewport_width * u;
    Math::Vector3D viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Math::Vector3D viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Rt::Ray Rt::Camera::get_ray(int i, int j) const
{

    Math::Vector3D offset = sample_square();
    Math::Vector3D pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

    Math::Point3D ray_origin = center;
    Math::Vector3D ray_direction = (pixel_sample - ray_origin).unit_vector();

    return Rt::Ray(ray_origin, ray_direction);
}

Math::Vector3D Rt::Camera::sample_square()
{
    return Math::Vector3D(Rt::Random::getBw01() - 0.5, Rt::Random::getBw01() - 0.5, 0);
}

Math::Color01 Rt::Camera::ray_color(const Rt::Ray &ray, int depth, const Rt::IObject &world) const
{
    Rt::HitData rec;

    if (depth <= 0) {
        return Math::Color01(0, 0, 0);
    }

    if (!world.hit(ray, Rt::Interval(0.001, std::numeric_limits<double>::infinity()), rec)) {
        return background;
    }

    Rt::Ray scattered;
    Math::Color01 attenuation;
    Math::Color01 emmited = rec.material->emitted(rec.u, rec.v, rec.pos);

    if (!rec.material->scatter(ray, rec, attenuation, scattered)) {
        return emmited;
    }

    return emmited + attenuation * ray_color(scattered, depth - 1, world);
}
