#pragma once
#include<vector>
#include<string>

struct wrapped_text
{
    std::vector<std::string> lines;
    float stamp_w_ratio;
    float stamp_h_ratio;
    float x_ratio;
    float y_ratio;
    float w_ratio;
    float h_ratio;
    bool borders;
    bool h_stamp_pad;
};
