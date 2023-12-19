#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

void print_repeating(std::vector<int> &data) {
    int size = data.size();
    std::cout << " Repeating elements are";
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (data[i] == data[j]) {
                std::cout << " " << data[i];
            }
        }
    }
}

void print_repeating2(std::vector<int> &data) {
    int size = data.size();
    std::sort(data.begin(), data.end());

    std::cout << " Repeating elements are:";
    for (int i = 0; i < size; i++) {
        if (data[i] == data[i - 1]) {
            std::cout << " " << data[i];
        }
    }
}

void print_repeating3(std::vector<int> &data) {
    int size = data.size();
    std::unordered_set<int> hs;
    std::cout << "Repeating elements are : ";
    for (int i = 0; i < size; i++) {
        if (std::find(hs.begin(), hs.end(), data[i]) != hs.end()) {
            std::cout << " " << data[i];
        } else {
            hs.insert(data[i]);
        }
    }
}

void print_repeating4(std::vector<int> &data) {
    int size = data.size();
    std::vector<int> count(size);
    for (int i = 0; i < size; i++) {
        count[i] = 0;
    }
    std::cout << " Repeating elements are : ";
    for (int i = 0; i < size; i++) {
        if (count[i] == 1) {
            std::cout << " " << data[i];
        } else {
            count[data[i]]++;
        }
    }
}