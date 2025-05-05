#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <cctype>

class CityGame {
private:
    std::unordered_set<std::string> allCities = {
        "London", "Berlin", "Paris", "Rome", "Madrid", "Chicago", "Eindhoven", "Glasgow", "Helsinki", "Warsaw", "Omsk", "Engels", "ћосква",//<-нерабоча€
        "Oslo", "Prague", "Vienna", "Dublin", "Athens", "Moscow", "Arkhangelsk", "Florence", "Volgograd", "Neapol", "Istanbul", "Shanghai", "Kyiv", "Kharkiv", "Kazan",
    };
    //у мен€ не получилось поставить кириллицу, т.к github с visual studio не распознают русские символы,
    // в терминале он их видит как пустое значение ' ', попробуйте написать ћосква в терминале, € пыталс€ внедрить setlocale(LC_ALL, "ru"); но тоже не сработало
    std::unordered_set<std::string> usedCities;

    char currentLetter = '\0';

    std::string toLower(const std::string& str) const {
        std::string result;
        for (char ch : str)
            result += std::tolower(static_cast<unsigned char>(ch));
        return result;
    }

public:
    void start() {
        std::cout << "»гра в города/ game called cities" << std::endl;
        std::cout << "вводите название города начина€ с прошлой последней буквы прошого ответа" << std::endl;
        std::cout << "Ќапишите exit чтобы выйти с терминала\n" << std::endl;

        while (true) {
            if (currentLetter == '\0')
                std::cout << "¬водите город/ put city here: ";
            else
                std::cout << "¬ведите город начина€ с буквы/ write down city that starts with letter '" << currentLetter << "': ";

            std::string input;
            std::getline(std::cin, input);

            if (input.empty())
                continue;

            if (input == "exit") {
                std::cout << "проигрыш/ you lost" << std::endl;
                break;
            }

            processInput(input);
        }
    }

    void processInput(const std::string& city) {
        std::string normalizedCity = toLower(city);

        if (!isValidCity(normalizedCity)) {
            std::cout << "введите другой город/ put other city\n";
            return;
        }

        usedCities.insert(normalizedCity);
        currentLetter = getNextLetter(normalizedCity);
        std::cout << "ѕрин€то, введите следующий/ correct put another one: '" << currentLetter << "'\n\n";
    }

    bool isValidCity(const std::string& city) {
        bool exists = false;
        for (const auto& c : allCities) {
            if (toLower(c) == city) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            std::cout << "Ётого города нет в списке allcities/ incorrect city, its not in allcities\n";
            return false;
        }
        if (usedCities.find(city) != usedCities.end()) {
            std::cout << "√ород не может быть повторно использован/ city cant be used twice\n";
            return false;
        }
        if (currentLetter != '\0') {
            char firstChar = std::tolower(static_cast<unsigned char>(city[0]));
            if (firstChar != std::tolower(currentLetter)) {
                std::cout << "√ород должен начинатс€ с../ city should begin with letter '" << currentLetter << "'!\n";
                return false;
            }
        }

        return true;
    }

    char getNextLetter(const std::string& city) {
        char lastChar = city.back();
        return std::toupper(static_cast<unsigned char>(lastChar));
    }
};

int main() {
    CityGame game;
    game.start();
    return 0;
}