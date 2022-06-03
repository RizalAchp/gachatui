/* #include <iostream> */
#include "cli.hpp"

using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::string;

bool argregex(const string &arg, const char *rgx1, const char *rgx2)
{
    if (!rgx2)
        return regex_match(arg, regex(rgx1));
    return regex_match(arg, regex(rgx1)) | regex_match(arg, regex(rgx2));
}

int showHelp()
{
    Gacha::printBanner();
    cout << "usage: gacha [-h] [-v] [-i <infile*.csv>] [-0 <outfile*.csv>] "
            "[--debug]\n\n"
         << "optional arguments:\n"
         << "  -h | --help    | help            show this help message and "
            "exit\n"
         << "  -v | --version | version         show version info and exit\n"
         << "  -t | --tui     | tuimode         run in TUI MODE (Terminal "
            "User Interface)\n"
         << "  -i | --in      | input=<f*.csv>  input for reverence list "
            "object for gacha\n"
         << "     |           |                 (default to "
            "`path/relative/data.csv`)\n"
         << "  -o | --out     | output=<f*.csv> output file for list gacha "
            "object generated\n"
         << "     |           |                 (default to "
            "`path/relative/data.csv`)\n"
         << "  -d | --debug   | debug           start in DEBUG mode: shows "
            "microsecond timer\n"
         << "                                   and sets loglevel to DEBUG\n"
         << endl;

    return 0;
}

namespace Gacha
{

    bool isFileExist(const string &fl)
    {
        DEBUG("check if file is exists in %s", fl.c_str());
        if (!argregex(fl.substr(fl.find_last_of(".") + 1), "^csv$"))
        {
            Logger::error(
                "aplikasi hanya dapat menerima file berextensi .csv!");
            return false;
        }
        else if (!fs::exists(fl))
        {
            Logger::error("tidak ada file pada %s!", fl.c_str());
            return false;
        }
        return true;
    }

    void printBanner()
    {
        for (const auto &line : Gacha::Banner_src)
        {
            string c = Color::hextostr(line[0]);
            cout << c << line[1] << endl;
        }
        cout << Fx::reset_base << endl;
    }

}  // namespace Gacha

namespace Logger
{
    string tdf   = "%Y/%m/%d (%T) | ";
    int loglevel = Warning;
    array<std::pair<int, string>, 4> modes;

    void setmode(const LogMode &mode)
    {
        array<int, 3> _m    = {Info, Warning, Error};
        array<string, 3> _s = {
            Color::fg_green + "[INFO] :", Color::fg_red + "[WARNING] :",
            Color::fg_red + "[ERROR] :"};
        for (int i = 0; i < 3; ++i)
            modes[i] = {_m[i], _s[i]};
        loglevel = mode;
    }

    void Debug(const char *msg, ...)
    {
        if (loglevel)
            return;
        char buf[1024];
        va_list args;
        va_start(args, msg);
        vsnprintf(buf, ARRSIZE(buf), msg, args);
        buf[ARRSIZE(buf) - 1] = 0;
        va_end(args);

        printf("%s %s\n", modes[Info].second.c_str(), buf);
    }

    void error(const char *_s, ...)
    {
        if (!(loglevel <= Error))
            return;
        char buf[1024];
        va_list args;
        va_start(args, _s);
        vsnprintf(buf, ARRSIZE(buf), _s, args);
        buf[ARRSIZE(buf) - 1] = 0;
        va_end(args);

        fprintf(stderr, "%s %s\n", modes[Error].second.c_str(), buf);
    }
}  // namespace Logger

namespace Color
{
    const string bg_black = "\x1b[0;40m";
    const string fg_white = "\x1b[1;97m";
    const string fg_green = "\x1b[1;92m";
    const string fg_red   = "\x1b[0;91m";
}  // namespace Color

namespace Fx
{
    const string e          = "\x1b[";
    const string b          = e + "1m";
    const string ub         = e + "22m";
    const string d          = e + "2m";
    const string ud         = e + "22m";
    const string i          = e + "3m";
    const string ui         = e + "23m";
    const string ul         = e + "4m";
    const string uul        = e + "24m";
    const string bl         = e + "5m";
    const string ubl        = e + "25m";
    const string s          = e + "9m";
    const string us         = e + "29m";

    const string reset_base = e + "0m";
    const string reset;
    const std::regex escape_regex(
        "\033\\[\\d+;?\\d?;?\\d*;?\\d*;?\\d*(m|f|s|u|C|D|A|B){1}");
    const std::regex color_regex("\033\\[\\d+;?\\d?;?\\d*;?\\d*;?\\d*(m){1}");
    string uncolor(const string &s)
    {
        return std::regex_replace(s, color_regex, "");
    }
}  // namespace Fx
