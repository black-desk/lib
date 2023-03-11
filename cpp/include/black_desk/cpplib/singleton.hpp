#pragma once

#include <memory>
#include <mutex>

#include "black_desk/cpplib/macro.hpp"

namespace black_desk::cpplib
{

class SingletonBase {
    protected:
        SingletonBase() = default;
        SingletonBase(const SingletonBase &) = delete;
        SingletonBase(SingletonBase &&) = delete;
        SingletonBase &operator=(const SingletonBase &) = delete;
        SingletonBase &operator=(SingletonBase &&) = delete;
};

template <typename T>
class Singleton final : private std::shared_ptr<T> {
    public:
        Singleton()
        {
                static std::shared_ptr<T> v(new T);
                this->std::shared_ptr<T>::operator=(v);
                return;
        }
        T *operator->() const
        {
                return this->std::shared_ptr<T>::operator->();
        }
};

}

// SINGLETON(name, (parents), (publics), (privates))
#define SINGLETON(name, ...)                                                    \
        class name##Impl;                                                       \
        typedef const black_desk::cpplib::Singleton<name##Impl> name;           \
        class name##Impl final                                                  \
                : private black_desk::cpplib::SingletonBase                     \
                  BLACKDESK_CPPLIB_ADD_COMMA_FRONT_IF_ARGS(SINGLETON_COMPONENT( \
                          BLACKDESK_CPPLIB_ARGS_ELEM_OR_EMPTY(0,                \
                                                              __VA_ARGS__))) {  \
                friend black_desk::cpplib::Singleton<name##Impl>;               \
                                                                                \
            public:                                                             \
                SINGLETON_COMPONENT(                                            \
                        BLACKDESK_CPPLIB_ARGS_ELEM_OR_EMPTY(1, __VA_ARGS__))    \
                                                                                \
            private:                                                            \
                name##Impl() = default;                                         \
                SINGLETON_COMPONENT(                                            \
                        BLACKDESK_CPPLIB_ARGS_ELEM_OR_EMPTY(2, __VA_ARGS__))    \
        }

#define SINGLETON_COMPONENT(...)                                              \
        BLACKDESK_CPPLIB_ARGS_OPT(BLACKDESK_CPPLIB_ARGS_ELEM(0, __VA_ARGS__), \
                                  (), __VA_ARGS__)
#define SINGLETON_PARENT(...) (__VA_ARGS__)
#define SINGLETON_PUBLIC(...) (__VA_ARGS__)
#define SINGLETON_PRIVATE(...) (__VA_ARGS__)
