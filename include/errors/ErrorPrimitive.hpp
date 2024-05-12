/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ErrorPrimitive
*/

#ifndef ERRORPRIMITIVE_HPP_
#define ERRORPRIMITIVE_HPP_

#include <iostream>

namespace Rt {
    class ErrorPrimitive : public std::exception {
        public:
            ErrorPrimitive(std::ostream &os, const std::string &message) noexcept;
        protected:
        private:
    };
}

#endif /* !ERRORPRIMITIVE_HPP_ */
