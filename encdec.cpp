#include "encdec.h"

size_t splitSize = 100000000;//100MB

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
	MEMORYSTATUSEX memoryBuf;
	memoryBuf.dwLength = sizeof(memoryBuf);
	GlobalMemoryStatusEx(&memoryBuf);
	auto memoryFreeSize = memoryBuf.ullAvailPhys;
	if (memoryFreeSize <= splitSize) splitSize = memoryFreeSize * 0.8;

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
	for (auto f : spEncKeyBuf) spEncKey.emplace_back(conv::stoi(f));
	Progress(i, fileSize);
	if (splitSize <= fileSize) b.reserve(splitSize);

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;
		
		a ^= spEncKey[i % encKeyMaxIndex];
		i++;
		b.emplace_back(a);

		if (i % splitSize == 0 && splitSize <= i)
		{
			for (size_t j = 0; j < splitSize; j++)
			{
				out.write((char*)&b[j], 1);
			}

			b.clear();
			Progress(i, fileSize);
		}
	}

	in.close();

	for (size_t j = 0, size = b.size(); j < size; j++)
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
	MEMORYSTATUSEX memoryBuf;
	memoryBuf.dwLength = sizeof(memoryBuf);
	GlobalMemoryStatusEx(&memoryBuf);
	auto memoryFreeSize = memoryBuf.ullAvailPhys;
	if (memoryFreeSize <= splitSize) splitSize = memoryFreeSize * 0.8;

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
	for (auto f : spDecKeyBuf) spDecKey.emplace_back(conv::stoi(f));
	Progress(i, fileSize);
	if (splitSize <= fileSize) b.reserve(splitSize);

	while (!in.eof())
	{
		in.read((char*)&a, 1);
		if (in.eof()) break;

		a ^= spDecKey[i % decKeyMaxIndex];
		i++;
		b.emplace_back(a);

		if (i % splitSize == 0 && splitSize <= i)
		{
			for (size_t j = 0; j < splitSize; j++)
			{
				out.write((char*)&b[j], 1);
			}

			b.clear();
			Progress(i, fileSize);
		}
	}

	in.close();

	for (size_t j = 0; j < b.size(); j++)
	{
		out.write((char*)&b[j], 1);
	}

	Progress(i, fileSize);
	out.close();
	return 0;
}

void encdec::Progress(const size_t& nowSize, const size_t& maxSize)
{
	cout << "\r" << flush;
	if (maxSize < 1000000) cout << nowSize << "B / " << maxSize << "B";
	else if (maxSize < 10000000) cout << nowSize / 1000 << "KB / " << maxSize / 1000 << "KB";
	else if (maxSize < 10000000000) cout << nowSize / 1000000 << "MB / " << maxSize / 1000000 << "MB";
	else cout << nowSize / 1000000000 << "GB / " << maxSize / 1000000000 << "GB";
	return;
}
