#pragma once

#include "pch.h"
#include "conv.h"
#include "random.h"

class encdec
{
public:
    static int Encryption(string inFilePath, string outFilePath, string encKey);
    static int Decryption(string inFilePath, string outFilePath, string decKey);
private:
    inline static size_t splitSize = 100000000;
    static void Progress(const size_t& nowSize, const size_t& maxSize);
};