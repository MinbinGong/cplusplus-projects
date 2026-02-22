/*
 * Design In-Memory File System
 *
 * Design an in-memory file system to simulate the following functions:
 * ls: Given a path in string format. If it is a file path, return a list that only contains this file's name. If it is a directory path, return the list of file and directory names in this directory. Your output (file and directory names together) should in lexicographic order.
 * 
 * mkdir: Given a directory path that does not exist, you should make a new directory according to the path. If the middle directories in the path don't exist either, you should create them as well. This function has void return type.
 * 
 * addContentToFile: Given a file path and file content in string format. If the file doesn't exist, you need to create that file containing given content. If the file already exists, you need to append given content to original content. This function has void return type.
 * 
 * readContentFromFile: Given a file path, return its content in string format.
 * 
 * Note:
 * You can assume all file or directory paths are absolute paths which begin with / and do not end with / except that the path is just "/".
 * You can assume that all operations will be passed valid parameters and users will not attempt to retrieve file content or list a directory or file that does not exist.
 * You can assume that all directory names and file names only contain lower-case letters, and same names won't exist in the same directory.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class FileSystem {
private:
    struct Node {
        unordered_map<string, Node*> children;
        bool is_file;
        string content;
        
        Node() : is_file(false) {}
    };
    
    Node* root;
    
    // Helper to split path into components (skipping empty strings from '/')
    vector<string> getPathComponents(const string& path) {
        vector<string> components;
        istringstream iss(path);
        string part;
        while (getline(iss, part, '/')) {
            if (!part.empty()) {
                components.push_back(part);
            }
        }
        return components;
    }
    
public:
    FileSystem() {
        root = new Node();
    }
    
    vector<string> ls(string path) {
        Node* curr = root;
        vector<string> components = getPathComponents(path);
        
        // Traverse to the target node
        for (const string& comp : components) {
            curr = curr->children[comp];
        }
        
        // If it's a file, return just its name
        if (curr->is_file) {
            return {components.empty() ? "" : components.back()};
        }
        
        // If it's a directory, collect and sort all child names
        vector<string> result;
        for (const auto& [name, _] : curr->children) {
            result.push_back(name);
        }
        sort(result.begin(), result.end());
        return result;
    }
    
    void mkdir(string path) {
        Node* curr = root;
        vector<string> components = getPathComponents(path);
        
        for (const string& comp : components) {
            if (!curr->children.count(comp)) {
                curr->children[comp] = new Node();
            }
            curr = curr->children[comp];
        }
    }
    
    void addContentToFile(string filePath, string content) {
        Node* curr = root;
        vector<string> components = getPathComponents(filePath);
        
        // Traverse/create all directories in the path
        for (int i = 0; i < components.size(); i++) {
            const string& comp = components[i];
            if (!curr->children.count(comp)) {
                curr->children[comp] = new Node();
            }
            curr = curr->children[comp];
        }
        
        // Mark as file and append content
        curr->is_file = true;
        curr->content += content;
    }
    
    string readContentFromFile(string filePath) {
        Node* curr = root;
        vector<string> components = getPathComponents(filePath);
        
        for (const string& comp : components) {
            curr = curr->children[comp];
        }
        
        return curr->content;
    }
};