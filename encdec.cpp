#include "encdec.h"

constexpr auto EXCEPTION_ENCRYPTION = "ファイルが出力できません。";;

int encdec::Encryption::Text(string inFilePath, string outFilePath, string encKey)
{
	ifstream in(inFilePath);
	if (!in) throw new exception("ファイルを開けませんでした");
	stringstream ss;
	ss << in.rdbuf();
	in.close();
	string str(ss.str());
	conv::StringToBinary(str);
	conv::StringToBinary(encKey);

	if (str.size() != encKey.size())
	{
		size_t k = encKey.size();

		while (k < str.size())
		{
			encKey += encKey;
			k = encKey.size();
		}
		while (str.size() < k)
		{
			encKey.erase(encKey.end() - 1);
			k = encKey.size();
		}
	}
	
	str = StringBitOperator::Xor(str, encKey);

	ofstream out(outFilePath, ios::trunc);
	if (!out) throw new exception("ファイルを出力できませんでした");
	out << str;
	out.close();

	return 0;
}

int encdec::Encryption::Binary(string inFilePath, string outFilePath, string encKey)
{
	conv::StringToBinary(encKey);
	ifstream in(inFilePath, ios::binary);
	if (!in) throw new exception("ファイルを開けませんでした");
	uint8_t a;
	vector<uint8_t> b;
	auto [spEncKey, encKeyMaxIndex] = conv::split(encKey, 2);
	size_t i = 0;

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;
		
		a ^= conv::stoi(spEncKey[i % encKeyMaxIndex]);
		i++;
		b.push_back(a);
	}

	in.close();
	ofstream out(outFilePath, ios::trunc | ios::binary);
	if (!out) throw new exception("ファイルを出力できませんでした");

	for (auto f : b)
	{
		out.write((char*)&f, 1);
	}

	out.close();
	return 0;
}

int encdec::Decryption::Text(string inFilePath, string outFilePath, string decKey)
{
	ifstream in(inFilePath);
	if (!in) throw new exception("ファイルを開けませんでした");
	stringstream ss;
	ss << in.rdbuf();
	in.close();
	string str(ss.str());
	conv::StringToBinary(decKey);

	if (str.size() != decKey.size())
	{
		size_t k = decKey.size();

		while (k < str.size())
		{
			decKey += decKey;
			k = decKey.size();
		}
		while (str.size() < k)
		{
			decKey.erase(decKey.end() - 1);
			k = decKey.size();
		}
	}

	str = StringBitOperator::Xor(str, decKey);

	conv::BinaryToString(str);

	ofstream out(outFilePath, ios::trunc);
	if (!out) throw new exception("ファイルを出力できませんでした");
	out << str;
	out.close();
	return 0;
}

int encdec::Decryption::Binary(string inFilePath, string outFilePath, string decKey)
{
	conv::StringToBinary(decKey);
	ifstream in(inFilePath, ios::binary);
	if (!in) throw new exception("ファイルを開けませんでした");
	uint8_t a;
	vector<uint8_t> b;
	auto [spdecKey, decKeyMaxIndex] = conv::split(decKey, 2);
	size_t i = 0;

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;

		a ^= conv::stoi(spdecKey[i % decKeyMaxIndex]);
		i++;
		b.push_back(a);
	}

	in.close();
	ofstream out(outFilePath, ios::trunc | ios::binary);
	if (!out) throw new exception("ファイルを出力できませんでした");

	for (auto f : b)
	{
		out.write((char*)&f, 1);
	}

	out.close();
	return 0;
}