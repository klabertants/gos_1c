//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#include <fstream>
#include <filesystem>

#include "Finder.h"

namespace {
    static const char* ARRAYS_DIRECTORY = "arrays";
    static const char* FILETYPE = ".bin";

    std::string arrayFilename(const int number) {
        return ARRAYS_DIRECTORY +
               std::string("/suff_array_") +
               std::to_string(number) +
               FILETYPE;
    }
}

Finder::Finder() {
    std::filesystem::create_directory(ARRAYS_DIRECTORY);
    blocksCount_ = 0;
    decomposer_ = std::make_unique<FileDecomposer>();
}

Finder::~Finder() {
    std::filesystem::remove_all(ARRAYS_DIRECTORY);
}

void Finder::preprocess(const std::string &filepath) {
    blocksCount_ = decomposer_->decompose(filepath);

    for (int i = 0; i < blocksCount_; i++) {
        std::ifstream inputFile(blockFilename(i));

        std::string tempText((std::istreambuf_iterator<char>(inputFile)),
                             std::istreambuf_iterator<char>());

        auto suffArray = std::make_unique<SuffixArray>(false, tempText);

        suffArray->dump(arrayFilename(i));
        suffArray.reset();

        inputFile.close();
    }
}

int Finder::findFirstEntry(const std::string &pattern) {
    for (int currentBlock = 0; currentBlock < blocksCount_; currentBlock++) {
        auto suffArray = getSuffixArray(currentBlock);

        const auto index = suffArray->findFirstEntry(pattern);

        if (index != SuffixArray::NOT_FOUND) {
            return currentBlock * BLOCK_SIZE + index;
        }

        suffArray.reset();
    }

    return Finder::NOT_FOUND;
}

std::shared_ptr<SuffixArray> Finder::getSuffixArray(const int index)
{
    return std::make_shared<SuffixArray>(true, arrayFilename(index));
}