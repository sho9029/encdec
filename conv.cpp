#include "conv.h"


void conv::StringToBinary(string& a)
{
    vector<int> z;

    for (auto f : a)
    {
        if (f == '0') z.emplace_back(VID_0);
        else if (f == '1') z.emplace_back(VID_1);
        else if (f == '2') z.emplace_back(VID_2);
        else if (f == '3') z.emplace_back(VID_3);
        else if (f == '4') z.emplace_back(VID_4);
        else if (f == '5') z.emplace_back(VID_5);
        else if (f == '6') z.emplace_back(VID_6);
        else if (f == '7') z.emplace_back(VID_7);
        else if (f == '8') z.emplace_back(VID_8);
        else if (f == '9') z.emplace_back(VID_9);
        else if (f == 'A') z.emplace_back(VID_A);
        else if (f == 'B') z.emplace_back(VID_B);
        else if (f == 'C') z.emplace_back(VID_C);
        else if (f == 'D') z.emplace_back(VID_D);
        else if (f == 'E') z.emplace_back(VID_E);
        else if (f == 'F') z.emplace_back(VID_F);
        else if (f == 'G') z.emplace_back(VID_G);
        else if (f == 'H') z.emplace_back(VID_H);
        else if (f == 'I') z.emplace_back(VID_I);
        else if (f == 'J') z.emplace_back(VID_J);
        else if (f == 'K') z.emplace_back(VID_K);
        else if (f == 'L') z.emplace_back(VID_L);
        else if (f == 'M') z.emplace_back(VID_M);
        else if (f == 'N') z.emplace_back(VID_N);
        else if (f == 'O') z.emplace_back(VID_O);
        else if (f == 'P') z.emplace_back(VID_P);
        else if (f == 'Q') z.emplace_back(VID_Q);
        else if (f == 'R') z.emplace_back(VID_R);
        else if (f == 'S') z.emplace_back(VID_S);
        else if (f == 'T') z.emplace_back(VID_T);
        else if (f == 'U') z.emplace_back(VID_U);
        else if (f == 'V') z.emplace_back(VID_V);
        else if (f == 'W') z.emplace_back(VID_W);
        else if (f == 'X') z.emplace_back(VID_X);
        else if (f == 'Y') z.emplace_back(VID_Y);
        else if (f == 'Z') z.emplace_back(VID_Z);
        else if (f == 'a') z.emplace_back(VID_a);
        else if (f == 'b') z.emplace_back(VID_b);
        else if (f == 'c') z.emplace_back(VID_c);
        else if (f == 'd') z.emplace_back(VID_d);
        else if (f == 'e') z.emplace_back(VID_e);
        else if (f == 'f') z.emplace_back(VID_f);
        else if (f == 'g') z.emplace_back(VID_g);
        else if (f == 'h') z.emplace_back(VID_h);
        else if (f == 'i') z.emplace_back(VID_i);
        else if (f == 'j') z.emplace_back(VID_j);
        else if (f == 'k') z.emplace_back(VID_k);
        else if (f == 'l') z.emplace_back(VID_l);
        else if (f == 'm') z.emplace_back(VID_m);
        else if (f == 'n') z.emplace_back(VID_n);
        else if (f == 'o') z.emplace_back(VID_o);
        else if (f == 'p') z.emplace_back(VID_p);
        else if (f == 'q') z.emplace_back(VID_q);
        else if (f == 'r') z.emplace_back(VID_r);
        else if (f == 's') z.emplace_back(VID_s);
        else if (f == 't') z.emplace_back(VID_t);
        else if (f == 'u') z.emplace_back(VID_u);
        else if (f == 'v') z.emplace_back(VID_v);
        else if (f == 'w') z.emplace_back(VID_w);
        else if (f == 'x') z.emplace_back(VID_x);
        else if (f == 'y') z.emplace_back(VID_y);
        else if (f == 'z') z.emplace_back(VID_z);
        else if (f == '!') z.emplace_back(VID_OEM_EXCLAMATION);
        else if (f == '"') z.emplace_back(VID_OEM_DOUBLEQUOTATION);
        else if (f == '#') z.emplace_back(VID_OEM_POUND);
        else if (f == '$') z.emplace_back(VID_OEM_DOLLAR);
        else if (f == '%') z.emplace_back(VID_OEM_PERCENT);
        else if (f == '&') z.emplace_back(VID_OEM_AMPERSAND);
        else if (f == '(') z.emplace_back(VID_OEM_LEFTPAREN);
        else if (f == ')') z.emplace_back(VID_OEM_RIGHTPAREN);
        else if (f == '-') z.emplace_back(VID_OEM_MINUS);
        else if (f == '=') z.emplace_back(VID_OEM_EQUAL);
        else if (f == '^') z.emplace_back(VID_OEM_HAT);
        else if (f == '~') z.emplace_back(VID_OEM_TILDE);
        else if (f == '|') z.emplace_back(VID_OEM_VERTICALBAR);
        else if (f == '@') z.emplace_back(VID_OEM_ATMARK);
        else if (f == '`') z.emplace_back(VID_OEM_BACKAPOSTROPHE);
        else if (f == '[') z.emplace_back(VID_OEM_LEFTBRACKET);
        else if (f == '{') z.emplace_back(VID_OEM_LEFTBRACE);
        else if (f == ';') z.emplace_back(VID_OEM_SEMICOLON);
        else if (f == '+') z.emplace_back(VID_OEM_PLUS);
        else if (f == ':') z.emplace_back(VID_OEM_COLON);
        else if (f == '*') z.emplace_back(VID_OEM_ASTERISK);
        else if (f == ']') z.emplace_back(VID_OEM_RIGHTBRACKET);
        else if (f == '}') z.emplace_back(VID_OEM_RIGHTBRACE);
        else if (f == ',') z.emplace_back(VID_OEM_COMMA);
        else if (f == '<') z.emplace_back(VID_OEM_LESSTHAN);
        else if (f == '.') z.emplace_back(VID_OEM_PERIOD);
        else if (f == '>') z.emplace_back(VID_OEM_GRATERTHAN);
        else if (f == '/') z.emplace_back(VID_OEM_SLASH);
        else if (f == '?') z.emplace_back(VID_OEM_QUESTION);
        else if (f == '_') z.emplace_back(VID_OEM_UNDERBAR);
        else if (f == ' ') z.emplace_back(VID_SPACE);
        else if (f == '\n') z.emplace_back(VID_ES_N);
        else if (f == '\t') z.emplace_back(VID_ES_T);
        else z.emplace_back(VID_UNDEFINED);
    }

    a = DecimalToBinary(z);
}

uint8_t conv::stoi(const string& a)
{
    if (a.empty()) {
        throw exception("Empty string cannot be converted to number");
    }

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

        for (unsigned long long j = 0; j < b && i + j < size; j++)
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
