/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
    #define ROTATION_HPP_

    #include "IObject.hpp"
    #include "Matrix3D.hpp"

namespace Rt
{
    class Rotation : public IObject
    {
    private:
        std::shared_ptr<Rt::IObject> object_;
        Math::Vector3D angle_;

        // Helper functions for rotation transformation
        Math::Matrix3D rotationMatrix(const Math::Vector3D &angles) const
        {
            double cos_x = std::cos(angles.x());
            double sin_x = std::sin(angles.x());
            double cos_y = std::cos(angles.y());
            double sin_y = std::sin(angles.y());
            double cos_z = std::cos(angles.z());
            double sin_z = std::sin(angles.z());

            // Calculate rotation matrix for each axis
            Math::Matrix3D rotation_x = {1, 0, 0, 0, cos_x, -sin_x, 0, sin_x, cos_x};
            Math::Matrix3D rotation_y = {cos_y, 0, sin_y, 0, 1, 0, -sin_y, 0, cos_y};
            Math::Matrix3D rotation_z = {cos_z, -sin_z, 0, sin_z, cos_z, 0, 0, 0, 1};

            // Combine rotation matrices for each axis to get the final rotation matrix
            return rotation_z * rotation_y * rotation_x;
        }

    public:
        Rotation(std::shared_ptr<Rt::IObject> object, Math::Vector3D angle)
            : object_(object), angle_(Math::Vector3D(
                angle.x() * (std::numbers::pi / 180.0),
                angle.y() * (std::numbers::pi / 180.0),
                angle.z() * (std::numbers::pi / 180.0)))
        {
        }


        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitData &rec) const override
        {
            Math::Matrix3D rotation_matrix = rotationMatrix(angle_);
            Rt::Ray rotated_ray = ray.rotate(rotation_matrix);

            if (!object_->hit(rotated_ray, ray_t, rec))
                return false;

            rec.pos = rec.pos.rotate(rotation_matrix.transpose());
            rec.normal = rec.normal.rotate(rotation_matrix.transpose()).unit_vector();

            return true;
        }
    };
}

#endif /* !ROTATION_HPP_ */
