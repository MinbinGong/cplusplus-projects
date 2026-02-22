/*
 * Find Duplicate File in System
 * 
 * Given a list of directory info including directory path, and all the files with contents in this directory, you need to find out all the groups of duplicate files in the file system in terms of their paths.
 * 
 * A group of duplicate files consists of at least two files that have exactly the same content.
 * 
 * A single directory info string in the input list has the following format:
 * 
 * "root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
 * 
 * It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm.
 * Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.
 * 
 * The output is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:
 * 
 * "directory_path/file_name.txt"
 * 
 * The order of returning the groups does not matter.
 * Within each group, the file paths are sorted in lexicographic order.
 * 
 * Note:
 * 1. No order is required for the final output.
 * 2. You may assume the directory name, file name and file content only has letters and digits, and the length of file content is in the range of [1,50].
 * 3. The number of files given is in the range of [1,20000].
 * 4. You may assume no files or directories share the same name in a same directory.
 * 5. You may assume each given directory info represents a unique directory. Directory path and file info are separated by a single blank space.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

class Solution {
public:
    std::vector<std::vector<std::string>> findDuplicate(std::vector<std::string>& paths) {
        std::unordered_map<std::string, std::vector<std::string>> contentToPaths;
        
        for (const std::string& entry : paths) {
            std::istringstream iss(entry);
            std::string dir;
            iss >> dir;  // first token is directory path
            
            std::string file;
            while (iss >> file) {
                // file format: "filename(content)"
                size_t openParen = file.find('(');
                std::string filename = file.substr(0, openParen);
                std::string content = file.substr(openParen + 1, file.size() - openParen - 2); // exclude closing ')'
                std::string fullPath = dir + "/" + filename;
                contentToPaths[content].push_back(fullPath);
            }
        }
        
        std::vector<std::vector<std::string>> result;
        for (const auto& pair : contentToPaths) {
            if (pair.second.size() > 1) {
                result.push_back(pair.second);
            }
        }
        return result;
    }
};