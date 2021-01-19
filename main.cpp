#include <iostream>

#include "Finder.h"

int main() {
    const auto finder = std::make_unique<Finder>();

    std::string filename;
    std::cout << "Enter a filename: ";
    std::cin >> filename;

    finder->preprocess(filename);

    std::cout << "Enter queries:\n";

    std::string pattern;
    while (std::cin >> pattern) {
        std::cout << finder->findFirstEntry(pattern);
    }

    return 0;
}
