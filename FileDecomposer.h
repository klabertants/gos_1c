//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#ifndef INC_1C_GOS_FILEDECOMPOSER_H
#define INC_1C_GOS_FILEDECOMPOSER_H

#include <string>

static const int BLOCK_SIZE = (1 << 20) / sizeof(char);

std::string blockFilename(const int number);

class FileDecomposer {
public:
    FileDecomposer();
    ~FileDecomposer();
    int decompose(const std::string& filepath);
};

#endif //INC_1C_GOS_FILEDECOMPOSER_H
