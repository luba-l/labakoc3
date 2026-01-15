#pragma once
#include "BlockingQueue.hpp"
#include "Record.hpp"

#include <fstream>
#include <sstream>

class Producer {
public:
    static void run(const std::string& filename,
                    BlockingQueue<Record>& queue) {

        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Record r;

            std::getline(ss, r.surname, ';');
            std::getline(ss, r.name, ';');
            std::getline(ss, r.patronymic, ';');
            std::getline(ss, r.phone, ';');

            queue.push(r);
        }
    }
};