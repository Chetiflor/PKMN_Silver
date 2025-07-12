#pragma once
#include <string>
#include <vector>
#include "enums.hpp"
#include "wrapper.hpp"

struct monolog;

struct choice
{
    choice(std::vector<std::tuple<std::string, monolog *, std::string>> outcomes_);
    std::tuple<std::string, monolog *, std::string> get_outcome();
    std::tuple<std::string, monolog *, std::string> get_outcome(std::pair<int,int> coord);
    std::vector<std::tuple<std::string, monolog *, std::string>> outcomes;
    std::pair<int,int> selected_outcome;
    std::pair<int,int> dimensions;

    void switch_choice(std::pair<int,int> direction);

    bool yes_no;
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
    long int full_line_time_trigger;
    long int time_since_line_begin;
    long int last_time;
    
    bool line_over;
    float rolling_offset;
    bool chosing;
    int speed;

    

public:
    TextInterface(/* args */);
    ~TextInterface();

    monolog *build_monolog_from_string(std::string str, int stamps_per_line);
    monolog *craft_test_dialog();
    void load_dialog(dialog *d);
    void step(bool face);
    void forward(std::string &next_state);
    void init_dialog();
    wrapped_text get_basic_dialog_content();
    wrapped_text get_basic_dialog_query();
    bool is_chosing();
    void select_yes_no(std::string& next_state,bool yes_no);
    void switch_choice(std::pair<int,int> direction);
};
