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
        int samples_per_pixel = 100;   // Count of random samples for each pixel
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

        void init();
        Rt::Ray get_ray(int i, int j) const;
        Math::Vector3D sample_square() const;
        Math::Color01 ray_color(const Rt::Ray &ray, int depth, const Rt::IObject &world) const;
    };
}

#endif /* !CAMERA_HPP_ */
