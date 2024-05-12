/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** rotation
*/

#include "Rotation.hpp"

Math::Matrix3D Rt::Rotation::rotationMatrix(const Math::Vector3D &angles)
{
    double cos_x = std::cos(angles.x());
    double sin_x = std::sin(angles.x());
    double cos_y = std::cos(angles.y());
    double sin_y = std::sin(angles.y());
    double cos_z = std::cos(angles.z());
    double sin_z = std::sin(angles.z());

    Math::Matrix3D rotation_x = {1, 0, 0, 0, cos_x, -sin_x, 0, sin_x, cos_x};
    Math::Matrix3D rotation_y = {cos_y, 0, sin_y, 0, 1, 0, -sin_y, 0, cos_y};
    Math::Matrix3D rotation_z = {cos_z, -sin_z, 0, sin_z, cos_z, 0, 0, 0, 1};

    return rotation_z * rotation_y * rotation_x;
}

bool Rt::Rotation::hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const
{
    Math::Matrix3D rotation_matrix = rotationMatrix(angle_);
    Rt::Ray rotated_ray = ray.rotate(rotation_matrix);

    if (!object_->hit(rotated_ray, ray_t, rec)) {
        return false;
    }

    rec.pos = rec.pos.rotate(rotation_matrix.transpose());
    rec.normal = rec.normal.rotate(rotation_matrix.transpose()).unit_vector();

    return true;
}