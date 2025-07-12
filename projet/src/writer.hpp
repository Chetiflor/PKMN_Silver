#pragma once
#include <SDL2/SDL_image.h>
#include<vector>
#include<map>
#include<string>
#include"wrapper.hpp"

struct graphic_character
{
    std::vector<std::vector<std::tuple<char,char,char,char>>> values;
    std::pair<int,int> dimensions;
};


class Writer
{
private:
    std::map<std::string,graphic_character> characters;
    std::map<std::string,graphic_character> style;

    
    void stamp_character(SDL_Renderer *renderer, graphic_character c, float x_ratio, float y_ratio, float w_ratio, float h_ratio);

public:
    static int * w;
    static int * h;    

    Writer(/* args */);
    ~Writer();
    void load_font(std::string filename, bool in_style);
    // void load_style(std::string filename);
    graphic_character create_gr_char(std::string txt,std::pair<int,int> dimensions);

    void write_string(SDL_Renderer *renderer, std::string str,float x_ratio, float y_ratio, float stamp_w_ratio, float stamp_h_ratio, int stamps_per_line);
    void write_style(SDL_Renderer *renderer,float x_ratio, float y_ratio, float stamp_w_ratio, float stamp_h_ratio, int stamps_per_line, int stamps_per_column);

    void write_wrapped_text(SDL_Renderer *renderer,wrapped_text content);
};
