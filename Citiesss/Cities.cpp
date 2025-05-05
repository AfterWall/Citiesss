#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <cctype>

class CityGame {
private:
    std::unordered_set<std::string> allCities = {
        "London", "Berlin", "Paris", "Rome", "Madrid", "Chicago", "Eindhoven", "Glasgow", "Helsinki", "Warsaw", "Omsk", "Engels", "������",//<-���������
        "Oslo", "Prague", "Vienna", "Dublin", "Athens", "Moscow", "Arkhangelsk", "Florence", "Volgograd", "Neapol", "Istanbul", "Shanghai", "Kyiv", "Kharkiv", "Kazan",
    };
    //� ���� �� ���������� ��������� ���������, �.� github � visual studio �� ���������� ������� �������,
    // � ��������� �� �� ����� ��� ������ �������� ' ', ���������� �������� ������ � ���������, � ������� �������� setlocale(LC_ALL, "ru"); �� ���� �� ���������
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
        std::cout << "���� � ������/ game called cities" << std::endl;
        std::cout << "������� �������� ������ ������� � ������� ��������� ����� ������� ������" << std::endl;
        std::cout << "�������� exit ����� ����� � ���������\n" << std::endl;

        while (true) {
            if (currentLetter == '\0')
                std::cout << "������� �����/ put city here: ";
            else
                std::cout << "������� ����� ������� � �����/ write down city that starts with letter '" << currentLetter << "': ";

            std::string input;
            std::getline(std::cin, input);

            if (input.empty())
                continue;

            if (input == "exit") {
                std::cout << "��������/ you lost" << std::endl;
                break;
            }

            processInput(input);
        }
    }

    void processInput(const std::string& city) {
        std::string normalizedCity = toLower(city);

        if (!isValidCity(normalizedCity)) {
            std::cout << "������� ������ �����/ put other city\n";
            return;
        }

        usedCities.insert(normalizedCity);
        currentLetter = getNextLetter(normalizedCity);
        std::cout << "�������, ������� ���������/ correct put another one: '" << currentLetter << "'\n\n";
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
            std::cout << "����� ������ ��� � ������ allcities/ incorrect city, its not in allcities\n";
            return false;
        }
        if (usedCities.find(city) != usedCities.end()) {
            std::cout << "����� �� ����� ���� �������� �����������/ city cant be used twice\n";
            return false;
        }
        if (currentLetter != '\0') {
            char firstChar = std::tolower(static_cast<unsigned char>(city[0]));
            if (firstChar != std::tolower(currentLetter)) {
                std::cout << "����� ������ ��������� �../ city should begin with letter '" << currentLetter << "'!\n";
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