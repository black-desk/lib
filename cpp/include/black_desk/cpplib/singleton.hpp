#pragma once

#include <memory>
#include <mutex>
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
class Singleton : public std::shared_ptr<T> {
    protected:
        static std::shared_ptr<T> v;

    public:
        Singleton()
                : std::shared_ptr<T>(v)
        {
                static std::once_flag flag;
                std::call_once(flag, []() { v.reset(new T); });
                return;
        }
};

}
