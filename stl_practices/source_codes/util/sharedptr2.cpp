#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

class FileDeleter {
 private:
  std::string fileName;

 public:
  FileDeleter(const std::string &fn) : fileName(fn) {}
  void operator()(std::ofstream *fp) {
    fp->close();
    std::remove(fileName.c_str());
  }
};

int main() {
  std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"), FileDeleter("tmpfile.txt"));

  return 0;
}