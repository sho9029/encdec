#pragma once

#include "pch.h"
#include "conv.h"

class encdec
{
public:
	class Encryption
	{
	public:
		static int Text(string inFilePath, string outFilePath, string encKey);
		static int Binary(string inFilePath, string outFilePath, string encKey);
	};
	class Decryption
	{
	public:
		static int Text(string inFilePath, string outFilePath, string decKey);
		static int Binary(string inFilePath, string outFilePath, string decKey);
	};
private:
	static void Progress(const size_t& nowSize, const size_t& maxSize);
};