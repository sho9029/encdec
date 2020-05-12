#include "random.h"

string random::rand(const string& a)
{
    string z;
    uint8_t sum = 0, temp;
    temp = conv::StringToDecimal(a);

    for (uint8_t i = 0; temp > 0; i++)
    {
        sum += (temp % 2) * static_cast<uint8_t>(pow(10, i));
        temp /= 2;
    }

    z = to_string(sum);

    if (z.size() != a.size() * 8)
    {
        while (z.size() < a.size() * 8)
        {
            z += z;
        }
        while (z.size() > a.size() * 8)
        {
            z.erase(z.end() - 1);
        }
    }

    return z;
}