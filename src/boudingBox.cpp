/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** boudingBox
*/

#include "BoundingBox.hpp"


const Rt::BoundingBox Rt::BoundingBox::empty =
    Rt::BoundingBox(
        Rt::Interval::empty,
        Rt::Interval::empty,
        Rt::Interval::empty
    );

const Rt::BoundingBox Rt::BoundingBox::universe =
    Rt::BoundingBox(
        Rt::Interval::universe,
        Rt::Interval::universe,
        Rt::Interval::universe
    );
