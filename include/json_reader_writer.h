#pragma once
#include <include/nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

class JsonReaderWriter
{
public:
    JsonReaderWriter(const std::string &filename)
    {
        std::fstream file(filename, std::ios::in | std::ios::out | std::ios::app); // Eğer dosya bulunamaz
        // ise oluşturur.
        if (!file.is_open())
        {
            json ex1 = {
                {"pi", 3.141},
                {"happy", true},
                {"name", "Niels"},
                {"nothing", nullptr},
                {"answer", {{"everything", 42}}},
                {"list", {1, 0, 2}},
                {"object", {{"currency", "USD"}, {"value", 42.99}}}};
            std::cout << "Dosya basari ile acildi!" << std::endl;
            // Okuma veya yazma işlemleri yapılabilir..
            file << ex1.dump(4);
            file.close();
        }
        else
        {
            std::cout << "Dosya zaten olusturulmus!" << std::endl;
        }
    }

    json read(const std::string &filename) const
    {
        try
        {
            std::fstream file(filename);
            if (!file)
            {
                std::cout << "Dosya acilamadi!";
                return nullptr;
            }
            json jdata;
            file >> jdata;
            file.close();
            return jdata;
            // file >> jdata;
        }
        catch (json::exception &e)
        {
            std::cout << "Json dosyasi okunurken bir hata meydana geldi!";
            return nullptr;
        }
    }

    bool write(const std::string &filename, json data)
    {
        std::ofstream file(filename);
        if (!file)
        {
            return false;
        }

        try
        {
            json jdata(data);
            file << jdata.dump(4);
        }
        catch (json::exception &e)
        {
            return false;
        }

        return true;
    }
};