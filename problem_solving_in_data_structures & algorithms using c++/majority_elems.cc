#include <algorithm>
#include <exception>
#include <vector>

int get_majority(std::vector<int> &data) {
    int size = data.size();
    int max = 0, count = 0, max_cnt = 0;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (data[i] == data[j]) {
                count++;
            }
        }
        if (count > max_cnt) {
            max = data[i];
            max_cnt = count;
        }
    }

    if (max_cnt > size / 2) {
        return max;
    } else {
        return -1;
    }
}

int get_majority2(std::vector<int> &data) {
    
}