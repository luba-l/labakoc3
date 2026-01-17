#pragma once
#include "BlockingQueue.hpp"
#include "Record.hpp"
#include <map>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

class Writer {
public:
    static void run(BlockingQueue<Record>& outputQueue) {

        std::map<std::string, std::vector<Record>> grouped;
        Record r;

        while (outputQueue.pop(r)) {
            if (r.surname.size() >= 2) {
                std::string key = r.surname.substr(0, 2);
                grouped[key].push_back(r);
            }
        }

        std::filesystem::create_directories("output");

        for (const auto& [letter, records] : grouped) {
            std::ofstream out("output/" + letter + ".txt");

            for (const auto& rec : records) {
                out << rec.surname << ";"
                    << rec.name << ";"
                    << rec.patronymic << ";"
                    << rec.phone << "\n";
            }
        }

        std::cout << "Запись файлов завершена\n";
    }
};
