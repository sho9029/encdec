#pragma once
#include "pch.h"
#include "conv.h"

class random
{
public:
    static string rand(const string&);
    static uint64_t stoiorder(const string&);
private:
    static string randjoin(const string&);
};

