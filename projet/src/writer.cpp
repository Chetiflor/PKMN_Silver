#include "writer.hpp"
#include <fstream>
#include <iostream>

Writer::Writer(/* args */)
{
}

Writer::~Writer()
{
}

graphic_character_88 Writer::create_gr_char(std::string txt)
{
    graphic_character_88 engram;
    for (int i = 0; i < 8; i++)
    {
        std::vector<bool> line;
        for (int j = 0; j < 8; j++)
        {
            line.push_back(txt[1 + 8 * i + j] == '1');
        }
        engram.binary_values.push_back(line);
    }
    return engram;
}

void Writer::load_font(std::string filename)
{
    std::ifstream font_file(filename);
    std::string line;
    int C = 0;
    std::string gr_char = "";
    while (getline(font_file, line))
    {
        gr_char += line;
        if (C == 8)
        {
            characters.insert({gr_char[0], create_gr_char(gr_char)});
            gr_char = "";
        }
        C = (C + 1) % 9;
    }
    font_file.close();
}
void Writer::load_style(std::string filename)
{
    std::ifstream style_file(filename);
    std::string line;
    int C = 0;
    std::string gr_char = "0";
    std::string stamp_name;
    while (getline(style_file, line))
    {
        if (C == 0)
        {
            stamp_name = line;
        }
        else
        {
            gr_char += line;
        }
        if (C == 8)
        {
            style.insert({stamp_name, create_gr_char(gr_char)});
            gr_char = "0";
            stamp_name = "";
        }
        C = (C + 1) % 9;
    }
    style_file.close();
}

void Writer::stamp_character(SDL_Renderer *renderer, graphic_character_88 c, float x_ratio, float y_ratio, float w_ratio, float h_ratio)
{
    float w_step = w_ratio * (*w) / 8;
    float h_step = h_ratio * (*h) / 8;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (c.binary_values[j][i])
            {
                SDL_Rect rect;
                rect.x = int(round((x_ratio * (*w) + i * w_step)));
                rect.y = int(round(y_ratio * (*h) + j * h_step));
                rect.w = int(round(x_ratio * (*w) + (i + 1) * w_step)) - int(round(x_ratio * (*w) + i * w_step));
                rect.h = int(round(y_ratio * (*h) + (j + 1) * h_step)) - int(round(y_ratio * (*h) + j * h_step));
                // std::cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << std::endl;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Writer::write_string(SDL_Renderer *renderer, std::string str, float x_ratio, float y_ratio, float stamp_w_ratio, float stamp_h_ratio, int stamps_per_line)
{
    int i = 0;
    while (str.length() > 0)
    {
        if (str[0] != '#')
        {
            stamp_character(renderer,
                            characters.find(str[0]) != characters.end() ? characters[str[0]] : characters[' '],
                            x_ratio + (i + 1) * stamp_w_ratio,
                            y_ratio,
                            stamp_w_ratio,
                            stamp_h_ratio);
            str.erase(0, 1);
        }
        else
        {
            str.erase(0, 1);
            int next_hashtag = str.find('#',0);
            std::string style_piece = str.substr(0,next_hashtag);
            str.erase(0, next_hashtag+1);
            stamp_character(renderer,
                            style.find(style_piece) != style.end() ? style[style_piece] : characters['!'],
                            x_ratio + (i + 1) * stamp_w_ratio,
                            y_ratio,
                            stamp_w_ratio,
                            stamp_h_ratio);
        }
        i++;
    }
}

void Writer::write_style(SDL_Renderer *renderer, float x_ratio, float y_ratio, float stamp_w_ratio, float stamp_h_ratio, int stamps_per_line, int stamps_per_column)
{

    // draw blank rectangle around text
    SDL_Rect rect;
    rect.x = int(round(x_ratio * (*w)));
    rect.y = int(round(y_ratio * (*h)));
    rect.w = int(round(stamps_per_line * stamp_w_ratio * (*w)));
    rect.h = int(round(stamps_per_column * stamp_h_ratio * (*h)));
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    // draw each corner
    std::vector<std::string> corner_names = {"corner_up_right", "corner_up_left", "corner_down_left", "corner_down_right"};
    std::vector<std::pair<float, float>> corner_coord = {{x_ratio + (stamps_per_line - 1) * stamp_w_ratio, y_ratio},
                                                         {x_ratio, y_ratio},
                                                         {x_ratio, y_ratio + (stamps_per_column - 1) * stamp_h_ratio},
                                                         {x_ratio + (stamps_per_line - 1) * stamp_w_ratio, y_ratio + (stamps_per_column - 1) * stamp_h_ratio}};
    for (int corner = 0; corner < 4; corner++)
    {
        stamp_character(renderer,
                        style.find(corner_names[corner]) != style.end() ? style[corner_names[corner]] : characters['!'],
                        corner_coord[corner].first,
                        corner_coord[corner].second,
                        stamp_w_ratio,
                        stamp_h_ratio);
    }

    // draw horizontal lines
    for (int i = 0; i < stamps_per_line - 2; i++)
    {
        stamp_character(renderer,
                        style.find("edge_up") != style.end() ? style["edge_up"] : characters['!'],
                        x_ratio + (i + 1) * stamp_w_ratio,
                        y_ratio,
                        stamp_w_ratio,
                        stamp_h_ratio);
        stamp_character(renderer,
                        style.find("edge_down") != style.end() ? style["edge_down"] : characters['!'],
                        x_ratio + (i + 1) * stamp_w_ratio,
                        y_ratio + (stamps_per_column - 1) * stamp_h_ratio,
                        stamp_w_ratio,
                        stamp_h_ratio);
    }

    // draw vertical lines
    for (int i = 0; i < stamps_per_column - 2; i++)
    {
        stamp_character(renderer,
                        style.find("edge_left") != style.end() ? style["edge_left"] : characters['!'],
                        x_ratio,
                        y_ratio + (i + 1) * stamp_h_ratio,
                        stamp_w_ratio,
                        stamp_h_ratio);
        stamp_character(renderer,
                        style.find("edge_right") != style.end() ? style["edge_right"] : characters['!'],
                        x_ratio + (stamps_per_line - 1) * stamp_w_ratio,
                        y_ratio + (i + 1) * stamp_h_ratio,
                        stamp_w_ratio,
                        stamp_h_ratio);
    }
}

void Writer::write_wrapped_text(SDL_Renderer *renderer, wrapped_text content)
{
    if (content.lines.size() == 0)
    {
        return;
    }

    int stamps_per_line = int(round(content.w_ratio / content.stamp_w_ratio));
    int stamps_per_column = int(round(content.h_ratio / content.stamp_h_ratio));
    write_style(renderer, content.x_ratio, content.y_ratio, content.stamp_w_ratio, content.stamp_h_ratio, stamps_per_line, stamps_per_column);
    for (int i = 0; i < content.lines.size(); i++)
    {
        write_string(renderer, content.lines[i], content.x_ratio, content.y_ratio + (2 * i + 1 + (content.h_stamp_pad ? 1 : 0)) * content.stamp_h_ratio, content.stamp_w_ratio, content.stamp_h_ratio, stamps_per_line);
    }
}