#include "encdec.h"

const size_t splitSize = 100000000;//100MB

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
	size_t fileSize = in.seekg(0, ios::end).tellg();
	in.clear();
	in.seekg(0, ios::beg);
	ofstream out(outFilePath, ios::trunc | ios::binary);
	if (!out) throw new exception("ファイルを出力できませんでした");
	auto [spEncKeyBuf, encKeyMaxIndex] = conv::split(encKey, 2);
	uint8_t a;
	vector<uint8_t> b, spEncKey;
	size_t i = 0;
	for (auto f : spEncKeyBuf) spEncKey.push_back(conv::stoi(f));
	Progress(i, fileSize);

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;
		
		a ^= spEncKey[i % encKeyMaxIndex];
		i++;
		b.push_back(a);

		if (i % splitSize == 0 && splitSize <= i)
		{
			for (unsigned long long j = 0; j < splitSize; j++)
			{
				out.write((char*)&b[j], 1);
			}

			b.clear();
			b.shrink_to_fit();
			Progress(i, fileSize);
		}
	}

	in.close();

	for (unsigned long long j = 0; j < b.size(); j++)
	{
		out.write((char*)&b[j], 1);
	}

	Progress(i, fileSize);
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
	size_t fileSize = in.seekg(0, ios::end).tellg();
	in.clear();
	in.seekg(0, ios::beg);
	ofstream out(outFilePath, ios::trunc | ios::binary);
	if (!out) throw new exception("ファイルを出力できませんでした");
	auto [spDecKeyBuf, decKeyMaxIndex] = conv::split(decKey, 2);
	uint8_t a;
	vector<uint8_t> b, spDecKey;
	size_t i = 0;
	for (auto f : spDecKeyBuf) spDecKey.push_back(conv::stoi(f));
	Progress(i, fileSize);

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;

		a ^= spDecKey[i % decKeyMaxIndex];
		i++;
		b.push_back(a);

		if (i % splitSize == 0 && splitSize <= i)
		{
			for (unsigned long long j = 0; j < splitSize; j++)
			{
				out.write((char*)&b[j], 1);
			}

			b.clear();
			b.shrink_to_fit();
			Progress(i, fileSize);
		}
	}

	in.close();

	for (unsigned long long j = 0; j < b.size(); j++)
	{
		out.write((char*)&b[j], 1);
	}

	Progress(i, fileSize);
	out.close();
	return 0;
}

void encdec::Progress(size_t nowSize, size_t maxSize)
{
	cout << "\r" << flush;
	if (maxSize < 1000000) cout << nowSize << "B / " << maxSize << "B";
	else if (maxSize < 1000000000) cout << nowSize / 1000 << "KB / " << maxSize / 1000 << "KB";
	else if (maxSize < 1000000000000) cout << nowSize / 1000000 << "MB / " << maxSize / 1000000 << "MB";
	else cout << nowSize / 1000000000 << "GB / " << maxSize / 1000000000 << "GB";
	return;
}
