#pragma once

#include "black_desk/cpplib/singleton.hpp"

SINGLETON(TestSingleton, (), SINGLETON_PUBLIC(int a, b; int add();));
