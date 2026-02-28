/*
 * 1166. Design File System
 *
 * You are asked to design a file system that allows you to create new paths and associate them with different values.
 *
 * The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string "" and "/" are not.
 *
 * Implement the FileSystem class:
 *
 * bool createPath(string path, int value) Creates a new path and associates a value to it if possible and returns true. Returns false if the path already exists or its parent path doesn't exist.
 * int get(string path) Returns the value associated with path or returns -1 if the path doesn't exist.
 *
 * Example 1:
 * Input: 
 * ["FileSystem","createPath","get"]
 * [[],["/a",1],["/a"]]
 * Output: 
 * [null,true,1]
 * Explanation: 
 * FileSystem fileSystem = new FileSystem();
 *
 * Example 2:
 * Input: 
 * ["FileSystem","createPath","createPath","get","createPath","get"]
 * [[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
 * Output: 
 * [null,true,true,2,false,-1]
 * Explanation: 
 * FileSystem fileSystem = new FileSystem();
 *
 * Note:
 * 1 <= path.length <= 100
 * 1 <= value <= 10^9
 * Each path is absolute and begins with a slash '/'.
 * Each path only contains lowercase English letters.
 * The same path won't be associated with two different values.
 * 
 */
#include <string>
#include <unordered_map>

class FileSystem {
private:
    std::unordered_map<std::string, int> paths; // stores created paths and their values

public:
    FileSystem() {
        // root "/" exists implicitly, no need to store it
    }
    
    bool createPath(std::string path, int value) {
        // if path already exists, cannot create
        if (paths.count(path)) {
            return false;
        }
        
        // find parent directory
        size_t lastSlash = path.find_last_of('/');
        std::string parent = path.substr(0, lastSlash);
        
        // parent must exist unless it's root (empty string)
        if (!parent.empty() && !paths.count(parent)) {
            return false;
        }
        
        // create the path
        paths[path] = value;
        return true;
    }
    
    int get(std::string path) {
        auto it = paths.find(path);
        if (it != paths.end()) {
            return it->second;
        }
        return -1;
    }
};