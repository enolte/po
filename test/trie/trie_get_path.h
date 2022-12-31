#include <iostream>
#include <cassert>
#include <vector>

#include "utils.h"
#include "../../ostream/vector_ostream.h"
#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_get_path.h"

using po::operator<<;

void empty_tree_rank2();
void empty_tree_rank4();
void nonempty_tree_partial_new_path();
void nonempty_tree_whole_new_path();
void nonempty_tree_extant_path();

void trie_get_path()
{
  empty_tree_rank2();
  empty_tree_rank4();
  nonempty_tree_partial_new_path();
  nonempty_tree_whole_new_path();
  nonempty_tree_extant_path();

  PO_LINE;
}

void nonempty_tree_extant_path()
{
  // PO_TRACE("--- Get extant path, test 5 ---------------------------------------------");
  std::vector<po::trie_vertex> vertices
  {
    {3, {1}},
    {5, {2}},
    {2, {3}},
    {4, {}},
  };

  const std::vector<po::trie_vertex> vertices_before = vertices;

  std::vector<std::size_t> roots{0};

  const auto [last_vertex, new_path] =
    po::trie_get_path(vertices, roots, po::exponents{3, 5, 2, 4});

// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);
  // PO_TRACE("roots = " << roots);

  assert(!new_path);
  PO_ASSERT(last_vertex == 3, last_vertex);

  assert(roots.size() == 1);
  assert(roots[0] == 0);

  assert(vertices == vertices_before);
}


void empty_tree_rank2()
{
  // PO_TRACE("--- Get/create path in empty trie, test 1 -------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;

  // PO_TRACE("inserting path " << (po::exponents{3, 5}));

  const auto [last_vertex, is_new_path] =
    po::trie_get_path(vertices, roots, po::exponents{3, 5});

// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);
  // PO_TRACE("roots = " << roots);

  assert(is_new_path);
  assert(last_vertex == 1);

  assert(vertices.size() == 2);
  assert(roots.size() == 1);

  assert(roots[0] == 0);

  assert(vertices[0].value == 3);
  PO_ASSERT(vertices[0].children == std::vector<std::size_t>{1}, vertices[0].children);

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{});
}


void empty_tree_rank4()
{
  // PO_TRACE("--- Get/create path in empty trie, test 2 -------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;

  const auto [last_vertex, is_new_path] =
    po::trie_get_path(vertices, roots, po::exponents{3, 5, 2, 4});

// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);
  // PO_TRACE("roots = " << roots);

  assert(is_new_path);
  assert(last_vertex == 3);

  assert(vertices.size() == 4);
  assert(roots.size() == 1);

  assert(roots[0] == 0);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});
  assert(vertices[0].level == 0);

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{2});
  assert(vertices[1].level == 1);

  assert(vertices[2].value == 2);
  assert(vertices[2].children == std::vector<std::size_t>{3});
  assert(vertices[2].level == 2);

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{});
  assert(vertices[3].level == 3);
}



void nonempty_tree_partial_new_path()
{
  // PO_TRACE("--- Get/create stem path in non-empty trie, test 3 ----------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;

  // Make a non-empty trie (verified in test 2)
  po::trie_get_path(vertices, roots, po::exponents{3, 5, 2, 4});

  // PO_TRACE("vertices before = " << vertices);
  // PO_TRACE("roots before = " << roots);

  // Add another (stem) path
  const auto [last_vertex, is_new_path] =
    po::trie_get_path(vertices, roots, po::exponents{3, 5, 1, 4});

  // PO_TRACE("vertices after = " << vertices);
  // PO_TRACE("roots after = " << roots);

  assert(is_new_path);
  assert(last_vertex == 5); // rank 4, 2 new vertices --> 6 vertices

  assert(vertices.size() == 6);
  assert(roots.size() == 1);

  assert(roots[0] == 0);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});
  assert(vertices[0].level == 0);

  assert(vertices[1].value == 5);
  assert((vertices[1].children == std::vector<std::size_t>{2, 4}));
  assert(vertices[1].level == 1);

  assert(vertices[2].value == 2);
  assert((vertices[2].children == std::vector<std::size_t>{3}));
  assert(vertices[2].level == 2);

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{});
  assert(vertices[3].level == 3);

  assert(vertices[4].value == 1);
  assert(vertices[4].children == std::vector<std::size_t>{5});
  assert(vertices[4].level == 2);

  assert(vertices[5].value == 4);
  assert(vertices[5].children == std::vector<std::size_t>{});
  assert(vertices[5].level == 3);
}



void nonempty_tree_whole_new_path()
{
  // PO_TRACE("--- Get/create new root with path in non-empty trie, test 4 -------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;

  // Make a non-empty trie (verified in test 2)
  po::trie_get_path(vertices, roots, po::exponents{3, 5, 2, 4});

  assert(vertices.size() == 4);
  assert(roots.size() == 1);

  // PO_TRACE("vertices before = " << vertices);
  // PO_TRACE("roots before = " << roots);

  // Add another (root) path
  const auto [last_vertex, is_new_path] =
    po::trie_get_path(vertices, roots, po::exponents{4, 5, 1, 4});

  const auto roots_after = roots;
  const auto vertices_after = vertices;

  // PO_TRACE("vertices after = " << vertices);
  // PO_TRACE("roots after = " << roots);

  assert(is_new_path);
  assert(last_vertex == 7); // rank 4, whole new path --> 8 vertices total

  assert(vertices.size() == 8);
  assert(roots.size() == 2);

  assert(roots[0] == 0);
  assert(roots[1] == 4);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{2});

  assert(vertices[2].value == 2);
  assert(vertices[2].children == std::vector<std::size_t>{3});

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{});

  assert(vertices[4].value == 4);
  assert(vertices[4].children == std::vector<std::size_t>{5});

  assert(vertices[5].value == 5);
  assert(vertices[5].children == std::vector<std::size_t>{6});

  assert(vertices[6].value == 1);
  assert(vertices[6].children == std::vector<std::size_t>{7});

  assert(vertices[7].value == 4);
  assert(vertices[7].children == std::vector<std::size_t>{});
}

