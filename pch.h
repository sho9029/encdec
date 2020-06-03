#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Windows.h"

using namespace std;

constexpr auto VID_0 = 1;
constexpr auto VID_1 = 3;
constexpr auto VID_2 = 5;
constexpr auto VID_3 = 7;
constexpr auto VID_4 = 9;
constexpr auto VID_5 = 11;
constexpr auto VID_6 = 13;
constexpr auto VID_7 = 15;
constexpr auto VID_8 = 17;
constexpr auto VID_9 = 19;
constexpr auto VID_A = 21;
constexpr auto VID_B = 23;
constexpr auto VID_C = 25;
constexpr auto VID_D = 27;
constexpr auto VID_E = 29;
constexpr auto VID_F = 31;
constexpr auto VID_G = 33;
constexpr auto VID_H = 35;
constexpr auto VID_I = 37;
constexpr auto VID_J = 39;
constexpr auto VID_K = 41;
constexpr auto VID_L = 43;
constexpr auto VID_M = 45;
constexpr auto VID_N = 47;
constexpr auto VID_O = 49;
constexpr auto VID_P = 51;
constexpr auto VID_Q = 53;
constexpr auto VID_R = 55;
constexpr auto VID_S = 57;
constexpr auto VID_T = 59;
constexpr auto VID_U = 61;
constexpr auto VID_V = 63;
constexpr auto VID_W = 65;
constexpr auto VID_X = 67;
constexpr auto VID_Y = 69;
constexpr auto VID_Z = 71;
constexpr auto VID_a = 73;
constexpr auto VID_b = 75;
constexpr auto VID_c = 77;
constexpr auto VID_d = 79;
constexpr auto VID_e = 81;
constexpr auto VID_f = 83;
constexpr auto VID_g = 85;
constexpr auto VID_h = 87;
constexpr auto VID_i = 89;
constexpr auto VID_j = 91;
constexpr auto VID_k = 93;
constexpr auto VID_l = 95;
constexpr auto VID_m = 97;
constexpr auto VID_n = 99;
constexpr auto VID_o = 101;
constexpr auto VID_p = 103;
constexpr auto VID_q = 105;
constexpr auto VID_r = 107;
constexpr auto VID_s = 109;
constexpr auto VID_t = 111;
constexpr auto VID_u = 113;
constexpr auto VID_v = 115;
constexpr auto VID_w = 117;
constexpr auto VID_x = 119;
constexpr auto VID_y = 121;
constexpr auto VID_z = 123;
constexpr auto VID_OEM_EXCLAMATION = 125;
constexpr auto VID_OEM_DOUBLEQUOTATION = 127;
constexpr auto VID_OEM_POUND = 129;
constexpr auto VID_OEM_DOLLAR = 131;
constexpr auto VID_OEM_PERCENT = 133;
constexpr auto VID_OEM_AMPERSAND = 135;
constexpr auto VID_OEM_LEFTPAREN = 137;
constexpr auto VID_OEM_RIGHTPAREN = 139;
constexpr auto VID_OEM_MINUS = 141;
constexpr auto VID_OEM_EQUAL = 143;
constexpr auto VID_OEM_HAT = 145;
constexpr auto VID_OEM_TILDE = 147;
constexpr auto VID_OEM_VERTICALBAR = 149;
constexpr auto VID_OEM_ATMARK = 151;
constexpr auto VID_OEM_BACKAPOSTROPHE = 153;
constexpr auto VID_OEM_LEFTBRACKET = 155;
constexpr auto VID_OEM_LEFTBRACE = 157;
constexpr auto VID_OEM_SEMICOLON = 159;
constexpr auto VID_OEM_PLUS = 161;
constexpr auto VID_OEM_COLON = 163;
constexpr auto VID_OEM_ASTERISK = 165;
constexpr auto VID_OEM_RIGHTBRACKET = 167;
constexpr auto VID_OEM_RIGHTBRACE = 169;
constexpr auto VID_OEM_COMMA = 171;
constexpr auto VID_OEM_LESSTHAN = 173;
constexpr auto VID_OEM_PERIOD = 175;
constexpr auto VID_OEM_GRATERTHAN = 177;
constexpr auto VID_OEM_SLASH = 179;
constexpr auto VID_OEM_QUESTION = 181;
constexpr auto VID_OEM_UNDERBAR = 183;
constexpr auto VID_SPACE = 185;
constexpr auto VID_ES_N = 187;
constexpr auto VID_ES_T = 189;
constexpr auto VID_UNDEFINED = 191;

//identifier
constexpr size_t identifierSize = 3;
constexpr uint8_t IDENTIFIER[identifierSize]= { 0x45, 0x44, 0xff };

//version
constexpr size_t versionSize = 2;
constexpr uint8_t ALGORITHM = 1;
constexpr uint8_t MAJOR = 2;
constexpr uint8_t VERSION[versionSize] = { ALGORITHM, MAJOR };