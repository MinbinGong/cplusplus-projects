/*
    Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any
    order.



    Example 1:

    Input: nums = [1,1,2]
    Output:
    [[1,1,2],
    [1,2,1],
    [2,1,1]]
    Example 2:

    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


    Constraints:

    1 <= nums.length <= 8
    -10 <= nums[i] <= 10
 */

/*

    Time Complexity : O(N!*KlogK), In worst case when all element of Array(nums) will different then there will
    be N! permutations and N! function calls and for every permutation we have to check in Hash Table(set) for
    inserting which take O(KlogK) time .Where N is the size of the array(nums) and ! stands for factorial. K is
    the worst case size of Array(output).

    Space Complexity: O(N!*N), In worst case when all element of Array(nums) will different, since we have to
    store all the possible solutions which are N! in size where N is the size of the array and ! stands for
    factorial.

    Solved using Array + BackTracking + Hash Table(set).

*/
