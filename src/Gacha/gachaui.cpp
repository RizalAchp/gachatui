#include "gachaui.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

namespace ftxui
{

    Element TableSiswa();
    Element WindowUtama();
    Element TableGacha();
    Element RandomWindow();
    Element SettingWindow();
    Element Banners();

    const vector<string> entries = {"MainMenu", "GachaData", "SettingData"};
    static int shift             = 0;
    void MainInteractiveLoop()
    {
        ScreenInteractive screen = ScreenInteractive::Fullscreen();
        static int mainx         = Terminal::Size().dimx / 2;
        static int tab_index     = 0;
        Component main_group     = ResizableSplitLeft(
                Renderer(TableSiswa), Renderer(WindowUtama), &mainx);

        Component main =
            Renderer(main_group, [&] { return main_group->Render(); }) |
            borderLight | color(Color::CyanLight);

        Component random  = Renderer(RandomWindow);
        Component setting = Renderer(SettingWindow);
        Component selects =
            Menu(&entries, &tab_index, MenuOption::HorizontalAnimated());
        Component contents =
            Container::Tab({main, random, setting}, &tab_index);

        Component renderers = Renderer(
            Container::Vertical({
                selects,
                contents,
            }),
            [&]
            {
                return vbox({
                    Banners() | hcenter,
                    selects->Render(),
                    contents->Render() | flex,
                });
            });

        std::thread refresh_ui(
            [&]
            {
                while (Gacha::isInteractive)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(0.05s);
                    shift++;
                    screen.PostEvent(Event::Custom);
                }
            });

        renderers = CatchEvent(
            renderers,
            [&](Event event)
            {
                if (event == Event::Character('q') || event == Event::Escape)
                {
                    screen.ExitLoopClosure()();
                    return true;
                }
                return false;
            });
        screen.Loop(renderers);
        Gacha::isInteractive = false;
        refresh_ui.join();
    }

    Element WindowUtama()
    {
        auto box = vbox(
            text("Selamat Datang Di Aplikasi Gacha!") | bold |
                color(Color::Red) | borderLight | size(WIDTH, EQUAL, 18),
            text("by Rizal Achmad Pahlevi!") | bold | color(Color::Red) |
                borderLight | size(WIDTH, EQUAL, 12),
            hbox(filler(), text("")));
        return box;
    };

    Element RandomWindow()
    {
        return paragraph("ini window random") | center | borderLight |
               color(Color::GreenYellow);
    };
    Element SettingWindow()
    {
        return paragraph("ini window setting") | center | borderLight |
               color(Color::GreenLight);
    };

    Element TableSiswa()
    {
        Gacha::Data data;
        static vector<vector<string>> _data;
        data.getAllData(_data);
        Table table = Table(_data);
        table.SelectAll().Border(ROUNDED);
        table.SelectAll().DecorateCells(center);
        table.SelectAll().SeparatorVertical(LIGHT);
        table.SelectColumn(0).Border(LIGHT);
        table.SelectRow(0).Decorate(bold);
        table.SelectRow(0).Border(DOUBLE);
        table.SelectCell(0, 0).DecorateCells(bgcolor(Color::DarkBlue));
        table.SelectCell(0, 0).DecorateCells(color(Color::White));
        return table.Render();
    };
    Element TableGacha()
    {
        Gacha::Data data;
        static vector<vector<string>> _data;
        data.getRandomData(_data);
        Table table = Table(_data);
        table.SelectAll().Border(ROUNDED);
        table.SelectAll().DecorateCells(center);
        table.SelectColumn(0).Border(LIGHT);
        table.SelectRow(0).Decorate(bold);
        table.SelectRow(0).SeparatorVertical(LIGHT);
        table.SelectRow(0).Border(DOUBLE);
        return table.Render();
    };

    Element Banners()
    {
        int r, g, b;
        auto c = Canvas(Terminal::Size().dimx, Terminal::Size().dimy * 0.80);
        int i  = 0;
        for (array<string, 2> str : Gacha::Banner_src)
        {
            sscanf(str[0].c_str(), "#%02x%02x%02x", &r, &g, &b);
            c.DrawText(0, 4 * i, str[1], Color::RGB(r, g, b));
            i++;
        }
        Element banner = canvas(std::move(c));

        /* Element doc = vbanner, filler()); */
        return banner;
    };
}  // namespace ftxui
