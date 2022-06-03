#pragma once

#include "std_libs.hpp"
#define _GACHA_DEBUG_ 1
#define ARRSIZE(ARR)  ((int)(sizeof(ARR) / sizeof(*(ARR))))
#define FMTARGS(FMT)  __attribute__((format(printf, FMT, FMT + 1)))

#define DEBUG(fmt, ...)                                           \
    do                                                            \
    {                                                             \
        if (_GACHA_DEBUG_)                                        \
            Logger::Debug(                                        \
                "%s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, \
                __VA_ARGS__);                                     \
    } while (0)

#define HEADER_TABLE                   \
    {                                  \
        "ID", "NAMA", "NIM", "KELAMIN" \
    }
#define HEADER_TABLE_RANDOM             \
    {                                   \
        "ID", "NAMA", "NIM", "KELOMPOK" \
    }

using std::array;
using std::string;
using std::to_string;
using std::vector;
namespace fs = std::filesystem;
namespace Gacha
{
    static const fs::path self_path;
    extern bool isInteractive;
    static const vector<array<string, 2>> Banner_src = {
        {"#e62525",
         "   ██████╗  █████╗  ██████╗██╗  ██╗ █████╗     ██╗████████╗██╗    "            },
        {"#cd2121",
         "  ██╔════╝ ██╔══██╗██╔════╝██║  ██║██╔══██╗    ██║╚══██╔══╝██║    "},
        {"#b31d1d",
         "  ██║  ███╗███████║██║     ███████║███████║    ██║   ██║   ██║    "                    },
        {"#9a1919",
         "  ██║   ██║██╔══██║██║     ██╔══██║██╔══██║    ██║   ██║   ╚═╝    "                      },
        {"#801414",
         "  ╚██████╔╝██║  ██║╚██████╗██║  ██║██║  ██║    ██║   ██║   ██╗    "                  },
        {"#000000",
         "   ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝   ╚═╝   ╚═╝    "                        }
    };

    struct Mahasiswa
    {
        Mahasiswa() { id = 0; };
        /* Mahasiswa(Mahasiswa &m)                               { id = m.id;
         * nama = m.nama; nim  = m.nim; klmn = m.klmn; }; */
        Mahasiswa(int _id, string _nm, string _ni, string _k)
        {
            id   = _id;
            nama = _nm;
            nim  = _ni;
            klmn = _k;
        };
        int id;
        string nama;
        string nim;
        string klmn;

        vector<string> getdata() { return {to_string(id), nama, nim, klmn}; };
    };

    class GachaCsv
    {
       public:
        GachaCsv(fs::path &_file)
            : m_infile(_file), m_outfile("out_gacha.csv"){};
        GachaCsv(fs::path &_file, fs::path &_ofile)
            : m_infile(_file), m_outfile(_ofile){};
        ~GachaCsv();
        void read();
        void write(vector<Mahasiswa> &data);

       private:
        fs::path m_infile;
        fs::path m_outfile;
    };

    enum By_
    {
        By_ID,
        By_NAME,
        By_NIM,
        By_KLMN
    };
    class Data
    {
       public:
        Data();
        ~Data();
        template <typename _s_i>
        Mahasiswa &getDataBy(const By_ by, _s_i indicator);
        void getAllData(vector<vector<string>> &_data);
        void refreshData(vector<vector<string>> &_data);
        void getRandomData(vector<vector<string>> &data);
        void addData(Mahasiswa &m);
        void editData(Mahasiswa &m);
        void delDataBy(int idx);
        void RandomData();

       private:
        template <typename _s_i>
        Mahasiswa m_getdata(_s_i indx);
        vector<Mahasiswa> m_mhsw;
    };
};  // namespace Gacha
