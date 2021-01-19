//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#ifndef INC_1C_GOS_FINDER_H
#define INC_1C_GOS_FINDER_H

#include <string>
#include <memory>

#include "FileDecomposer.h"
#include "SuffixArray.h"

class Finder {
public:
    Finder();
    ~Finder();

    void preprocess(const std::string& filepath);

    int findFirstEntry(const std::string& pattern);

    static const int NOT_FOUND = -1;
private:
    int blocksCount_;
    std::unique_ptr<FileDecomposer> decomposer_;

    std::shared_ptr<SuffixArray> getSuffixArray(const int index);
};

#endif //INC_1C_GOS_FINDER_H
