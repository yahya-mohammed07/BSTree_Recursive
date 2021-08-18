/**
 * @file bst.hpp
 * @author yahya mohammed (goldroger.1993@outlook.com)
 * @version 1.5
 * @date 2021-07-7 (date started)
 */

#ifndef BST_HPP
#define BST_HPP

// includes

#include <iostream>
#include <memory>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <stack>
#include <unordered_map>
#include <string_view>


enum class Apology {
  empty = 1,
  not_found = 2,
};

inline
const std::unordered_map<Apology, std::string_view>
  Apologies =
{
  { Apology::empty, "- Apology: Tree is empty...\n" },
  { Apology::not_found, "- Apology: Node not found...\n" },
};

inline
auto check_apology(const Apology& apology)
    -> void
{

  if ( apology == Apology::empty ) {
    std::cerr << Apologies.at( Apology::empty );
    assert(false);
  }
  std::cerr << Apologies.at( Apology::not_found );
  assert(false);
}

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
private:
//
  using sh_ptr = std::shared_ptr<node>;
  // allocators
  constexpr
  auto allocate(const Ty& val, const sh_ptr& left,
                    const sh_ptr& right)
      -> const sh_ptr
  {
    return std::make_shared<node>(val, left, right);
  }
  constexpr
  auto allocate(Ty &&val, sh_ptr &&left, sh_ptr &&right)
      -> sh_ptr&&
  {
    return std::make_shared<node>(val, left, right);
  }
  //
  sh_ptr m_root{nullptr};
  sh_ptr m_left_most{};
  std::size_t m_size{};
  Ty _failed_{};
//
  class iterator {
  private:
    sh_ptr root_itr{};
  //
  public:
    iterator(const sh_ptr &copy) : root_itr(copy) {}
    iterator(sh_ptr &&move) : root_itr(move) {}
    iterator(std::nullptr_t &&move ) : root_itr(move) {}
    iterator(const std::nullptr_t &move ) : root_itr(move) {}
    // foo++
    constexpr iterator operator++(int) {
      // TODO
      return *this;
    }
    // ++foo
    constexpr iterator operator++() {
      // TODO;
      return *this;
    }
    // get data
    constexpr Ty& operator*() const {
      return root_itr->m_data;
    }
    // get and modify data
    constexpr Ty& operator*() {
      return root_itr->m_data;
    }
    constexpr bool operator!=(const sh_ptr & rhs) const {
      return root_itr != rhs;
    }
    constexpr bool operator!=(sh_ptr && rhs) const {
      return root_itr != rhs;
    }

    constexpr bool operator==(const sh_ptr & rhs) const {
      return root_itr == rhs;
    }
    constexpr bool operator==(sh_ptr && rhs) const {
      return root_itr == rhs;
    }
  //
  }; // end of class iterator
//
public:
//
  constexpr bst_() noexcept : m_root{nullptr} {};

  constexpr bst_(const bst_<Ty> &rhs) noexcept {
    m_root = rhs.m_root;
    m_size = rhs.m_size;
    m_left_most = rhs.m_left_most;
  }

  constexpr bst_(bst_<Ty> &&rhs) noexcept
    : m_root(std::move(rhs.m_root)),
        m_left_most(std::move(rhs.m_left_most)),
          m_size(std::move(rhs.m_size))
  {
    rhs.m_root.reset();
    rhs.m_size = 0;
    rhs.m_left_most.reset();
  }

//
  [[nodiscard]]
  constexpr auto find(Ty &&node) const
      -> const iterator
  {
    if ( is_empty() ) {
      return end();
    }
    auto find_hidden = [this] (Ty &&node, const sh_ptr& root,
                                    auto && lambda)
        -> const iterator
    {
      if ( !root ) return end();
      if ( node > root->m_data ) {
        return lambda(std::move(node), root->m_right,
                            std::move(lambda));
      } else if ( node < root->m_data) {
          return lambda(std::move(node), root->m_left,
                      std::move(lambda));
      } else return root;
      return end();
    };
    return find_hidden(std::move(node), m_root,
                            std::move(find_hidden));
  }
  [[nodiscard]]
  constexpr auto find(const Ty &node) const
      -> const iterator
  {
    if ( is_empty() ) {
      return end();
    }
    auto find_hidden = [this] (const Ty &node, const sh_ptr& root,
                                    auto && lambda)
        -> const iterator
    {
      if ( !root ) return end();
      if ( node > root->m_data ) {
        return lambda(node, root->m_right,
                            std::move(lambda));
      } else if ( node < root->m_data) {
          return lambda(node, root->m_left,
                      std::move(lambda));
      } else return root;
      return end();
    };
    return find_hidden(node, m_root,
                            std::move(find_hidden));
  }

  [[nodiscard]]
  constexpr auto begin() const noexcept
    -> iterator { return iterator( m_left_most ); }
   [[nodiscard]]
  constexpr auto begin() noexcept
    -> iterator { return iterator( m_left_most ); }

  [[nodiscard]]
  constexpr auto end() const noexcept
    ->  std::nullptr_t { return nullptr; }
//

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
    auto insert_hidden = [this]
                (Ty &&val, sh_ptr &root, auto&& lambda)
        -> void
    {
      if ( !root ) {
        root = allocate(std::move(val), std::move(nullptr),
                                            std::move(nullptr));
      } else if (val > root->m_data) {
        lambda(std::move(val), root->m_right, std::move(lambda));
      } else if (val < root->m_data) {
        lambda(std::move(val), root->m_left, std::move(lambda));
      } else;
    };
    insert_hidden(std::move(val), std::move(m_root),
                                    std::move(insert_hidden));
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
    auto insert_hidden = [this]
                        (const Ty &val,
                          sh_ptr &root, auto&& lambda)
        -> void
    {
      if ( !root ) { // root == nullptr
        root = allocate(val, nullptr, nullptr);
      } else if (val > root->m_data) {
        lambda(val, root->m_right, std::move(lambda));
      } else if (val < root->m_data) {
        lambda(val, root->m_left, std::move(lambda));
      } else;
    };
    insert_hidden(val, m_root, std::move(insert_hidden));
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
      check_apology( Apology::empty );
      return;
    }
    //
    assert((order > 0 && order < 4) && "- order undefined\n");
    constexpr
    auto print_hidden = []
                        (const sh_ptr &root,
                          const int order,
                            auto &&lambda)
        -> void
    {
      if ( order == 1 && root != nullptr ) {
        std::cout << root->m_data << ' ';
        lambda(root->m_left, order, std::move(lambda));
        lambda(root->m_right, order, std::move(lambda));
      } else if ( order == 2 && root != nullptr ) {
        lambda(root->m_left, order, std::move(lambda));
        std::cout << root->m_data << ' ';
        lambda(root->m_right, order, std::move(lambda));
      } else if ( order == 3 && root != nullptr ) {
        lambda(root->m_left, order, std::move(lambda));
        lambda(root->m_right, order, std::move(lambda));
        std::cout << root->m_data << ' ';
      }
    };
    print_hidden(m_root, order, std::move(print_hidden));
  }

  /**
   * @brief find if certain element exits int BSTree
   * @param val
   * @return true
   * @return false
   */
  [[nodiscard]]
  constexpr
  auto contains(Ty &&val) const
    -> bool
  {
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return false;
    }
    //
    constexpr
    auto contains_hidden = []
                      (Ty &&val , const sh_ptr &root,
                                   auto &&lambda)
      -> bool
    {
      if ( !root ) { return false; }
      else if (val > root->m_data) {
        return lambda(std::move(val), root->m_right, std::move(lambda));
      } else if (val < root->m_data) {
        return lambda(std::move(val), root->m_left, std::move(lambda));
      } else return true; // found
      return false;
    };
    return contains_hidden(std::move(val), m_root,
                          std::move(contains_hidden));
  }

  /**
   * @brief find if certain element exits int BSTree
   * @param val
   * @return true
   * @return false
   */
  [[nodiscard]]
  constexpr
  auto contains(const Ty &val) const
    -> bool
  {
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return false;
    }
    //
    constexpr
    auto contains_hidden = []
                      (const Ty& val , const sh_ptr& root,
                            auto &&lambda)
      -> bool
    {
      if ( !root ) { return false; }
      else if (val > root->m_data) {
        return lambda(val, root->m_right, std::move(lambda));
      } else if (val < root->m_data) {
        return lambda(val, root->m_left, std::move(lambda));
      } else return true; // found
      return false;
    };
    return contains_hidden(val, m_root, std::move(contains_hidden));
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
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return _failed_;
    }
    //
    constexpr
    auto max_hidden = []
                      (const sh_ptr &root,
                            auto &&lambda)
        -> sh_ptr
    {
      if ( !root ) { return nullptr; }
      if ( !root->m_right ) { return root; }
      return lambda(root->m_right, std::move(lambda));
    };
    return max_hidden(m_root, std::move(max_hidden))->m_data;
  }
  /**
   * @brief get minimum element in BSTree
   * @return const Ty&
   */
  [[nodiscard]]
  constexpr
  auto min()
      -> Ty
  {
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return _failed_;
    }
    //
    m_left_most = std::move( min(m_root) );
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
      check_apology( Apology::empty );
      return;
    }
    //
    --m_size;
    auto remove_hidden = [this]
                        (Ty &&val, sh_ptr &root,
                            auto &&lambda)
        -> void
    {
      if ( !root ) { return; }
      else if ( val > root->m_data ) {
        lambda(std::move(val), root->m_right, std::move(lambda));
      } else if ( val < root->m_data ) {
        lambda(std::move(val), root->m_left, std::move(lambda));
      } else if ( root->m_right != nullptr
                      && root->m_left != nullptr)
      { // Has two children
        root->m_data = min(root->m_right)->m_data;
        lambda(std::move(root->m_data), root->m_right, std::move(lambda));
      } else {
        sh_ptr old_node = root;
        root = (root->m_left != nullptr)
                        ?  root->m_left : root->m_right;
        old_node.reset();
      }
    };
    remove_hidden(std::move(val), m_root, std::move(remove_hidden));
  }

  constexpr
  auto remove(const Ty &val)
	  -> void
  {
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return;
    }
    //
    --m_size;
    auto remove_hidden = [this]
                        (const Ty &val, sh_ptr &root,
                            auto &&lambda)
        -> void
    {
      if ( !root ) { return; }
      else if ( val > root->m_data ) {
        lambda(val, root->m_right, std::move(lambda));
      } else if ( val < root->m_data ) {
        lambda(val, root->m_left, std::move(lambda));
      } else if ( root->m_right != nullptr
                      && root->m_left != nullptr)
      { // Has two children
        root->m_data = min(root->m_right)->m_data;
        lambda(root->m_data, root->m_right, std::move(lambda));
      } else {
        sh_ptr old_node = root;
        root = (root->m_left != nullptr)
                        ?  root->m_left : root->m_right;
        old_node.reset();
      }
    };
    remove_hidden(val, m_root, std::move(remove_hidden));
  }

  //
  constexpr
  auto depth(Ty &&node) const
      -> std::size_t
  {
    if ( is_empty() ) {check_apology( Apology::empty ); return 0ull;}
    //
    constexpr
    auto depth_hidden = [](const sh_ptr &root, Ty &&node,
                                      std::size_t &&height,
                                        auto &&lambda)
        -> std::size_t
    {
      if ( !root ) { return 0ull; }
      else if  ( root->m_data == node ) { return height; }
      return static_cast<std::size_t>(std::max(
        lambda(root->m_left, std::move(node), height+1ull, std::move(lambda)),
        lambda(root->m_right, std::move(node), height+1ull, std::move(lambda))
      ));
    };
  //
    return depth_hidden(m_root, std::move(node), 0ull,
                            std::move(depth_hidden));
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
    if ( is_empty() ) {
      check_apology( Apology::empty );
      return 0ull;
    }
    //
    constexpr
    auto depth_hidden = [](const sh_ptr &root,
                            const Ty &node,
                                  std::size_t &&height,
                                    auto &&lambda)
        -> std::size_t
    {
      if ( !root ) { return 0ull; }
      else if  ( root->m_data == node ) { return height; }
      return static_cast<std::size_t> (std::max(
        lambda(root->m_left, node, height+1ull, std::move(lambda)),
        lambda(root->m_right, node, height+1ull, std::move(lambda))
      ));
    };
  //
    return depth_hidden(m_root, node, 0ull, std::move(depth_hidden));
  }

//
private:
  constexpr
  auto min (const sh_ptr &root)
        -> sh_ptr
  {
    if ( !root ) { return nullptr; }
    if ( !root->m_left ) { return root; }
    return min(root->m_left);
  }

// operators
public:

  constexpr bst_<Ty>& operator=(const bst_<Ty> &rhs) noexcept {
    if (this != &rhs) {
      m_root      = rhs.m_root;
      m_size      = rhs.m_size;
      m_left_most = rhs.m_left_most;
    }
    return *this;
  }

  constexpr bst_<Ty>& operator=(bst_<Ty> &&rhs) noexcept {
    if (this != &rhs) {
      m_root        = std::move(rhs.m_root);
      m_size        = std::move(rhs.m_size);
      m_left_most   = std::move(rhs.m_left_most);
      //
      rhs.m_root.reset();
      rhs.m_size = 0;
      rhs.m_left_most.reset();
    }
    return *this;
  }
};

#endif // BST_HPP