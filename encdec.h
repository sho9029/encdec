#pragma once

#include "pch.h"
#include "conv.h"
#include "random.h"

class encdec
{
public:
    static int Convert(string inFilePath, string outFilePath, string key);
private:
    inline static size_t splitSize = 100000000;
    static void Progress(const size_t& nowSize, const size_t& maxSize);
};