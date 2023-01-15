/*
 * Leetcode 33, Search in Rotated Sorted Array
 * Approach
 * 1. To Find Peak Element in rotated array
 *      We can return the mid, if we found the peak in the mid i.e nums[mid-1]<nums[mid]>nums[mid+1]
 *      else we'll check if the peak can be found in right subarray or left subarray.
 *      If the left subarray is unsorted that means peak is in the left subarray i.e if nums[low]>nums[mid]
 *      else the peak is in the right subarray.
 * 2. To find the target after peak (k)
        Once the peak is found i.e k then we can easily search for elements with updated mid index as
        (mid+k+1)%n , where k is the peak or point from where array is rotated.
 */

#include <vector>

int peek(std::vector<int> &nums)
{
    unsigned int low{0}, high{nums.size() - 1};
    while (low <= high)
    {
        unsigned int mid = (low + high) >> 1;
        if ((mid == 0 || nums[mid] > nums[mid - 1]) && (mid == n - 1 || nums[mid] > nums[mid + 1]))
        {
            return mid;
        }

        if (nums[low] > nums[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
        
    }
    return -1;
}

int search(std::vector<int> &nums, int target)
{
    int ret{-1};
    int low{0}, high{nums.size() - 1};

    int k = peek(nums);
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        int z = (mid + k + 1) % n;
        if (nums[z] == target)
        {
            ret = z;
            break;
        }

        if (nums[z] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return ret;
}