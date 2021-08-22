#ifndef APOLOGY_HPP
#define APOLOGY_HPP

#include <unordered_map>
#include <string_view>
#include <cassert>
#include <iostream>


enum class Apology {
  empty = 1,
  not_found = 2,
  invalid_order = 3,
  invalid_node = 4,
  invalid_apology = 5,
};

inline static
const std::unordered_map<Apology, std::string_view>
  Apologies =
{
  { Apology::empty, "- Apology: Tree is empty...\n" },
  { Apology::not_found, "- Apology: Node not found...\n" },
  { Apology::invalid_order, "- Apology: Invalid order...\n"},
  { Apology::invalid_node, "- Apology: Invalid node...\n"},
  { Apology::invalid_apology, "- Apology: Invalid apology...\n"}
};

inline
auto show(const Apology& apology)
    -> void
{
  switch ( apology ) {
    case Apology::empty: {
      std::cerr << Apologies.at( Apology::empty );
      assert(false);
      break;
    } case Apology::invalid_order: {
      std::cerr << Apologies.at( Apology::invalid_order );
      assert(false);
      break;
    } case Apology::invalid_node: {
      std::cerr << Apologies.at( Apology::invalid_node );
      assert(false);
    } case Apology::not_found: {
      std::cerr << Apologies.at( Apology::not_found );
      assert(false);
      break;
    }
    default: {
      std::cerr << Apologies.at( Apology::invalid_apology );
      assert(false);
    }
  }
}

#endif // APOLOGY_HPP
