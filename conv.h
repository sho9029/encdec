#pragma once
#include "pch.h"

class conv
{
public:
	static void StringToBinary(string&);
	static void BinaryToString(string&);
	static uint8_t stoi(const string&);
	static uint1024_t stoi1024(const string&);
	static tuple<vector<string>, unsigned long long> split(const string&, const unsigned long long&);
private:
	static string DecimalToBinary(const vector<int>&);
};

class StringBitOperator
{
public:
	static string And(string, string);
	static string Or(string, string);
	static string Not(string);
	static string Nand(string, string);
	static string Nor(string, string);
	static string Xor(string, string);
private:
	static void StringsFormat(string&, string&);
};