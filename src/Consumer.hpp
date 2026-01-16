#pragma once
#include "BlockingQueue.hpp"
#include "Record.hpp"

#include <thread>
#include <chrono>
#include <iostream>

class Consumer {
public:
    static void run(BlockingQueue<Record>& queue, int id) {
        Record r;

        while (queue.pop(r)) {
            std::cout << "Поток " << id
                      << " обрабатывает "
                      << r.surname << std::endl;

            std::this_thread::sleep_for(
                std::chrono::seconds(2)
            );
        }
    }
};
