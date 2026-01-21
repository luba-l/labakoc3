#pragma once
#include <string>
#include <cctype>

struct Record {
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string phone;

    // Проверка, что строка состоит только из русских букв, пробелов или дефисов
    static bool isCyrillic(const std::string& s) {
       if (s.empty()) return false;

        for (unsigned char c : s) {
        // запрещаем цифры
            if (std::isdigit(c))
                return false;

        // запрещаем латиницу
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                return false;

        // разрешаем пробел и дефис
            if (c == ' ' || c == '-')
                continue;
        }
        return true;
    }


    // Проверка телефона
    static bool isPhoneValid(const std::string& s) {
        if (s.empty()) return false;

        if (s[0] == '+') {
            // должен быть +7xxxxxxxxxx, длина 12 символов
            if (s.size() != 12) return false;
            if (s[1] != '7') return false;
            for (size_t i = 2; i < s.size(); ++i) {
                if (!std::isdigit(static_cast<unsigned char>(s[i])))
                    return false;
            }
            return true;
        } else {
            // простой вариант без плюса c 8 в начале: 11 цифр
            if (s.size() != 11) return false;
            for (char c : s) {
                if (!std::isdigit(static_cast<unsigned char>(c)))
                    return false;
            }
            return true;
        }
    }

    // Метод проверки корректности записи
    bool isValid() const {
        if (!isCyrillic(surname)) return false;
        if (!isCyrillic(name)) return false;
        if (!isCyrillic(patronymic)) return false;

        if (!isPhoneValid(phone)) return false;

        return true;
    }
};