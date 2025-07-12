#pragma once

struct keys_timer
{
    long int A = 0;
    long int B = 0;
    long int right = 0;
    long int up = 0;
    long int left = 0;
    long int down = 0;
    long int start = 0;
    long int select = 0;
    long int R = 0;
    long int L = 0;

    void reset();
    void print();
};