#include "black_desk/cpplib/singleton.hpp"

class testSingleton;

typedef const black_desk::cpplib::Singleton<testSingleton> TestSingleton;

class testSingleton final : private black_desk::cpplib::SingletonBase {
    private:
        testSingleton();
        friend black_desk::cpplib::Singleton<testSingleton>;
};
