/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-raytracer-thibaud.cathala
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

    #include <string>
    #include <dlfcn.h>
    #include "my_tracked_exception.hpp"

namespace Rt
{
    template<typename T>
    class DLLoader
    {
    public:
        DLLoader() = default;
        DLLoader(const std::string &libName)
        {
            this->_handle = dlopen(libName.c_str(), RTLD_LAZY);
            if (!this->_handle) {
                throw my::tracked_exception(dlerror());
            }
        }

        ~DLLoader()
        {
            if (this->_handle == nullptr) {
                return;
            }
            dlclose(this->_handle);
        }

        void load(const std::string &libName)
        {
            if (this->_handle) {
                this->close();
            }
            this->_handle = dlopen(libName.c_str(), RTLD_LAZY);
            if (!this->_handle) {
                throw my::tracked_exception(dlerror());
            }
        }

        void close()
        {
            if (this->_handle == nullptr) {
                return;
            }
            dlclose(this->_handle);
            this->_handle = nullptr;
        }

        T *getInstance(const std::string &name)
        {
            auto func = reinterpret_cast<T *(*)(void)>(dlsym(this->_handle, name.c_str()));
            if (!func) {
                throw my::tracked_exception(dlerror());
            }
            return func();
        }

        template<typename T2>
        T2 getSymbol(const std::string &name)
        {
            auto func = reinterpret_cast<T2 (*)(void)>(dlsym(this->_handle, name.c_str()));
            if (!func) {
                throw my::tracked_exception(dlerror());
            }
            return func();
        }

    private:
        void *_handle = nullptr;
    };
}

#endif /* !DLLOADER_HPP_ */
