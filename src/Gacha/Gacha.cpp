#include "Gacha.hpp"

#include <algorithm>
#include <random>

namespace Gacha
{

    bool isInteractive = false;
    template <typename _s_i>
    Mahasiswa &Data::getDataBy(const By_ by, _s_i indicator)
    {
        switch ((int)by)
        {
            case By_ID:
                return m_getdata(indicator);
            case By_NAME:
                return m_getdata(indicator);
            case By_NIM:
                return m_getdata(indicator);
            case By_KLMN:
                return m_getdata(indicator);
        }
    }

    Data::Data() {}

    Data::~Data() { m_mhsw.clear(); }

    void Data::refreshData(vector<vector<string>> &_data)
    {
        if (!_data.empty())
            _data.erase(_data.begin(), _data.end());
        return;
    }
    void Data::getAllData(vector<vector<string>> &_data)
    {
        if ((_data.empty()) & (!m_mhsw.empty()))
        {
            _data.push_back(HEADER_TABLE);
            for (Mahasiswa &m : m_mhsw)
                _data.push_back(m.getdata());
            return;
        }
        else if (m_mhsw.empty())
        {
            _data = {
                HEADER_TABLE,
                {"data kosong", "tambahkan data pada menu tambah", "pada",
                  "file csv data"}
            };
            return;
        }
        return;
    }

    void Data::addData(Mahasiswa &m)
    {
        m_mhsw.push_back(m);
        return;
    }

    void Data::editData(Mahasiswa &m)
    {
        for (Mahasiswa &_m : m_mhsw)
            if (_m.id == m.id)
                _m = Mahasiswa(m);
        return;
    }

    void Data::delDataBy(int idx)
    {
        m_mhsw.erase(m_mhsw.begin() + idx);
        return;
    }
    void Data::RandomData()
    {
        std::random_device rd;
        std::mt19937 g(rd());
        return std::shuffle(m_mhsw.begin(), m_mhsw.end(), g);
    }

    void Data::getRandomData(vector<vector<string>> &data)
    {
        if ((data.empty()) && (!m_mhsw.empty()))
        {
            data.push_back(HEADER_TABLE_RANDOM);
            for (Mahasiswa &m : m_mhsw)
                data.push_back(m.getdata());
            return;
        }
        else if (m_mhsw.empty())
        {
            data = {
                HEADER_TABLE_RANDOM,
                {"data random kosong", "random pada menu random", "pada",
                  "file csv data"}
            };
            return;
        }
        return;
    }
}  // namespace Gacha
