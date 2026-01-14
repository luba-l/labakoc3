cmake_minimum_required(VERSION 3.10)

project(parallel_text_processing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Указываем все исходники
add_executable(parallel_text_processing
    src/main.cpp
    src/Record.hpp
    src/BlockingQueue.hpp
    src/Producer.hpp
    src/Consumer.hpp
    src/Writer.hpp
)

# Пути для заголовочных файлов
target_include_directories(parallel_text_processing
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)
