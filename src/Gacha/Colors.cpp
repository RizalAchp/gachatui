#include "cli.hpp"

#define R(x) round(x)
namespace Color
{
int truecolor(const int &r, const int &g, const int &b)
{
    if (const int red = R(r / 11.0);
        red == R((double)g / 11) and red == R((double)b / 11))
        return 232 + red;
    else
        return R(r / 51.0) * 36 + R(g / 51.0) * 6 + R(b / 51.0) + 16;
}
string hextostr(string hexa, const bool &t_to_256, const string &depth)
{
    if (hexa.size() > 1)
    {
        hexa.erase(0, 1);
        for (auto &c : hexa)
            if (not isxdigit(c))
                return "";
        string pre = Fx::e + (depth == "fg" ? "38" : "48") + ";" +
                     (t_to_256 ? "5;" : "2;");

        if (hexa.size() == 2)
        {
            int h_int = stoi(hexa, nullptr, 16);
            if (t_to_256)
                return pre + to_string(truecolor(h_int, h_int, h_int)) + "m";
            else
            {
                string h_str = to_string(h_int);
                return pre + h_str + ";" + h_str + ";" + h_str + "m";
            }
        }
        else if (hexa.size() == 6)
        {
            if (t_to_256)
                return pre +
                       to_string(
                           truecolor(stoi(hexa.substr(0, 2), nullptr, 16),
                                     stoi(hexa.substr(2, 2), nullptr, 16),
                                     stoi(hexa.substr(4, 2), nullptr, 16))) +
                       "m";
            else
                return pre + to_string(stoi(hexa.substr(0, 2), nullptr, 16)) +
                       ";" + to_string(stoi(hexa.substr(2, 2), nullptr, 16)) +
                       ";" + to_string(stoi(hexa.substr(4, 2), nullptr, 16)) +
                       "m";
        }
        else
            Logger::error("Invalid size of hex value: %s\n", hexa.c_str());
    }
    else
        Logger::error("Hex value missing: %s\n", hexa.c_str());
    return "";
}

} // namespace Color
