#include <iostream>
#include "LinkedList.hpp"

int main()
{
  LinkedList<int> ageList;
  ageList.append(25);
  ageList.append(30);
  ageList.append(22);
  std::cout << "Age List: ";
  ageList.print();
  LinkedList<std::string> wordList;
  wordList.append("Hello");
  wordList.append("World");
  std::cout << "Word List: ";
  wordList.print();
  LinkedList<char> charList;
  charList.append('H');
  charList.append('E');
  charList.append('L');
  charList.append('L');
  charList.append('O');
  charList.append(' ');
  charList.append('W');
  charList.append('O');
  charList.append('R');
  charList.append('L');
  charList.append('D');
  std::cout << "Character List: ";
  charList.print();

  return 0;
}