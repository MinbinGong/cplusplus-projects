#include <vector>

bool binary_search(std::vector<int> &data, int value) {
    int size = data.size();
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (data[mid] == value) {
            return true;
        } else if (data[mid] < value) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

bool binary_search_recursive(std::vector<int> &data, int low, int high, int value) {
    if (low > high) {
        return false;
    }

    int mid = low + (high - low) / 2;
    if (data[mid] == value) {
        return true;
    } else if (data[mid] < value) {
        return binary_search_recursive(data, mid + 1, high, value);
    } else {
        return binary_search_recursive(data, low, mid - 1, value);
    }
}