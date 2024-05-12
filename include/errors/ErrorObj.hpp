/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** ErrorObj
*/

#ifndef ERROROBJ_HPP_
#define ERROROBJ_HPP_

#include <iostream>

namespace Rt {
    class ErrorObj : public std::exception {
        public:
            ErrorObj(std::ostream &os, const std::string &message) noexcept;
        protected:
        private:
    };
};

#endif /* !ERROROBJ_HPP_ */
