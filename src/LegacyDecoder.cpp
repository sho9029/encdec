#include "LegacyDecoder.h"
#include <cmath>
#include <vector>
#include <string>
#include <tuple>
#include <exception>

namespace legacy {

void v1_3::Decrypt(std::ifstream& in, std::ofstream& out, std::string key, size_t fileSize) {
    // 1. 疑似乱数生成
    key = rand(key);

    // 2. 鍵の分割と変換
    auto [spkeyBuf, spkeySize] = split(key, 2);
    if (spkeySize == 0) throw std::exception("Legacy: Invalid key");

    std::vector<uint8_t> spkey;
    for (auto& f : spkeyBuf) spkey.emplace_back(stoi(f));

    // 3. XORループ（固定長バッファ方式）
    uint8_t a;
    std::vector<uint8_t> buffer;
    size_t processedSize = 0;
    size_t splitSize = 1024 * 1024 * 10; // デフォルト10MB

    buffer.reserve(splitSize);

    while (!in.eof()) {
        in.read((char*)&a, 1);
        if (in.eof()) break;

        a ^= spkey[processedSize % spkeySize];
        processedSize++;
        buffer.emplace_back(a);

        if (processedSize % splitSize == 0) {
            for (auto byte : buffer) out.write((char*)&byte, 1);
            buffer.clear();
            PrintProgress(processedSize, fileSize);
        }
    }

    for (auto byte : buffer) out.write((char*)&byte, 1);
    PrintProgress(processedSize, fileSize);
}

std::string v1_3::rand(const std::string& a) {
    std::string z;
    uint64_t sum = 0, temp;
    temp = stoiorder(a);

    for (uint8_t i = 0; temp > 0; i++) {
        sum += (temp % 2) * static_cast<uint64_t>(std::pow(10, i));
        temp /= 2;
    }

    z = std::to_string(sum);

    if (z.size() != a.size() * 8) {
        while (z.size() < a.size() * 8) z += randjoin(z);
        while (z.size() > a.size() * 8) z.erase(z.end() - 1);
    }
    return z;
}

uint64_t v1_3::stoiorder(const std::string& a) {
    uint64_t z = 0;
    double weight = 1.0;

    for (auto f : a) {
        if (f == '0') z += static_cast<uint64_t>(weight * VID_0);
        else if (f == '1') z += static_cast<uint64_t>(weight * VID_1);
        else if (f == '2') z += static_cast<uint64_t>(weight * VID_2);
        else if (f == '3') z += static_cast<uint64_t>(weight * VID_3);
        else if (f == '4') z += static_cast<uint64_t>(weight * VID_4);
        else if (f == '5') z += static_cast<uint64_t>(weight * VID_5);
        else if (f == '6') z += static_cast<uint64_t>(weight * VID_6);
        else if (f == '7') z += static_cast<uint64_t>(weight * VID_7);
        else if (f == '8') z += static_cast<uint64_t>(weight * VID_8);
        else if (f == '9') z += static_cast<uint64_t>(weight * VID_9);
        else if (f == 'A') z += static_cast<uint64_t>(weight * VID_A);
        else if (f == 'B') z += static_cast<uint64_t>(weight * VID_B);
        else if (f == 'C') z += static_cast<uint64_t>(weight * VID_C);
        else if (f == 'D') z += static_cast<uint64_t>(weight * VID_D);
        else if (f == 'E') z += static_cast<uint64_t>(weight * VID_E);
        else if (f == 'F') z += static_cast<uint64_t>(weight * VID_F);
        else if (f == 'G') z += static_cast<uint64_t>(weight * VID_G);
        else if (f == 'H') z += static_cast<uint64_t>(weight * VID_H);
        else if (f == 'I') z += static_cast<uint64_t>(weight * VID_I);
        else if (f == 'J') z += static_cast<uint64_t>(weight * VID_J);
        else if (f == 'K') z += static_cast<uint64_t>(weight * VID_K);
        else if (f == 'L') z += static_cast<uint64_t>(weight * VID_L);
        else if (f == 'M') z += static_cast<uint64_t>(weight * VID_M);
        else if (f == 'N') z += static_cast<uint64_t>(weight * VID_N);
        else if (f == 'O') z += static_cast<uint64_t>(weight * VID_O);
        else if (f == 'P') z += static_cast<uint64_t>(weight * VID_P);
        else if (f == 'Q') z += static_cast<uint64_t>(weight * VID_Q);
        else if (f == 'R') z += static_cast<uint64_t>(weight * VID_R);
        else if (f == 'S') z += static_cast<uint64_t>(weight * VID_S);
        else if (f == 'T') z += static_cast<uint64_t>(weight * VID_T);
        else if (f == 'U') z += static_cast<uint64_t>(weight * VID_U);
        else if (f == 'V') z += static_cast<uint64_t>(weight * VID_V);
        else if (f == 'W') z += static_cast<uint64_t>(weight * VID_W);
        else if (f == 'X') z += static_cast<uint64_t>(weight * VID_X);
        else if (f == 'Y') z += static_cast<uint64_t>(weight * VID_Y);
        else if (f == 'Z') z += static_cast<uint64_t>(weight * VID_Z);
        else if (f == 'a') z += static_cast<uint64_t>(weight * VID_a);
        else if (f == 'b') z += static_cast<uint64_t>(weight * VID_b);
        else if (f == 'c') z += static_cast<uint64_t>(weight * VID_c);
        else if (f == 'd') z += static_cast<uint64_t>(weight * VID_d);
        else if (f == 'e') z += static_cast<uint64_t>(weight * VID_e);
        else if (f == 'f') z += static_cast<uint64_t>(weight * VID_f);
        else if (f == 'g') z += static_cast<uint64_t>(weight * VID_g);
        else if (f == 'h') z += static_cast<uint64_t>(weight * VID_h);
        else if (f == 'i') z += static_cast<uint64_t>(weight * VID_i);
        else if (f == 'j') z += static_cast<uint64_t>(weight * VID_j);
        else if (f == 'k') z += static_cast<uint64_t>(weight * VID_k);
        else if (f == 'l') z += static_cast<uint64_t>(weight * VID_l);
        else if (f == 'm') z += static_cast<uint64_t>(weight * VID_m);
        else if (f == 'n') z += static_cast<uint64_t>(weight * VID_n);
        else if (f == 'o') z += static_cast<uint64_t>(weight * VID_o);
        else if (f == 'p') z += static_cast<uint64_t>(weight * VID_p);
        else if (f == 'q') z += static_cast<uint64_t>(weight * VID_q);
        else if (f == 'r') z += static_cast<uint64_t>(weight * VID_r);
        else if (f == 's') z += static_cast<uint64_t>(weight * VID_s);
        else if (f == 't') z += static_cast<uint64_t>(weight * VID_t);
        else if (f == 'u') z += static_cast<uint64_t>(weight * VID_u);
        else if (f == 'v') z += static_cast<uint64_t>(weight * VID_v);
        else if (f == 'w') z += static_cast<uint64_t>(weight * VID_w);
        else if (f == 'x') z += static_cast<uint64_t>(weight * VID_x);
        else if (f == 'y') z += static_cast<uint64_t>(weight * VID_y);
        else if (f == 'z') z += static_cast<uint64_t>(weight * VID_z);
        else if (f == '!') z += static_cast<uint64_t>(weight * VID_OEM_EXCLAMATION);
        else if (f == '"') z += static_cast<uint64_t>(weight * VID_OEM_DOUBLEQUOTATION);
        else if (f == '#') z += static_cast<uint64_t>(weight * VID_OEM_POUND);
        else if (f == '$') z += static_cast<uint64_t>(weight * VID_OEM_DOLLAR);
        else if (f == '%') z += static_cast<uint64_t>(weight * VID_OEM_PERCENT);
        else if (f == '&') z += static_cast<uint64_t>(weight * VID_OEM_AMPERSAND);
        else if (f == '(') z += static_cast<uint64_t>(weight * VID_OEM_LEFTPAREN);
        else if (f == ')') z += static_cast<uint64_t>(weight * VID_OEM_RIGHTPAREN);
        else if (f == '-') z += static_cast<uint64_t>(weight * VID_OEM_MINUS);
        else if (f == '=') z += static_cast<uint64_t>(weight * VID_OEM_EQUAL);
        else if (f == '^') z += static_cast<uint64_t>(weight * VID_OEM_HAT);
        else if (f == '~') z += static_cast<uint64_t>(weight * VID_OEM_TILDE);
        else if (f == '|') z += static_cast<uint64_t>(weight * VID_OEM_VERTICALBAR);
        else if (f == '@') z += static_cast<uint64_t>(weight * VID_OEM_ATMARK);
        else if (f == '`') z += static_cast<uint64_t>(weight * VID_OEM_BACKAPOSTROPHE);
        else if (f == '[') z += static_cast<uint64_t>(weight * VID_OEM_LEFTBRACKET);
        else if (f == '{') z += static_cast<uint64_t>(weight * VID_OEM_LEFTBRACE);
        else if (f == ';') z += static_cast<uint64_t>(weight * VID_OEM_SEMICOLON);
        else if (f == '+') z += static_cast<uint64_t>(weight * VID_OEM_PLUS);
        else if (f == ':') z += static_cast<uint64_t>(weight * VID_OEM_COLON);
        else if (f == '*') z += static_cast<uint64_t>(weight * VID_OEM_ASTERISK);
        else if (f == ']') z += static_cast<uint64_t>(weight * VID_OEM_RIGHTBRACKET);
        else if (f == '}') z += static_cast<uint64_t>(weight * VID_OEM_RIGHTBRACE);
        else if (f == ',') z += static_cast<uint64_t>(weight * VID_OEM_COMMA);
        else if (f == '<') z += static_cast<uint64_t>(weight * VID_OEM_LESSTHAN);
        else if (f == '.') z += static_cast<uint64_t>(weight * VID_OEM_PERIOD);
        else if (f == '>') z += static_cast<uint64_t>(weight * VID_OEM_GRATERTHAN);
        else if (f == '/') z += static_cast<uint64_t>(weight * VID_OEM_SLASH);
        else if (f == '?') z += static_cast<uint64_t>(weight * VID_OEM_QUESTION);
        else if (f == '_') z += static_cast<uint64_t>(weight * VID_OEM_UNDERBAR);
        else if (f == ' ') z += static_cast<uint64_t>(weight * VID_SPACE);
        else if (f == '\n') z += static_cast<uint64_t>(weight * VID_ES_N);
        else if (f == '\t') z += static_cast<uint64_t>(weight * VID_ES_T);
        else z += static_cast<uint64_t>(weight * VID_UNDEFINED);

        weight *= 1.1;
    }
    return z;
}

std::string v1_3::randjoin(const std::string& a) {
    if (a.length() < 2) return a;
    return a.substr(1) + a[0];
}

void v1_3::PrintProgress(const size_t& nowSize, const size_t& maxSize) {
    std::cout << "\r" << std::flush;
    if (maxSize < 1e3) std::cout << nowSize << "B / " << maxSize << "B";
    else if (maxSize < 1e6) std::cout << nowSize / 1e3 << "KB / " << maxSize / 1e3 << "KB";
    else if (maxSize < 1e9) std::cout << nowSize / 1e6 << "MB / " << maxSize / 1e6 << "MB";
    else std::cout << nowSize / 1e9 << "GB / " << maxSize / 1e9 << "GB";
}

uint8_t v1_3::stoi(const std::string& a) {
    if (a.empty()) {
        throw std::exception("Empty string cannot be converted to number");
    }
    uint8_t z = 0;
    for (auto f : a) {
        z = 10 * z + (f - '0');
    }
    return z;
}

std::tuple<std::vector<std::string>, unsigned long long> v1_3::split(const std::string& a, const unsigned long long& b) {
    std::vector<std::string> z;
    std::string buf;
    for (unsigned long long i = 0, size = a.size(); i < size; i += b) {
        buf = "";
        for (unsigned long long j = 0; j < b && i + j < size; j++) {
            buf += a[i + j];
        }
        z.emplace_back(buf);
    }
    return { z, z.size() };
}

} // namespace legacy
