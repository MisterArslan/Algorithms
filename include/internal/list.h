#ifndef NSTL_INTERNAL_LIST_H
#define NSTL_INTERNAL_LIST_H

#include "allocator.h"
#include <iterator>

namespace nstl {
namespace internal {

template<class T, class Allocator = allocator<T>>
class list;

template<typename T>
struct node {
  T value;
  node<T> *next;
  node<T> *prev;
};

template<typename T>
class iterator_impl {
private:
  node<T> *current;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename list<T>::value_type;
  using difference_type = typename list<T>::difference_type;
  using pointer = typename list<T>::pointer;
  using reference = typename list<T>::reference;
  using const_reference = typename list<T>::const_reference;
public:
  explicit iterator_impl(node<T> *node) noexcept;
  iterator_impl &operator++();
  iterator_impl operator++(int);
  iterator_impl &operator--();
  iterator_impl operator--(int);
  bool operator==(const iterator_impl &rhs);
  bool operator!=(const iterator_impl &rhs);
  reference operator*();
  const_reference operator*() const;
};

template<class T, class Allocator>
class list {
public:
  using value_type = T;
  using allocator_type = typename Allocator::template rebind<node<T>>::other;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = typename Allocator::pointer;
  using const_pointer = typename Allocator::const_pointer;
  using iterator = iterator_impl<T>;
  using const_iterator = int;
  using reverse_iterator = int;
  using const_reverse_iterator = int;
private:
  allocator_type alloc;
  node<T> *head;
  node<T> *tail;

  node<T> *create_node(const T &value);
public:
  void initialize();
  list();
  list(const list &rhs) noexcept;
  list(list &&rhs) noexcept;
  ~list();
  list &operator=(const list &rhs);
  void assign(size_type count, const T &value);
  allocator_type get_allocator();
  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;
  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
  reverse_iterator rend();
  const_reverse_iterator rend() const;
  const_reverse_iterator crend() const;
  bool empty();
  size_type size();
  void push_front(T value);
  void push_back(T value);
  reference pop_back();
  void clear();
};

#include "list_iter.inl"
#include "list.inl"

}
}

#endif //NSTL_INTERNAL_LIST_H