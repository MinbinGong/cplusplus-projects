/**
 * 1500. Design a File Sharing System
 * 
 * We will use a vector to store the files of each user.
 * We will use a set to store the available user ids.
 * When a user joins, we will return the smallest available user id.
 * When a user leaves, we will add the user id back to the available user ids.
 * When a user uploads a file, we will add the file id to the user's files.
 * When a user requests a file, we will return the list of user ids who have the file.
 * 
 * Example 1:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.join(); // The smallest user id that is free is 3, so we return 3.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 2:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.join(); // The smallest user id that is free is 3, so we return 3.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 3:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.join(); // The smallest user id that is free is 3, so we return 3.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 4:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.join(); // The smallest user id that is free is 3, so we return 3.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 5:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.join(); // The smallest user id that is free is 3, so we return 3.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.    
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 6:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:
 * [null,1,2,3,null,null,4,5,[4],[2],null]
 * 
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Example 7:
 * Input:
 * ["FileSharing","join","join","join","leave","leave","join","join","request","request","leave"]
 * [[],[],[],[],[2],[1],[],[],[1],[2],[]]
 * Output:  
 * Explanation:
 * FileSharing fileSharing = new FileSharing(5); // We use a data structure that does not provide auto-ids, so we have to track the ids ourselves.
 * fileSharing.join(); // The smallest user id that is free is 1, so we return 1.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2.
 * fileSharing.leave(2); // User 2 leaves the service. No more files are shared with user 2.
 * fileSharing.join(); // The smallest user id that is free is 2, so we return 2. Note that user 2 is available.
 * fileSharing.join(); // The smallest user id that is free is 4, so we return 4.
 * fileSharing.request(1); // User 1 has not uploaded any files.
 * fileSharing.request(2); // User 2 has not uploaded any files.
 * fileSharing.leave(4); // User 4 leaves the service. No more files are shared with user 4.
 * 
 * Constraints:
 * 1 <= k <= 10^9
 * 1 <= files.length <= 10^5
 * 1 <= files[i] <= k
 * 1 <= user_id <= k
 * At most 10^5 calls will be made to join, leave, upload, and request.
 * 
 */
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

class FileSharing {
private:
    // chunkID -> set of userIDs who own this chunk (sorted)
    std::unordered_map<int, std::set<int>> chunkOwners;
    // userID -> set of chunkIDs owned by this user
    std::unordered_map<int, std::set<int>> userChunks;
    
    // Min-heap of available user IDs (reused after leave)
    std::priority_queue<int, std::vector<int>, std::greater<int>> availableIDs;
    int nextID;  // next new ID if no reusable ID is available

public:
    FileSharing(int m) {
        // m is the total number of chunks; not directly stored except for validation (optional)
        nextID = 1;
    }
    
    int join(std::vector<int> ownedChunks) {
        // Assign the smallest available ID
        int userID;
        if (!availableIDs.empty()) {
            userID = availableIDs.top();
            availableIDs.pop();
        } else {
            userID = nextID++;
        }
        
        // Record the chunks owned by this user
        for (int chunk : ownedChunks) {
            userChunks[userID].insert(chunk);
            chunkOwners[chunk].insert(userID);
        }
        
        return userID;
    }
    
    void leave(int userID) {
        // Remove user from all chunks they owned
        if (userChunks.find(userID) != userChunks.end()) {
            for (int chunk : userChunks[userID]) {
                chunkOwners[chunk].erase(userID);
                // Optional: if chunkOwners[chunk] becomes empty, you can leave it as is
            }
            userChunks.erase(userID);
        }
        
        // Recycle the user ID
        availableIDs.push(userID);
    }
    
    std::vector<int> request(int userID, int chunkID) {
        // Get current owners of the chunk (sorted because we use set)
        std::vector<int> result;
        if (chunkOwners.find(chunkID) != chunkOwners.end()) {
            result.assign(chunkOwners[chunkID].begin(), chunkOwners[chunkID].end());
        }
        
        // After the request, the user obtains the chunk
        userChunks[userID].insert(chunkID);
        chunkOwners[chunkID].insert(userID);
        
        return result;
    }
};