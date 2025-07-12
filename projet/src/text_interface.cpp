#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "text_interface.hpp"
#include "game.hpp"

choice::choice(std::vector<std::tuple<std::string, monolog *, std::string>> outcomes_)
{
    outcomes = outcomes_;
    dimensions = {2, 1};
    selected_outcome = {0, 0};
    yes_no = true;
}

std::tuple<std::string, monolog *, std::string> choice::get_outcome()
{
    return outcomes[dimensions.second * selected_outcome.first + selected_outcome.second];
}

std::tuple<std::string, monolog *, std::string> choice::get_outcome(std::pair<int, int> coord)
{
    return outcomes[dimensions.second * coord.first + coord.second];
}

void choice::switch_choice(std::pair<int, int> direction)
{
    selected_outcome.first = (selected_outcome.first + direction.first + dimensions.first) % dimensions.first;
    selected_outcome.second = (selected_outcome.second + direction.second + dimensions.second) % dimensions.second;
}
void TextInterface::select_yes_no(std::string &next_state, bool yes_no)
{
    if (chosing && current_loaded_dialog->query->yes_no)
    {
        current_loaded_dialog->query->selected_outcome.first = !yes_no;
        current_loaded_dialog->query->selected_outcome.second = 0;
    }
}
TextInterface::TextInterface(/* args */)
{
    full_line_time_trigger = 1000000000;
}

TextInterface::~TextInterface()
{
}

monolog *TextInterface::build_monolog_from_string(std::string str, int stamps_per_line)
{
    return new monolog(str, stamps_per_line);
}

monolog::monolog(std::string str, int stamps_per_line)
{

    std::vector<std::string> tokens;
    while (str.length() != 0)
    {
        int pos = str.find(' ');
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos != -1 ? pos + 1 : str.length());
    }
    std::string line = "";
    for (int i = 0; i < tokens.size(); i++)
    {
        if (line.length() + tokens[i].length() > stamps_per_line)
        {

            content.push_back(line.substr(0, line.size() - 1));
            line = "";
        }
        line += tokens[i] + " ";
    }
    if (line != "")
    {
        content.push_back(line.substr(0, line.size() - 1));
    }
}

monolog *TextInterface::craft_test_dialog()
{
    monolog *txt = new monolog("Hello World ? How are you ? Do you want to read over ?", 18);
    monolog *txt2 = new monolog("Alright, let's go, see you later then !", 18);
    std::tuple<std::string, monolog *, std::string> yes = {"YES", txt, "text"};
    std::tuple<std::string, monolog *, std::string> no = {"NO", txt2, "map"};
    txt->query = new choice({yes, no});
    return txt;
};

void TextInterface::load_dialog(dialog *d)
{
    current_loaded_dialog = d;
    init_dialog();
}

void TextInterface::init_dialog()
{

    auto time = std::chrono::system_clock::now();
    last_time = time.time_since_epoch().count();
    dialog_current_line = 0;
    line_over = false;
    chosing = false;
}

bool TextInterface::is_chosing()
{
    return chosing;
}

void TextInterface::step(bool fast)
{
    auto time = std::chrono::system_clock::now();
    int delta_time = (time.time_since_epoch().count() - last_time)* (fast ? 2 : 1);
    time_since_line_begin += delta_time ;
    if (rolling_offset != 0)
    {
        rolling_offset = std::max(rolling_offset - float(9*delta_time) / (full_line_time_trigger), 0.f);
        if (rolling_offset == 0)
        {

            dialog_current_line++;
        }
    }
    last_time = time.time_since_epoch().count();
}

void TextInterface::forward(std::string &next_state)
{
    // std::cout << dialog_current_line << std::endl;
    if (!line_over || rolling_offset > 0)
    {
        return;
    }
    if (dialog_current_line != current_loaded_dialog->content.size() - 1)
    {
        line_over = false;
        rolling_offset = 1;
        auto time = std::chrono::system_clock::now();
        time_since_line_begin = 0;
        last_time = time.time_since_epoch().count();
        return;
    }
    // TODO : maybe delete previous dialog and choice depending on how is stored text data
    if (current_loaded_dialog->query == nullptr)
    {
        next_state = "map";
        return;
    }
    std::tuple<std::string, monolog *, std::string> outcome = current_loaded_dialog->query->get_outcome();
    if (std::get<1>(outcome) == nullptr)
    {
        next_state = std::get<2>(outcome);
        return;
    }
    load_dialog(std::get<1>(outcome));
    return;
};

wrapped_text TextInterface::get_basic_dialog_content()
{

    wrapped_text to_return;
    to_return.stamp_w_ratio = 1.f / 20;
    to_return.stamp_h_ratio = 1.f / 18;
    to_return.x_ratio = 0;
    to_return.y_ratio = 2.f / 3;
    to_return.w_ratio = 1.f;
    to_return.h_ratio = 1.f / 3;
    to_return.borders = true;
    to_return.h_stamp_pad = true;

    int stamps_per_line = to_return.w_ratio / to_return.stamp_w_ratio;
    if (rolling_offset > 0)
    {

        to_return.rolling_offset = rolling_offset;
        to_return.lines.push_back(current_loaded_dialog->content[dialog_current_line]);

        return to_return;
    }

    to_return.rolling_offset = 0;
    if (dialog_current_line != 0)
    {

        to_return.lines.push_back(current_loaded_dialog->content[dialog_current_line - 1]);
    }
    auto time = std::chrono::system_clock::now();
    if (line_over)
    {
        to_return.lines.push_back(current_loaded_dialog->content[dialog_current_line]);
        if (dialog_current_line == 0)
        {
            dialog_current_line++;
            line_over = false;
        }
        time_since_line_begin = 0;

        return to_return;
    }
    int number_of_characters_to_write = stamps_per_line * time_since_line_begin / full_line_time_trigger;
    if (number_of_characters_to_write >= current_loaded_dialog->content[dialog_current_line].length())
    {
        line_over = true;
        to_return.lines.push_back(current_loaded_dialog->content[dialog_current_line]);
        return to_return;
    }

    to_return.lines.push_back(current_loaded_dialog->content[dialog_current_line].substr(0, number_of_characters_to_write));
    return to_return;
};

wrapped_text TextInterface::get_basic_dialog_query()
{
    wrapped_text to_return;

    if (line_over && current_loaded_dialog->content.size() - 1 == dialog_current_line && current_loaded_dialog->query != nullptr)
    {
        chosing = true;
        to_return.stamp_w_ratio = 1.f / 20;
        to_return.stamp_h_ratio = 1.f / 18;
        to_return.x_ratio = 7.f / 10;
        to_return.y_ratio = 7.f / 18;
        to_return.w_ratio = 3.f / 10;
        to_return.h_ratio = 1.f / 4;
        to_return.borders = true;
        to_return.h_stamp_pad = false;
        choice c = *current_loaded_dialog->query;
        for (int i = 0; i < c.dimensions.first; i++)
        {
            for (int j = 0; j < c.dimensions.second; j++)
            {

                to_return.lines.push_back((i == c.selected_outcome.first && j == c.selected_outcome.second ? "#arrow_right#" : " ") + std::get<0>(current_loaded_dialog->query->outcomes[i]));
            }
        }
    }

    return to_return;
};

void TextInterface::switch_choice(std::pair<int, int> direction)
{
    if (chosing)
    {

        current_loaded_dialog->query->switch_choice(direction);
    }
};