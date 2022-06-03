#pragma once
#include "Gacha.hpp"

bool argregex(
    const std::string &arg,
    const char *rgx1,
    const char *rgx2 = NULL);
int showHelp();

namespace Gacha
{
    void printBanner();
    bool isFileExist(const string &fl);
}  // namespace Gacha

namespace Fx
{
    extern const string e;
    extern const string b;
    extern const string ub;
    extern const string d;
    extern const string ud;
    extern const string i;
    extern const string ui;
    extern const string ul;
    extern const string uul;
    extern const string bl;
    extern const string ubl;
    extern const string s;
    extern const string us;
    extern const string reset_base;
    extern const string reset;
    extern const std::regex escape_regex;
    extern const std::regex color_regex;
    string uncolor(const string &s);
}  // namespace Fx

namespace Color
{
    extern const string bg_black;
    extern const string fg_white;
    extern const string fg_green;
    extern const string fg_red;
    string hextostr(
        string hexa,
        const bool &t_to_256 = false,
        const string &depth  = "fg");
}  // namespace Color

namespace Logger
{
    enum LogMode
    {
        Info,
        Warning,
        Error,
    };
    void setmode(const LogMode &mode);
    void Debug(const char *msg, ...) FMTARGS(1);
    void error(const char *_s, ...) FMTARGS(1);
}  // namespace Logger
