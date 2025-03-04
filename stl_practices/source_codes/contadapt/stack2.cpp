// contadapt/stack2.cpp

#include <exception>
#include <iostream>

#include "Stack.hpp"
using namespace std;

int main() {
  try {
    Stack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);

    cout << st.pop() << ' ';
    cout << st.pop() << ' ';

    st.top() = 77;

    st.push(4);
    st.push(5);

    st.pop();

    cout << st.pop() << ' ';
    cout << st.pop() << endl;
    cout << st.pop() << endl;
  } catch (const std::exception& e) {
    cerr << "EXCEPTION: " << e.what() << endl;
  }
}