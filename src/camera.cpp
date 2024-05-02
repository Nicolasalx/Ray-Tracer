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
}

void Rt::Camera::init()
{
    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    // Determine viewport dimensions.
    double focal_length = (lookfrom - lookat).length();
    double viewport_height = 2.0 * std::tan((fov * std::numbers::pi / 180.0) / 2.0) * focal_length;
    double viewport_width = viewport_height * (double(image_width)/image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = (lookfrom - lookat).unit_vector();
    u = vup.cross(w).unit_vector();
    v = w.cross(u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Math::Vector3D viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    Math::Vector3D viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    Math::Vector3D viewport_upper_left = center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Rt::Ray Rt::Camera::get_ray(int i, int j) const
{
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = (pixel_sample - ray_origin).unit_vector();

    return Rt::Ray(ray_origin, ray_direction);
}

Math::Vector3D Rt::Camera::sample_square() const
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
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
