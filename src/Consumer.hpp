#pragma once

#include "BlockingQueue.hpp"
#include "Record.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>

inline std::mutex coutMutex; // для синхронизации вывода в консоль

class Consumer {
public:
    static void run(BlockingQueue<Record>& inputQueue,
                    BlockingQueue<Record>& outputQueue,
                    int id) {

        Record r;

        while (inputQueue.pop(r)) {

            // Проверка записи
            if (!r.isValid()) {
                {
                    std::ostringstream oss;
                    oss << "[Consumer " << id
                        << "] Пропущена некорректная запись: "
                        << r.surname << ";"
                        << r.name << ";"
                        << r.patronymic << ";"
                        << r.phone << "\n";

                    std::lock_guard<std::mutex> lock(coutMutex);
                    std::cout << oss.str();
                }
                continue; // пропускаем запись
            }

            // Обработка
            {
                std::ostringstream oss;
                oss << "[Consumer " << id
                    << "] Обработка: " << r.surname << "\n";

                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << oss.str();
            }

            // Симуляция обработки
            std::this_thread::sleep_for(std::chrono::seconds(2));

            // Кладём только валидные записи в очередь для Writer
            outputQueue.push(r);

            {
                std::ostringstream oss;
                oss << "[Consumer " << id
                    << "] Готово: " << r.surname << "\n";

                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << oss.str();
            }
        }
    }
};
