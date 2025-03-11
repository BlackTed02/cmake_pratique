#pragma once
#include <iostream>
#include <map>
#include <optional>
#include <vector>

std::map<std::string, std::vector<int>> studentScores = {
    {"Alice", {95, 87, 92}},
    {"Bob", {85, 90, 78}},
    {"Charlie", {100, 93, 97}}
};

std::optional<std::vector<int>> findStudentScores(const std::string& name) {
    auto it = studentScores.find(name);
    
    if (it != studentScores.end())
    {
        return std::make_optional<std::vector<int>>(it->second);
    }
    else
    {
        return std::nullopt;
    }
}

void printStudentScores(const std::string& name) {
    auto scoresOpt = findStudentScores(name);

    if (scoresOpt) {
        std::cout << name << "'s scores: ";
        for (int score : *scoresOpt) {
            std::cout << score << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No student named " << name << " found." << std::endl;
    }
}
