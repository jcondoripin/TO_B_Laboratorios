#include <memory>

template <typename V>
class Node
{
public:
  V value;
  std::shared_ptr<Node<V>> next;

  Node(V val) : value(val), next(nullptr) {}
};