#include <chrono>
#include <ctime>
#include <iostream>
#include "timer.hpp"

void keys_timer::reset()
{
    A = 0;
    B = 0;
    right = 0;
    up = 0;
    left = 0;
    down = 0;
    start = 0;
    select = 0;
    R = 0;
    L = 0;
}

void keys_timer::print()
{
    float x = 1000000000.f;
    auto time = std::chrono::system_clock::now().time_since_epoch().count();
#define since(a) (a > 0 ? time - a : 0)
    std::cout << "A:" << since(A) / x << ", B:" << since(B) / x << ", right:" << since(right) / x << ", up:" << since(up) / x << ", left:" << since(left) / x << ", down:" << since(down) / x << ", start:" << since(start) / x << ", select:" << since(select) / x << ", R:" << since(R) / x << ", L:" << since(L) / x << std::endl;
}