#pragma once
#include "BlockingQueue.hpp"
#include "Record.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

class Producer {
public:
    static void run(const std::string& filename,
                    BlockingQueue<Record>& inputQueue) {

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла\n";
            inputQueue.finish();
            return;
        }

        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            Record r;

            std::getline(ss, r.surname, ';');
            std::getline(ss, r.name, ';');
            std::getline(ss, r.patronymic, ';');
            std::getline(ss, r.phone, ';');

            inputQueue.push(r);
        }

        inputQueue.finish();
    }
};