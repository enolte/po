#include <iostream>
#include <cassert>

#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie.h"

using po::operator<<;

void trie_scenario_rank2();

void trie_scenario()
{
  trie_scenario_rank2();

  PO_LINE;
}

po::trie add_first_term();
po::trie& add_second_term(po::trie&);
po::trie& add_third_term(po::trie&);
po::trie& remove_second_term(po::trie&);
po::trie& readd_second_term(po::trie&);

void trie_scenario_rank2()
{
  auto t = add_first_term();
  add_second_term(t);
  add_third_term(t);
  remove_second_term(t);
  readd_second_term(t);
  remove_second_term(t);
}

po::trie add_first_term()
{
  po::trie t{};

  assert(t.npaths() == 0);
  assert(t.coefficients.empty());
  assert(t.vertices.empty());
  assert(t.roots.empty());

  t.insert(1.2, {3, 5}); // 1.2 * x**3 * y**5

// PO_LINE;
  // PO_TRACE(" t.vertices = " << t.vertices);
  // PO_TRACE(t.coefficients);

  assert(t.roots == decltype(po::trie::vertex::children){0});
  assert(t.vertices.size() == 3);
  assert((t.vertices[0] == po::trie::vertex{3, {1}, 0}));
  assert((t.vertices[1] == po::trie::vertex{5, {2}, 1}));
  assert((t.vertices[2] == po::trie::vertex{0, {} , po::trie_constants::ABSENT}));

  assert(t.coefficients == (decltype(t.coefficients)){1.2});
  assert(t.coefficient({3, 2}) == po::scalar_type{0});

  assert(t.npaths() == 1);

  return t;
}

po::trie& add_second_term(po::trie& t)
{
  t.insert(-.33, {3, 2}); // -.33 * x**3 * y**2

// PO_LINE;
  // PO_TRACE(" t.vertices = " << t.vertices);
  // PO_TRACE(t.coefficients);

  assert(t.roots == decltype(po::trie::vertex::children){0});
  assert(t.vertices.size() == 5);
  assert((t.vertices[0] == po::trie::vertex{3, {1, 3}, 0}));
  assert((t.vertices[1] == po::trie::vertex{5, {2}   , 1}));
  assert((t.vertices[2] == po::trie::vertex{0, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[3] == po::trie::vertex{2, {4}   , 1}));
  assert((t.vertices[4] == po::trie::vertex{1, {}    , po::trie_constants::ABSENT}));

  assert((t.coefficients == (decltype(t.coefficients)){1.2, -0.33}));
  assert(t.coefficient({3, 2}) == -.33);

  assert(t.npaths() == 2);

  return t;

}

po::trie& add_third_term(po::trie& t)
{
  t.insert(5.1, {12, 12});

  assert((t.roots == decltype(po::trie::vertex::children){0, 5}));
  assert(t.vertices.size() == 8);
  assert((t.vertices[0] == po::trie::vertex{ 3, {1, 3}, 0}));
  assert((t.vertices[1] == po::trie::vertex{ 5, {2}   , 1}));
  assert((t.vertices[2] == po::trie::vertex{ 0, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[3] == po::trie::vertex{ 2, {4}   , 1}));
  assert((t.vertices[4] == po::trie::vertex{ 1, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[5] == po::trie::vertex{12, {6}   , 0}));
  assert((t.vertices[6] == po::trie::vertex{12, {7}   , 1}));
  assert((t.vertices[7] == po::trie::vertex{ 2, {}    , po::trie_constants::ABSENT}));

  assert((t.coefficients == (decltype(t.coefficients)){1.2, -0.33, 5.1}));
  assert(t.coefficient({12, 12}) == 5.1);

  assert(t.npaths() == 3);

  return t;
}

po::trie& remove_second_term(po::trie& t)
{
  t.remove({3, 2});

  assert((t.roots == decltype(po::trie::vertex::children){0, 5}));
  assert(t.vertices.size() == 8);
  assert((t.vertices[0] == po::trie::vertex{ 3, {1, 3}, 0}));
  assert((t.vertices[1] == po::trie::vertex{ 5, {2}   , 1}));
  assert((t.vertices[2] == po::trie::vertex{ 0, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[3] == po::trie::vertex{ 2, {4}   , 1}));
  assert((t.vertices[4] == po::trie::vertex{ 1, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[5] == po::trie::vertex{12, {6}   , 0}));
  assert((t.vertices[6] == po::trie::vertex{12, {7}   , 1}));
  assert((t.vertices[7] == po::trie::vertex{ 2, {}    , po::trie_constants::ABSENT}));


  assert(t.coefficients.size() == 3);
  assert(t.coefficients[0] == 1.2);
  assert(t.coefficients[1] != t.coefficients[1]);
  assert(t.coefficients[2] == 5.1);

  assert(t.coefficient({3, 2}) == 0);

  assert(t.npaths() == 3);
  assert(t.nterms() == 2);

  return t;
}

po::trie& readd_second_term(po::trie& t)
{
  t.insert(-.33, {3, 2}); // -.33 * x**3 * y**2

// PO_LINE;
  // PO_TRACE(" t.vertices = " << t.vertices);
  // PO_TRACE(" t.coefficients = " << t.coefficients);

  assert(t.vertices.size() == 8);
  assert((t.vertices[0] == po::trie::vertex{ 3, {1, 3}, 0}));
  assert((t.vertices[1] == po::trie::vertex{ 5, {2}   , 1}));
  assert((t.vertices[2] == po::trie::vertex{ 0, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[3] == po::trie::vertex{ 2, {4}   , 1}));
  assert((t.vertices[4] == po::trie::vertex{ 1, {}    , po::trie_constants::ABSENT}));
  assert((t.vertices[5] == po::trie::vertex{12, {6}   , 0}));
  assert((t.vertices[6] == po::trie::vertex{12, {7}   , 1}));
  assert((t.vertices[7] == po::trie::vertex{ 2, {}    , po::trie_constants::ABSENT}));

  assert((t.coefficients == (decltype(t.coefficients)){1.2, -0.33, 5.1}));
  assert(t.coefficient({3, 2}) == -.33);

  assert(t.npaths() == 3);
  assert(t.nterms() == 3);

  return t;
}