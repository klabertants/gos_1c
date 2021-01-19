//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#ifndef GOS_SUFFIXARRAY_H
#define GOS_SUFFIXARRAY_H

#include <vector>
#include <string>

class SuffixArray {
public:
    SuffixArray(const bool fromFile, const std::string& target);

    int findFirstEntry(const std::string& pattern);

    void dump(const std::string& filename);

    static const int NOT_FOUND = -1;

private:
    std::string text_;
    std::vector<int> suffArray_;
};

#endif //GOS_SUFFIXARRAY_H
