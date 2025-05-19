#pragma once
#include <SDL2/SDL_image.h>
#include<vector>
#include<map>
#include<string>

struct skin_FF
{
    std::vector<std::vector<std::tuple<char,char,char>>> colors;
};

struct oriented_skin
{
    skin_FF right;
    skin_FF up;
    skin_FF left;
    skin_FF down;
};
struct moving_skin
{
    std::vector<oriented_skin> frames;
};



class Drawer
{
private:
    /* data */
public:
    Drawer(/* args */);
    ~Drawer();
};
