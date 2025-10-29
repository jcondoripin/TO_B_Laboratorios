#include "Node.h"

template <typename V>
class LinkedList
{
public:
  std::shared_ptr<Node<V>> head;

  LinkedList() : head(nullptr) {}

  void append(V val)
  {
    auto newNode = std::make_shared<Node<V>>(val);
    if (!head)
    {
      head = newNode;
    }
    else
    {
      auto current = head;
      while (current->next)
      {
        current = current->next;
      }
      current->next = newNode;
    }
  }

  void print() const
  {
    auto current = head;
    while (current)
    {
      std::cout << current->value << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};
