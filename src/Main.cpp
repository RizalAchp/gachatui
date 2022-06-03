#include "Gacha.hpp"
#include "cli.hpp"
#include "gachaui.hpp"

int ArgsParse(int jmlarg, char **arguments);

int main(int argc, char **argv)
{
    int sig = ArgsParse(argc, argv);
    if (Gacha::isInteractive)
    {
        ftxui::MainInteractiveLoop();
    }
    return sig;
}

int ArgsParse(int jmlarg, char **arguments)
{
    DEBUG("Get jmlarg : %d", jmlarg);
    if (jmlarg == 1)
    {
        Gacha::isInteractive = true;
        return 0;
    }

    string arg = arguments[1];
    DEBUG("Get arguments : %s", arg.c_str());
    if (argregex(arg, "^-h.*", "^.*help.*"))
        return showHelp();

    else if (argregex(arg, "^-v.*$", "^.*ver.*"))
    {
        std::cout << "\nGacha: Currently on Version : " << project_version
                  << "\n"
                  << "by: Rizal Achmad Pahlevi\n";
        return 0;
    }
    else if (argregex(arg, "^-t.*", "^.*tu.*"))
    {
        Gacha::isInteractive = true;
        return 0;
    }
    //
    else if (argregex(arg, "^-i.*", "^.*in.*"))
    {
        if (jmlarg != 3)
        {
            Logger::error(
                "expect 2 arguments : {inputfile} after arguments %s",
                arg.c_str());
            return 1;
        }
        const string _f = arguments[jmlarg - 1];
        if (!Gacha::isFileExist(_f))
        {
            Logger::error(
                "File %s Not Found! for arguments : %s", _f.c_str(),
                arg.c_str());
            return 1;
        }
    }

    else if (argregex(arg, "^-o.*", "^.*out.*"))
    {
        if (jmlarg != 3)
        {
            Logger::error(
                "expect 2 arguments : {outfile} after arguments %s",
                arg.c_str());
            return 1;
        }
        const string _f = arguments[jmlarg - 1];
        if (!Gacha::isFileExist(_f))
        {
            Logger::error(
                "File %s Not Found! for arguments : %s", _f.c_str(),
                arg.c_str());
            return 1;
        }
    }

    else if (argregex(arg, "^-d.*", "^.*deb.*"))
        Logger::setmode(Logger::Info);

    Logger::error(
        "Argument Salah! Tidak ada Arguments untuk : %s\n", arg.c_str());
    return 1;
}
