//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#include "FileDecomposer.h"

#include <fstream>

namespace {
    static const char* BLOCKS_DIRECTORY = "blocks";
    static const char* FILETYPE = ".bin";

    void dumpBuffer(char* buffer, const int count, const int part)
    {
        const auto filename = blockFilename(part);
        std::ofstream fout(filename, std::ios::out | std::ios::binary);
        fout.write(buffer, count * sizeof(char));
        fout.close();
    }
}

std::string blockFilename(const int number)
{
    return BLOCKS_DIRECTORY +
           std::string("/block_") +
           std::to_string(number) +
           FILETYPE;
}

FileDecomposer::FileDecomposer()
{}

FileDecomposer::~FileDecomposer() {
    std::filesystem::remove_all(BLOCKS_DIRECTORY);
}

int FileDecomposer::decompose(const std::string& filepath)
{
    std::filesystem::create_directory(BLOCKS_DIRECTORY);

    char c;
    std::ifstream inputFile(filepath);

    int currentPart = 0;
    char* buffer = new char[BLOCK_SIZE];

    while (inputFile) {
        inputFile.read(buffer, BLOCK_SIZE);

        auto count = inputFile.gcount();

        if (!count) {
            break;
        }

        dumpBuffer(buffer, count - currentPart * BLOCK_SIZE, currentPart);
        currentPart++;
    }

    return currentPart;
}