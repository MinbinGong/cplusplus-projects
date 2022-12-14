#include <cstring>

class custom_string {
private:
  char *str;

public:
  custom_string();
  custom_string(char *val);
  custom_string(const custom_string &source);
  custom_string(custom_string &&source);
  ~custom_string();
};

custom_string::custom_string() : str{nullptr} {
  str = new char[1];
  str[0] = '\0';
}

custom_string::custom_string(char *val) {
  if (nullptr == val) {
    custom_string();
  } else {
    str = new char[strlen(val) + 1];

    strcpy(str, val);
    str[strlen(val)] = '\0';
  }
}

custom_string::custom_string(const custom_string &source) {
  str = new char[strlen(source.str) + 1];
  strcpy(str, source.str);
  str[strlen(source.str)] = '\0';
}

custom_string::custom_string(custom_string &&source) {
  str = source.str;
  source.str = nullptr;
}

custom_string::~custom_string() { delete str; }
