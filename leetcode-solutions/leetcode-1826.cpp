/*
 * 1826. Faulty Sensor
 * 
 * An experiment is being conducted in a lab. To ensure accuracy, there are two sensors collecting data simultaneously. You are given two arrays sensor1 and sensor2, where sensor1[i] and sensor2[i] are the ith data points collected by the two sensors.
 * 
 * However, this type of sensor has a chance of being defective, which causes exactly one data point to be dropped. After the data is dropped, all the data points to the right of the dropped data are shifted one place to the left, and the last data point is replaced with some random value. It is guaranteed that this random value will not be equal to the dropped value.
 * 
 * For example, if sensor1 = [4,2,3,1,5] and sensor2 = [4,1,2,3,5], after the data at index 2 is dropped, the sensors will collect sensor1 = [4,2,1,5] and sensor2 = [4,1,2,3,5].
 * 
 * We call the defectiveness of a sensor the number of indices at which the two sensors collect different data.
 * 
 * Example 1:
 * Input: sensor1 = [2,3,4,5], sensor2 = [2,1,3,4]
 * Output: 1
 * Explanation: The data at index 1 is dropped, which causes sensor1 to become [2,4,5] and sensor2 to become [2,3,4]. The defectiveness of sensor1 is 1 (sensor1[1] != sensor2[1]) while the defectiveness of sensor2 is 0. Therefore, we return 1.
 * 
 * Example 2:
 * Input: sensor1 = [2,2,2,2,2], sensor2 = [2,2,2,2,2]
 * Output: -1
 * Explanation: It is impossible to determine which sensor is defective.
 * 
 * Example 3:
 * Input: sensor1 = [2,3,2,2,3,2], sensor2 = [2,3,2,3,2,7]
 * Output: 3
 * Explanation: The data at index 3 is dropped, which causes sensor1 to become [2,3,2,3,2] and sensor2 to become [2,3,2,7]. The defectiveness of sensor1 is 1 (sensor1[3] != sensor2[3]) while the defectiveness of sensor2 is 2 (sensor1[4] != sensor2[4]). Therefore, we return 3.
 * 
 * Constraints:
 * 
 * 1 <= sensor1.length <= 100
 * sensor2.length == sensor1.length
 * 0 <= sensor1[i], sensor2[i] <= 100
 * 
 */
class Solution {
public:
    int badSensor(vector<int>& sensor1, vector<int>& sensor2) {
        int i = 0;
        int n = sensor1.size();
        
        // 1. 找到第一个不匹配的位置
        while (i < n - 1 && sensor1[i] == sensor2[i]) {
            i++;
        }
        
        // 2. 从第一个不匹配的位置开始，检查两种可能性
        while (i < n - 1) {
            // 如果传感器1是好的，那么传感器2应该与传感器1错位匹配
            // 即 sensor1[i+1] == sensor2[i]
            if (sensor1[i + 1] != sensor2[i]) {
                return 1;  // 传感器1有缺陷
            }
            // 如果传感器2是好的，那么传感器1应该与传感器2错位匹配
            // 即 sensor1[i] == sensor2[i+1]
            if (sensor1[i] != sensor2[i + 1]) {
                return 2;  // 传感器2有缺陷
            }
            i++;
        }
        
        // 3. 无法确定
        return -1;
    }
};