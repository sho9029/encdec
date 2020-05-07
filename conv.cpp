#include "conv.h"

void conv::StringToBinary(string& a)
{
	vector<int> z;

	for (auto f : a)
	{
		if (f == '0') z.emplace_back(1);
		else if (f == '1') z.emplace_back(3);
		else if (f == '2') z.emplace_back(5);
		else if (f == '3') z.emplace_back(7);
		else if (f == '4') z.emplace_back(9);
		else if (f == '5') z.emplace_back(11);
		else if (f == '6') z.emplace_back(13);
		else if (f == '7') z.emplace_back(15);
		else if (f == '8') z.emplace_back(17);
		else if (f == '9') z.emplace_back(19);
		else if (f == 'A') z.emplace_back(21);
		else if (f == 'B') z.emplace_back(23);
		else if (f == 'C') z.emplace_back(25);
		else if (f == 'D') z.emplace_back(27);
		else if (f == 'E') z.emplace_back(29);
		else if (f == 'F') z.emplace_back(31);
		else if (f == 'G') z.emplace_back(33);
		else if (f == 'H') z.emplace_back(35);
		else if (f == 'I') z.emplace_back(37);
		else if (f == 'J') z.emplace_back(39);
		else if (f == 'K') z.emplace_back(41);
		else if (f == 'L') z.emplace_back(43);
		else if (f == 'M') z.emplace_back(45);
		else if (f == 'N') z.emplace_back(47);
		else if (f == 'O') z.emplace_back(49);
		else if (f == 'P') z.emplace_back(51);
		else if (f == 'Q') z.emplace_back(53);
		else if (f == 'R') z.emplace_back(55);
		else if (f == 'S') z.emplace_back(57);
		else if (f == 'T') z.emplace_back(59);
		else if (f == 'U') z.emplace_back(61);
		else if (f == 'V') z.emplace_back(63);
		else if (f == 'W') z.emplace_back(65);
		else if (f == 'X') z.emplace_back(67);
		else if (f == 'Y') z.emplace_back(69);
		else if (f == 'Z') z.emplace_back(71);
		else if (f == 'a') z.emplace_back(73);
		else if (f == 'b') z.emplace_back(75);
		else if (f == 'c') z.emplace_back(77);
		else if (f == 'd') z.emplace_back(79);
		else if (f == 'e') z.emplace_back(81);
		else if (f == 'f') z.emplace_back(83);
		else if (f == 'g') z.emplace_back(85);
		else if (f == 'h') z.emplace_back(87);
		else if (f == 'i') z.emplace_back(89);
		else if (f == 'j') z.emplace_back(91);
		else if (f == 'k') z.emplace_back(93);
		else if (f == 'l') z.emplace_back(95);
		else if (f == 'm') z.emplace_back(97);
		else if (f == 'n') z.emplace_back(99);
		else if (f == 'o') z.emplace_back(101);
		else if (f == 'p') z.emplace_back(103);
		else if (f == 'q') z.emplace_back(105);
		else if (f == 'r') z.emplace_back(107);
		else if (f == 's') z.emplace_back(109);
		else if (f == 't') z.emplace_back(111);
		else if (f == 'u') z.emplace_back(113);
		else if (f == 'v') z.emplace_back(115);
		else if (f == 'w') z.emplace_back(117);
		else if (f == 'x') z.emplace_back(119);
		else if (f == 'y') z.emplace_back(121);
		else if (f == 'z') z.emplace_back(123);
		else if (f == '!') z.emplace_back(125);
		else if (f == '"') z.emplace_back(127);
		else if (f == '#') z.emplace_back(129);
		else if (f == '$') z.emplace_back(131);
		else if (f == '%') z.emplace_back(133);
		else if (f == '&') z.emplace_back(135);
		else if (f == '(') z.emplace_back(137);
		else if (f == ')') z.emplace_back(139);
		else if (f == '-') z.emplace_back(141);
		else if (f == '=') z.emplace_back(143);
		else if (f == '^') z.emplace_back(145);
		else if (f == '~') z.emplace_back(147);
		else if (f == '|') z.emplace_back(149);
		else if (f == '@') z.emplace_back(151);
		else if (f == '`') z.emplace_back(153);
		else if (f == '[') z.emplace_back(155);
		else if (f == '{') z.emplace_back(157);
		else if (f == ';') z.emplace_back(159);
		else if (f == '+') z.emplace_back(161);
		else if (f == ':') z.emplace_back(163);
		else if (f == '*') z.emplace_back(165);
		else if (f == ']') z.emplace_back(167);
		else if (f == '}') z.emplace_back(169);
		else if (f == ',') z.emplace_back(171);
		else if (f == '<') z.emplace_back(173);
		else if (f == '.') z.emplace_back(175);
		else if (f == '>') z.emplace_back(177);
		else if (f == '/') z.emplace_back(179);
		else if (f == '?') z.emplace_back(181);
		else if (f == '_') z.emplace_back(183);
		else if (f == ' ') z.emplace_back(185);
		else if (f == '\n') z.emplace_back(187);
		else if (f == '\t') z.emplace_back(189);
	}

	a = DecimalToBinary(z);
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

	for (unsigned long long i = 0, size = a.size(); i < size; i += b)
	{
		buf = "";

		for (unsigned long long j = 0; j < b; j++)
		{
			buf += a[i + j];
		}

		z.emplace_back(buf);
	}

	return { z, z.size()};
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
