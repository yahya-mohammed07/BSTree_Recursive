/**
 * @file bst.hpp
 * @author your name (goldroger.1993@outlook.com)
 * @version 0.1
 * @date 2021-07-7 (date started)
 */

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <memory>
#include <cassert>
#include <functional>
#include <initializer_list>
//
inline constexpr
auto empty_tree = [] {
  std::puts("- tree is empty, value returned: ");
};

template<class Ty>
class bst_
{
//
  struct node
  {
    using sh_ptr = std::shared_ptr<node>;
    //
    Ty m_data{};
    sh_ptr m_left{};
    sh_ptr m_right{};
    //
    explicit constexpr
    node(const Ty& val, const sh_ptr& left,
                              const sh_ptr& right)
                                    noexcept
        : m_data(val), m_left(left), m_right(right) {}
    //
    explicit constexpr
    node(Ty&& val, sh_ptr&& left, sh_ptr&& right)
                                      noexcept
        : m_data(val), m_left(left), m_right(right) {}
  };
//
//TODO add iterators
private:
//
  using sh_ptr = std::shared_ptr<node>;
  // allocators
  constexpr
  auto allocate(const Ty& val, const sh_ptr& left,
                    const sh_ptr& right)
      -> sh_ptr
  {
    return std::make_shared<node>(val, left, right);
  }
  constexpr
  auto allocate(Ty &&val, sh_ptr &&left, sh_ptr &&right)
      -> sh_ptr
  {
    return std::make_shared<node>(val, left, right);
  }
  //
  sh_ptr m_root{nullptr};
  std::size_t m_size{};
  Ty _failed_{};
//
public:

  explicit constexpr bst_() noexcept : m_root{nullptr} {};
///variadic inserting
  template<class ...arg>
  explicit constexpr bst_(arg &&...values) noexcept
  {
    (insert(std::move(values)),...);
  }
  template<class ...arg>
  explicit constexpr bst_(const arg &...values) noexcept
  {
    (insert(values),...);
  }
// init-list inserting
  explicit constexpr
  bst_(std::initializer_list<Ty> &&values) noexcept
  {
    for (auto &&i : values) { insert(i); }
  }
  explicit constexpr
  bst_(const std::initializer_list<Ty> &values) noexcept
  {
    for (const auto &i : values) { insert(i); }
  }
//
  /**
   * @brief checks if the tree is empty
   * @return true
   * @return false
   */
  [[nodiscard]]
  constexpr
  auto is_empty() const
      -> bool
  {
    return m_root == nullptr;
  }

  /**
   * @brief exactly!!
   * @return std::size_t
   */
  [[nodiscard]]
  constexpr
  auto size() const -> std::size_t
  {
    return m_size;
  }

  /**
   * @brief insert an element to BSTree
   * @param val
   */
  constexpr
  auto insert(Ty &&val)
      -> void
  {
    ++m_size;
    std::function<void(Ty, sh_ptr&)>
        insert_hidden = [&insert_hidden, this]
                        (Ty &&val, sh_ptr &root)
        -> void
    {
      if ( !root ) {
        root = allocate(std::move(val), nullptr, nullptr);
      } else if (val > root->m_data) {
        insert_hidden(std::move(val), root->m_right);
      } else if (val < root->m_data) {
        insert_hidden(std::move(val), root->m_left);
      } else;
    };
    insert_hidden(std::move(val), m_root);
  }

  /**
   * @brief insert an element to BSTree
   * @param val
   */
  constexpr
  auto insert(const Ty &val)
      -> void
  {
    ++m_size;
    std::function<void(Ty, sh_ptr&)>
      insert_hidden = [&insert_hidden, this]
                        (const Ty &val,
                          sh_ptr &root)
        -> void
    {
      if ( !root ) { // root == nullptr
        root = allocate(val, nullptr, nullptr);
      } else if (val > root->m_data) {
        insert_hidden(val, root->m_right);
      } else if (val < root->m_data) {
        insert_hidden(val, root->m_left);
      } else;
    };
    insert_hidden(val, m_root);
  }

  /**
   * @brief you what is does
   * @param order `1` for pre-order
   * @param order `2` for in-order
   * @param order `3` for post-order
   */
  constexpr
  auto print(const int order) const
      -> void
  {
    if ( is_empty() ) {
      empty_tree();
      return;
    }
    //
    assert((order > 0 && order < 4) && "- order undefined\n");
    std::function<void(sh_ptr, int)>
      print_hidden = [&print_hidden]
                        (const sh_ptr &root,
                          const int order)
        -> void
    {
      if ( order == 1 && root != nullptr ) {
        std::cout << root->m_data << ' ';
        print_hidden(root->m_left, order);
        print_hidden(root->m_right, order);
      } else if ( order == 2 && root != nullptr ) {
        print_hidden(root->m_left, order);
        std::cout << root->m_data << ' ';
        print_hidden(root->m_right, order);
      } else if ( order == 3 && root != nullptr ) {
        print_hidden(root->m_left, order);
        print_hidden(root->m_right, order);
        std::cout << root->m_data << ' ';
      }
    };
    print_hidden(m_root, order);
  }

  /**
   * @brief find if certain element exits int BSTree
   * @param val
   * @return true
   * @return false
   */
  [[nodiscard]]
  constexpr
  auto find(Ty &&val) const
    -> bool
  {
    if (is_empty()) {
      empty_tree();
      return _failed_;
    }
    //
    std::function<bool(Ty, sh_ptr)>
      find_hidden = [&find_hidden]
                      (Ty &&val , sh_ptr &&root)
      -> bool
    {
      if ( !root ) { return false; }
      else if (val > root->m_data) {
        return find_hidden(std::move(val), root->m_right);
      } else if (val < root->m_data) {
        return find_hidden(std::move(val), root->m_left);
      } else return true; // found
      return false;
    };
    return find_hidden(std::move(val), m_root);
  }

  /**
   * @brief find if certain element exits int BSTree
   * @param val
   * @return true
   * @return false
   */
  [[nodiscard]]
  constexpr
  auto find(const Ty &val) const
    -> bool
  {
    if (is_empty()) {
      empty_tree();
      return _failed_;
    }
    //
    std::function<bool(Ty, sh_ptr)>
      find_hidden = [&find_hidden]
                      (const Ty& val , const sh_ptr& root)
      -> bool
    {
      if ( !root ) { return false; }
      else if (val > root->m_data) {
        return find_hidden(val, root->m_right);
      } else if (val < root->m_data) {
        return find_hidden(val, root->m_left);
      } else return true; // found
      return false;
    };
    return find_hidden(val, m_root);
  }

  /**
   * @brief get maximum element in BSTree
   * @return const Ty&
   */
  [[nodiscard]]
  constexpr
  auto max() const
      -> Ty
  {
    if (is_empty()) {
      empty_tree();
      return _failed_;
    }
    //
    std::function<sh_ptr(sh_ptr)>
      max_hidden = [&max_hidden]
                      (const sh_ptr &root)
        -> sh_ptr
    {
      if ( !root ) { return nullptr; }
      if ( !root->m_right ) { return root; }
      return max_hidden(root->m_right);
    };
    return max_hidden(m_root)->m_data;
  }
  /**
   * @brief get minimum element in BSTree
   * @return const Ty&
   */
  [[nodiscard]]
  constexpr
  auto min() const
      -> Ty
  {
    if (is_empty()) {
      empty_tree();
      return _failed_;
    }
    //
    return min(m_root)->m_data;
  }

  /**
   * @brief remove a node from the BSTree
   * @param val to be removes
   */
  constexpr
  auto remove(Ty &&val)
	  -> void
  {
    if ( is_empty() ) {
      empty_tree();
      return;
    }
    //
    std::function<void(Ty, sh_ptr&)>
      remove_hidden = [&remove_hidden, this]
                        (Ty &&val, sh_ptr &root)
        -> void
    {
      if ( !root ) { return; }
      else if ( val > root->m_data ) {
        remove_hidden(std::move(val), root->m_right);
      } else if ( val < root->m_data ) {
        remove_hidden(std::move(val), root->m_left);
      } else if ( root->m_right != nullptr
                      && root->m_left != nullptr)
      { // Has two children
        root->m_data = min(root->m_right)->m_data;
        remove_hidden(std::move(root->m_data), root->m_right);
      } else {
        sh_ptr old_node = root;
        root = (root->m_left != nullptr)
                        ?  root->m_left : root->m_right;
        old_node.reset();
      }
    };
    remove_hidden(std::move(val), m_root);
  }

  constexpr
  auto remove(const Ty &val)
	  -> void
  {
    if ( is_empty() ) {
      empty_tree();
      return;
    }
    //
    std::function<void(Ty, sh_ptr&)>
      remove_hidden = [&remove_hidden, this]
                        (const Ty &val, sh_ptr &root)
        -> void
    {
      if ( !root ) { return; }
      else if ( val > root->m_data ) {
        remove_hidden(val, root->m_right);
      } else if ( val < root->m_data ) {
        remove_hidden(val, root->m_left);
      } else if ( root->m_right != nullptr
                      && root->m_left != nullptr)
      { // Has two children
        root->m_data = min(root->m_right)->m_data;
        remove_hidden(root->m_data, root->m_right);
      } else {
        sh_ptr old_node = root;
        root = (root->m_left != nullptr)
                        ?  root->m_left : root->m_right;
        old_node.reset();
      }
    };
    remove_hidden(val, m_root);
  }

  //
  constexpr
  auto depth(Ty &&node) const
      -> std::size_t
  {
    if ( is_empty() ) { empty_tree(); return 0ull;}
  //
    std::function<std::size_t(sh_ptr , Ty, std::size_t)>
    depth_hidden = [&depth_hidden](sh_ptr &&root, Ty &&node,
                                      std::size_t &&height)
        -> std::size_t
    {
      if ( !root ) { return 0ull; }
      else if  ( root->m_data == node ) { return height; }
      return static_cast<std::size_t> (std::max(
        depth_hidden(root->m_left, node, height+1ull),
        depth_hidden(root->m_right, node, height+1ull)
      ));
    };
  //
    return depth_hidden(std::move(m_root), node, 0ull);
  }

  /**
   * @brief get the height of given node number in the BSTree
   * @param node node number
   * @return std::size_t
   */
  constexpr
  auto depth(const Ty &node) const
      -> std::size_t
  {
    if ( is_empty() ) { empty_tree(); return 0ull;}
  //
    std::function<std::size_t(sh_ptr , Ty, std::size_t)>
    depth_hidden = [&depth_hidden](const sh_ptr &root,
                            const Ty &node,
                                  std::size_t &&height)
        -> std::size_t
    {
      if ( !root ) { return 0ull; }
      else if  ( root->m_data == node ) { return height; }
      return static_cast<std::size_t> (std::max(
        depth_hidden(root->m_left, node, height+1ull),
        depth_hidden(root->m_right, node, height+1ull)
      ));
    };
  //
    return depth_hidden(m_root, node, 0ull);
  }
//
private:
  constexpr
  auto min (const sh_ptr &root) const
        -> sh_ptr
  {
    if ( !root ) { return nullptr; }
    if ( !root->m_left ) { return root; }
    return min(root->m_left);
  }

};

#endif // BST_HPP