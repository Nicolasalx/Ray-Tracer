/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** BoundingNode
*/

#ifndef BoundingNode_HPP_
    #define BoundingNode_HPP_

    #include "IObject.hpp"
    #include "ObjectList.hpp"
    #include "BoundingBox.hpp"
    #include <algorithm>

namespace Rt
{
    class BoundingNode : public IObject
    {
    private:
        std::shared_ptr<Rt::IObject> left;
        std::shared_ptr<Rt::IObject> right;
        Rt::BoundingBox bounding_box_;

        static bool box_compare(
        const std::shared_ptr<Rt::IObject> a, const std::shared_ptr<Rt::IObject> b, int axis_index)
        {
            auto a_axis_interval = a->getBoundingBox().axis_interval(axis_index);
            auto b_axis_interval = b->getBoundingBox().axis_interval(axis_index);
            return a_axis_interval.min < b_axis_interval.min;
        }

        static bool box_x_compare (const std::shared_ptr<Rt::IObject> a, const std::shared_ptr<Rt::IObject> b) {
            return box_compare(a, b, 0);
        }

        static bool box_y_compare (const std::shared_ptr<Rt::IObject> a, const std::shared_ptr<Rt::IObject> b) {
            return box_compare(a, b, 1);
        }

        static bool box_z_compare (const std::shared_ptr<Rt::IObject> a, const std::shared_ptr<Rt::IObject> b) {
            return box_compare(a, b, 2);
        }

    public:
        BoundingNode(Rt::ObjectList list) : BoundingNode(list.objects, 0, list.objects.size())
        {
            // There's a C++ subtlety here. This constructor (without span indices) creates an
            // implicit copy of the hittable list, which we will modify. The lifetime of the copied
            // list only extends until this constructor exits. That's OK, because we only need to
            // persist the resulting bounding volume hierarchy.
        }

        BoundingNode(std::vector<std::shared_ptr<Rt::IObject>> &objects, size_t start, size_t end)
        {
         // Build the bounding box of the span of source objects.
            this->bounding_box_ = Rt::BoundingBox::empty;
            for (size_t object_index = start; object_index < end; ++object_index) {
                bounding_box_ = Rt::BoundingBox(bounding_box_, objects[object_index]->getBoundingBox());
            }

            int axis = bounding_box_.longest_axis();

            auto comparator = (axis == 0) ? box_x_compare
                            : (axis == 1) ? box_y_compare
                                          : box_z_compare;

            size_t object_span = end - start;

            if (object_span == 1) {
                left = right = objects[start];
            } else if (object_span == 2) {
                left = objects[start];
                right = objects[start+1];
            } else {
                std::sort(objects.begin() + start, objects.begin() + end, comparator);

                auto mid = start + object_span/2;
                left = std::make_shared<Rt::BoundingNode>(objects, start, mid);
                right = std::make_shared<Rt::BoundingNode>(objects, mid, end);
            }
//
//            this->bounding_box_ = Rt::BoundingBox(left->bounding_box(), right->bounding_box());
        }

        bool hit(const Rt::Ray &ray, Rt::Interval ray_t, Rt::HitRecord &rec) const override {
            if (!bounding_box_.hit(ray, ray_t))
                return false;

            bool hit_left = left->hit(ray, ray_t, rec);
            bool hit_right = right->hit(ray, Rt::Interval(ray_t.min, hit_left ? rec.t : ray_t.max), rec);

            return hit_left || hit_right;
        }

        Rt::BoundingBox getBoundingBox() const override
        {
            return bounding_box_;
        }
    };
}

#endif /* !BoundingNode_HPP_ */
