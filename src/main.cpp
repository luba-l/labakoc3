#include <thread>
#include <vector>
#include <iostream>

#include "BlockingQueue.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "Writer.hpp"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Использование:\n"
                  << argv[0] << " <входной_файл>\n";
        return 1;
    }

    std::string inputFile = argv[1];

    // Создаём очереди
    BlockingQueue<Record> inputQueue;
    BlockingQueue<Record> outputQueue;

    // Запускаем производителя
    std::thread producer(
        Producer::run,
        inputFile,
        std::ref(inputQueue)
    );

    const int CONSUMER_COUNT = 3;
    std::vector<std::thread> consumers;

    // Запускаем потребителей
    for (int i = 0; i < CONSUMER_COUNT; ++i) {
        consumers.emplace_back(
            Consumer::run,
            std::ref(inputQueue),
            std::ref(outputQueue),
            i + 1
        );
    }

    // Запускаем writer
    std::thread writer(
        Writer::run,
        std::ref(outputQueue)
    );

    // Ждём завершения всех потоков
    producer.join();
    for (auto& c : consumers)
        c.join();

    outputQueue.finish();
    writer.join();

    std::cout << "Обработка данных завершена.\n";
    return 0;
}
