/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "ColorRGB.hpp"
    #include "IObject.hpp"
    #include "Color01.hpp"
    #include "Random.hpp"
    #include "Matrix3D.hpp"

namespace Rt
{
    class Camera
    {
    public:
        Camera() = default;
        ~Camera() = default;

        int image_width = 1920;
        int image_height = 1080;
        double fov = 90;
        int samples_per_pixel = 10;   // Count of random samples for each pixel
        int max_depth = 10;   // Maximum number of ray bounces into scene
        std::size_t nb_thread = 16;
        Math::Point3D lookfrom = Math::Point3D(0,0,0);
        Math::Point3D lookat = Math::Point3D(0,0,-1);
        Math::Vector3D vup = Math::Vector3D(0,1,0);
        Math::Color01 background;               // Scene background color

//        Math::Point3D position = Math::Point3D(0, 0, 0);   // Camera position
//        Math::Vector3D rotation = Math::Vector3D(0, 0, 0); // Camera rotation

        void render(const Rt::IObject &world);

    private:

        Math::Point3D center;         // Camera center
        Math::Point3D pixel00_loc;    // Location of pixel 0, 0
        Math::Vector3D   pixel_delta_u;  // Offset to pixel to the right
        Math::Vector3D   pixel_delta_v;  // Offset to pixel below
        double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
        Math::Vector3D   u, v, w;              // Camera frame basis vectors

        void init()
        {
            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = lookfrom;

            // Determine viewport dimensions.
            double focal_length = (lookfrom - lookat).length();
            double viewport_height = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focal_length;
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

        Rt::Ray get_ray(int i, int j) const
        {
            // Construct a camera ray originating from the origin and directed at randomly sampled
            // point around the pixel location i, j.

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                              + ((i + offset.x()) * pixel_delta_u)
                              + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return Rt::Ray(ray_origin, ray_direction);
        }

        Math::Vector3D sample_square() const
        {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return Math::Vector3D(Rt::Random::getBw01() - 0.5, Rt::Random::getBw01() - 0.5, 0);
        }

        Math::Color01 ray_color(const Rt::Ray &ray, int depth, const Rt::IObject &world) const
        {
            Rt::HitRecord rec;

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
    };
}

#endif /* !CAMERA_HPP_ */
