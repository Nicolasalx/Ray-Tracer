/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ErrorCamera
*/

#ifndef ERRORCAMERA_HPP_
#define ERRORCAMERA_HPP_

#include <iostream>

namespace Rt {
    class ErrorCamera : public std::exception {
        public:
            ErrorCamera(std::ostream &os, const std::string &message) noexcept;
        protected:
        private:

    };
}

#endif /* !ERRORCAMERA_HPP_ */
