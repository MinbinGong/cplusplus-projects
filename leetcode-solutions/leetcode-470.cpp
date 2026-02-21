/*
 * Implement Rand10() using Rand7()
 *
 *  Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
 *
 *  Constraints:
 *  The number of calls to rand7() is less than 105.
 * 
 */

int rand10() {
  int random = 0;
  for (size_t i = 0; i < 7; i++) {
    random += rand7();
  }

  return random % 10 + 1;
}