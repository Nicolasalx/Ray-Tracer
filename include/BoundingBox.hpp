/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** BoundingBox
*/

#ifndef BOUNDINGBOX_HPP_
    #define BOUNDINGBOX_HPP_

    #include "Interval.hpp"
    #include "Point3D.hpp"
    #include "Ray.hpp"

namespace Rt
{
    class BoundingBox
    {
    private:
        void pad_to_minimums()
        {
            double delta = 0.0001;
            if (x.size() < delta) x = x.expand(delta);
            if (y.size() < delta) y = y.expand(delta);
            if (z.size() < delta) z = z.expand(delta);
        }

    public:
        Rt::Interval x;
        Rt::Interval y;
        Rt::Interval z;

        BoundingBox() = default;
        BoundingBox(const Rt::Interval &x_, const Rt::Interval &y_, const Interval &z_)
            : x(x_), y(y_), z(z_)
        {
            pad_to_minimums();
        }
        BoundingBox(const Math::Point3D &a, const Math::Point3D &b)
        {
            x = (a[0] <= b[0]) ? Rt::Interval(a[0], b[0]) : Rt::Interval(b[0], a[0]);
            y = (a[1] <= b[1]) ? Rt::Interval(a[1], b[1]) : Rt::Interval(b[1], a[1]);
            z = (a[2] <= b[2]) ? Rt::Interval(a[2], b[2]) : Rt::Interval(b[2], a[2]);
            pad_to_minimums();
        }
        BoundingBox(const Rt::BoundingBox &box0, const Rt::BoundingBox &box1)
        {
            x = Rt::Interval(box0.x, box1.x);
            y = Rt::Interval(box0.y, box1.y);
            z = Rt::Interval(box0.z, box1.z);
        }
        ~BoundingBox() = default;

        const Rt::Interval &axis_interval(int n) const
        {
            if (n == 1) return y;
            if (n == 2) return z;
            return x;
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t) const
        {
            const Math::Point3D &ray_orig = ray.getOrigin();
            const Math::Vector3D &ray_dir = ray.getDirection();

            for (int axis = 0; axis < 3; axis++) {
                const Rt::Interval &ax = axis_interval(axis);
                const double adinv = 1.0 / ray_dir[axis];

                auto t0 = (ax.min - ray_orig[axis]) * adinv;
                auto t1 = (ax.max - ray_orig[axis]) * adinv;

                if (t0 < t1) {
                    if (t0 > ray_t.min) {
                        ray_t.min = t0;
                    }
                    if (t1 < ray_t.max) {
                        ray_t.max = t1;
                    }
                } else {
                    if (t1 > ray_t.min) {
                        ray_t.min = t1;
                    }
                    if (t0 < ray_t.max) {
                        ray_t.max = t0;
                    }
                }
                if (ray_t.max <= ray_t.min) {
                    return false;
                }
            }
            return true;
        }

        int longest_axis() const
        {
            // Returns the index of the longest axis of the bounding box.
            if (x.size() > y.size())
                return x.size() > z.size() ? 0 : 2;
            else
                return y.size() > z.size() ? 1 : 2;
        }

        static const Rt::BoundingBox empty;
        static const Rt::BoundingBox universe;
    };
}

#endif /* !BOUNDINGBOX_HPP_ */
