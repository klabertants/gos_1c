//
// Created by Dmitry Tkachenko on 19.01.2021.
//

#include "SuffixArray.h"

#include <algorithm>
#include <fstream>

namespace {
    struct suffix {
        int index;
        int rank[2];
    };

    bool comparator(struct suffix a, struct suffix b) {
        return (a.rank[0] == b.rank[0])
        ? (a.rank[1] < b.rank[1] ? true : false)
        : (a.rank[0] < b.rank[0] ? true : false);
    }

    std::string getTarget(const bool fromFile, const std::string& target)
    {
        if (!fromFile) {
            return target;
        }

        std::ifstream inputFile(target);

        std::string tmp;
        getline(inputFile, tmp);
        return tmp;
    }

    std::vector<int> getSuffArr(const bool fromFile, const std::string& target)
    {
        if (!fromFile) {
            return {};
        }

        std::ifstream inputFile(target);

        std::string tmp;
        getline(inputFile, tmp);

        int count;
        inputFile >> count;
        std::vector<int> sArr;
        sArr.assign(count, 0);
        for (int i = 0; i < count; i++) {
            inputFile >> sArr[i];
        }

        inputFile.close();

        return sArr;
    }
}

SuffixArray::SuffixArray(const bool fromFile, const std::string &target) :
    text_(getTarget(fromFile, target)),
    suffArray_(getSuffArr(fromFile, target))
{
    if (fromFile) {
        return;
    }

    const int n = target.size();
    std::vector<suffix> suffixes;
    suffixes.assign(n, suffix());

    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = target[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)
                ? (target[i + 1] - 'a')
                : -1;
    }

    std::sort(suffixes.begin(), suffixes.end(), comparator);

    int ind[n];
    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i-1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)
                                  ? suffixes[ind[nextindex]].rank[0]
                                  : -1;
        }

        std::sort(suffixes.begin(), suffixes.end(), comparator);
    }

    for (int i = 0; i < n; i++) {
        suffArray_.push_back(suffixes[i].index);
    }
}

void SuffixArray::dump(const std::string &filename)
{
    FILE* outputFile = fopen(filename.c_str(), "w");

    fprintf(outputFile, "%s\n", text_.c_str());
    fprintf(outputFile, "%d\n", suffArray_.size());
    for (const auto& val: suffArray_) {
        fprintf(outputFile, "%d\n", val);
    }

    fclose(outputFile);
}

int SuffixArray::findFirstEntry(const std::string &pattern)
{
    int left = 0;
    int right = suffArray_.size();

    int mid = 0;
    while (true) {
        mid = (left + right) / 2;

        std::string current;
        for (int i = suffArray_[mid]; i < text_.size() && current.size() < pattern.size(); i++) {
            current += text_[i];
        }

        if (pattern < current) {
            right = mid - 1;
        } else if (pattern > current) {
            left = mid + 1;
        } else {
            return suffArray_[mid];
        }

        if (left > right) {
            return SuffixArray::NOT_FOUND;
        }
    }
}
