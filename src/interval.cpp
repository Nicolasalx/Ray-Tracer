/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** interval
*/

#include "Interval.hpp"

const Rt::Interval Rt::Interval::empty = Rt::Interval(+std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const Rt::Interval Rt::Interval::universe = Rt::Interval(-std::numeric_limits<double>::infinity(), +std::numeric_limits<double>::infinity());
