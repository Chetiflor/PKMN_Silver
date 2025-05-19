#pragma once
#include <string>
#include <vector>
#include "enums.hpp"
#include "wrapper.hpp"

struct monolog;

struct choice
{
    choice(std::vector<std::tuple<std::string, monolog *, State>> outcomes_);
    std::tuple<std::string, monolog *, State> get_outcome();
    std::tuple<std::string, monolog *, State> get_outcome(std::pair<int,int> coord);
    std::vector<std::tuple<std::string, monolog *, State>> outcomes;
    std::pair<int,int> selected_outcome;
    std::pair<int,int> dimensions;

    void switch_choice(std::pair<int,int> direction);
};

struct monolog
{
    monolog(std::string str, int stamps_per_line);
    std::vector<std::string> content;
    choice *query;
};

#define dialog monolog

class TextInterface
{
private:
    dialog *current_loaded_dialog;
    int dialog_current_line;
    long int time_of_line_begin;
    bool line_over;
    bool chosing;
    int speed;
    

public:
    TextInterface(/* args */);
    ~TextInterface();

    monolog *build_monolog_from_string(std::string str, int stamps_per_line);
    monolog *craft_test_dialog();
    void load_dialog(dialog *d);
    void forward(State &state);
    void init_dialog();
    wrapped_text get_basic_dialog_content();
    wrapped_text get_basic_dialog_query();
    bool is_chosing();
    void switch_choice(std::pair<int,int> direction);
};
