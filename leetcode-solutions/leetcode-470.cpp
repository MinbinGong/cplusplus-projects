// Implement Rand10() using Rand7()

int rand10() {
  int random = 0;
  for (size_t i = 0; i < 7; i++) {
    random += rand7();
  }

  return random % 10 + 1;
}