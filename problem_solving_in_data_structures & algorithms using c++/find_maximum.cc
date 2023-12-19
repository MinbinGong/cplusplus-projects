#include <algorithm>
#include <vector>

int get_max(std::vector<int> &data) {
    int size = data.size();
    int max = data[0], count = 1, max_count = 1;
    for (int i = 0; i < size; i++) {
        count = 1;
        for (int j = i + 1; j < size; j++) {
            if (data[i] == data[j]) {
                count++;
            }
        }

        if (count > max_count) {
            max = data[i];
            max_count = count;
        }
    }

    return max;
}

int get_max2(std::vector<int> &data) {
    int size = data.size();
    int max = data[0], max_cnt = 1;
    int curr = data[0], curr_cnt = 1;

    std::sort(data.begin(), data.end());

    for (int i = 1; i < size; i++) {
        if (data[i] == data[i - 1]) {
            curr_cnt++;
        } else {
            curr_cnt = 1;
            curr = data[i];
        }

        if (curr_cnt > max_cnt) {
            max_cnt = curr_cnt;
            max = curr;
        }
    }
    return max;
}

int get_max3(std::vector<int> &data, int range) {
    int max = data[0], max_cnt = 1;
    int size = data.size();
    std::vector<int> count(range);
    for (int i = 0; i < size; i++) {
        count[data[i]]++;
        if (count[data[i]] > max_cnt) {
            max_cnt = count[data[i]];
            max = data[i];
        }
    }
    return max;
}