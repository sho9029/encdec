#include "conv.h"

void conv::StringToBinary(string& a)
{
	vector<int> z;

	for (auto f : a)
	{
		if (f == '0') z.push_back(1);
		else if (f == '1') z.push_back(3);
		else if (f == '2') z.push_back(5);
		else if (f == '3') z.push_back(7);
		else if (f == '4') z.push_back(9);
		else if (f == '5') z.push_back(11);
		else if (f == '6') z.push_back(13);
		else if (f == '7') z.push_back(15);
		else if (f == '8') z.push_back(17);
		else if (f == '9') z.push_back(19);
		else if (f == 'A') z.push_back(21);
		else if (f == 'B') z.push_back(23);
		else if (f == 'C') z.push_back(25);
		else if (f == 'D') z.push_back(27);
		else if (f == 'E') z.push_back(29);
		else if (f == 'F') z.push_back(31);
		else if (f == 'G') z.push_back(33);
		else if (f == 'H') z.push_back(35);
		else if (f == 'I') z.push_back(37);
		else if (f == 'J') z.push_back(39);
		else if (f == 'K') z.push_back(41);
		else if (f == 'L') z.push_back(43);
		else if (f == 'M') z.push_back(45);
		else if (f == 'N') z.push_back(47);
		else if (f == 'O') z.push_back(49);
		else if (f == 'P') z.push_back(51);
		else if (f == 'Q') z.push_back(53);
		else if (f == 'R') z.push_back(55);
		else if (f == 'S') z.push_back(57);
		else if (f == 'T') z.push_back(59);
		else if (f == 'U') z.push_back(61);
		else if (f == 'V') z.push_back(63);
		else if (f == 'W') z.push_back(65);
		else if (f == 'X') z.push_back(67);
		else if (f == 'Y') z.push_back(69);
		else if (f == 'Z') z.push_back(71);
		else if (f == 'a') z.push_back(73);
		else if (f == 'b') z.push_back(75);
		else if (f == 'c') z.push_back(77);
		else if (f == 'd') z.push_back(79);
		else if (f == 'e') z.push_back(81);
		else if (f == 'f') z.push_back(83);
		else if (f == 'g') z.push_back(85);
		else if (f == 'h') z.push_back(87);
		else if (f == 'i') z.push_back(89);
		else if (f == 'j') z.push_back(91);
		else if (f == 'k') z.push_back(93);
		else if (f == 'l') z.push_back(95);
		else if (f == 'm') z.push_back(97);
		else if (f == 'n') z.push_back(99);
		else if (f == 'o') z.push_back(101);
		else if (f == 'p') z.push_back(103);
		else if (f == 'q') z.push_back(105);
		else if (f == 'r') z.push_back(107);
		else if (f == 's') z.push_back(109);
		else if (f == 't') z.push_back(111);
		else if (f == 'u') z.push_back(113);
		else if (f == 'v') z.push_back(115);
		else if (f == 'w') z.push_back(117);
		else if (f == 'x') z.push_back(119);
		else if (f == 'y') z.push_back(121);
		else if (f == 'z') z.push_back(123);
		else if (f == '!') z.push_back(125);
		else if (f == '"') z.push_back(127);
		else if (f == '#') z.push_back(129);
		else if (f == '$') z.push_back(131);
		else if (f == '%') z.push_back(133);
		else if (f == '&') z.push_back(135);
		else if (f == '(') z.push_back(137);
		else if (f == ')') z.push_back(139);
		else if (f == '-') z.push_back(141);
		else if (f == '=') z.push_back(143);
		else if (f == '^') z.push_back(145);
		else if (f == '~') z.push_back(147);
		else if (f == '|') z.push_back(149);
		else if (f == '@') z.push_back(151);
		else if (f == '`') z.push_back(153);
		else if (f == '[') z.push_back(155);
		else if (f == '{') z.push_back(157);
		else if (f == ';') z.push_back(159);
		else if (f == '+') z.push_back(161);
		else if (f == ':') z.push_back(163);
		else if (f == '*') z.push_back(165);
		else if (f == ']') z.push_back(167);
		else if (f == '}') z.push_back(169);
		else if (f == ',') z.push_back(171);
		else if (f == '<') z.push_back(173);
		else if (f == '.') z.push_back(175);
		else if (f == '>') z.push_back(177);
		else if (f == '/') z.push_back(179);
		else if (f == '?') z.push_back(181);
		else if (f == '_') z.push_back(183);
		else if (f == ' ') z.push_back(185);
		else if (f == '\n') z.push_back(187);
		else if (f == '\t') z.push_back(189);
	}

	a = DecimalToBinary(z);
}

void conv::BinaryToString(string& a)
{
	string z = "";
	char str[95] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
				  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
				  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
				  '!', '"', '#', '$', '%', '&', '(', ')', '-', '=', '^', '~', '|', '@', '`', '[', '{', ';', '+', ':', '*', ']', '}', ',', '<', '.',
				  '>', '/', '?', '_', ' ', '\n', '\t' };
	
	for (size_t i = 0; i < a.size(); i += 7)
	{
		size_t temp = 0;

		for (size_t j = 0; j < 7; j++)
		{
			if (a[i + j] == '1')
			{
				temp += static_cast<size_t>(pow(2, 6 - j));
			}
		}

		z += str[temp];
	}

	a = z;
}

uint8_t conv::stoi(const string& a)
{
	uint8_t z = 0;

	for (auto f : a)
	{
		z = 10 * z + (f - '0');
	}

	return z;
}

tuple<vector<string>, unsigned long long> conv::split(const string& a, const unsigned long long& b)
{
	vector<string> z;
	string buf;

	for (unsigned long long i = 0; i < a.size(); i += b)
	{
		buf = "";

		for (unsigned long long j = 0; j < b; j++)
		{
			buf += a[i + j];
		}

		z.push_back(buf);
	}

	return { z, z.size() - 1 };
}

string conv::DecimalToBinary(const vector<int>& a)
{
	string z = "";

	for (auto f : a)
	{
		int temp = 0;

		for (int i = 0; f > 0; i++)
		{
			temp += (f % 2) * static_cast<int>(pow(10, i));
			f /= 2;
		}

		if (temp < 10) z += "0000000" + to_string(temp);
		else if (temp < 100) z += "000000" + to_string(temp);
		else if (temp < 1000) z += "00000" + to_string(temp);
		else if (temp < 10000) z += "0000" + to_string(temp);
		else if (temp < 100000) z += "000" + to_string(temp);
		else if (temp < 1000000) z += "00" + to_string(temp);
		else if (temp < 10000000) z += "0" + to_string(temp);
		else z += to_string(temp);
	}

	return z;
}

string StringBitOperator::And(string a, string b)
{
	StringsFormat(a, b);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = a[i] == b[i] ? a[i] : '0';
	}

	return a;
}

string StringBitOperator::Or(string a, string b)
{
	StringsFormat(a, b);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = (a[i] == '1' || b[i] == '1') ? '1' : '0';
	}

	return a;
}

string StringBitOperator::Not(string a)
{
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = a[i] == '0' ? '1' : '0';
	}

	return a;
}

string StringBitOperator::Nand(string a, string b)
{
	StringsFormat(a, b);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = a[i] == b[i] ? a[i] : '0';
		a[i] = a[i] == '0' ? '1' : '0';
	}

	return a;
}

string StringBitOperator::Nor(string a, string b)
{
	StringsFormat(a, b);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = (a[i] == '1' || b[i] == '1') ? '1' : '0';
		a[i] = a[i] == '0' ? '1' : '0';
	}

	return a;
}

string StringBitOperator::Xor(string a, string b)
{
	StringsFormat(a, b);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		a[i] = a[i] != b[i] ? '1' : '0';
	}

	return a;
}

void StringBitOperator::StringsFormat(string& a, string& b)
{
	while (a.size() < b.size()) a += "0";
	while (b.size() < a.size()) b += "0";
}