#include <iostream>
#include <cassert>
#include <vector>

#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_insert.h"

using po::operator<<;

void trie_insert_path_to_empty_rank2();
void trie_insert_path_to_empty_rank4();
void trie_insert_new_path_to_nonempty();
void trie_insert_new_partial_path_to_nonempty();
void trie_insert_extant_path_to_nonempty();

void trie_insert()
{
  trie_insert_path_to_empty_rank2();
  trie_insert_path_to_empty_rank4();
  trie_insert_new_partial_path_to_nonempty();
  trie_insert_extant_path_to_nonempty();
  trie_insert_new_path_to_nonempty();

  PO_LINE;
}

void trie_insert_path_to_empty_rank2()
{
  // PO_TRACE("--- Insert into empty trie, test 1 -----------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 1., {3, 5});

  // PO_TRACE("vertices = " << vertices);
  // PO_TRACE("roots = " << roots);
  // PO_TRACE("coefficients = " << coefficients);

  PO_ASSERT(vertices.size() == 3, vertices.size());
  assert(roots.size() == 1);
  assert(coefficients.size() == 1);

  assert(coefficients[0] == 1.);
  assert(roots[0] == 0);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{2});

  assert(vertices[2].value == 0);
  assert(vertices[2].children == std::vector<std::size_t>{});
}

void trie_insert_path_to_empty_rank4()
{
  // PO_TRACE("--- Insert into empty trie, test 2 -----------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 1., {3, 5, 2, 4});

// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);
  // PO_TRACE("roots = " << roots);
  // PO_TRACE("coefficients = " << coefficients);

  assert(vertices.size() == 5);
  assert(roots.size() == 1);
  assert(coefficients.size() == 1);

  assert(coefficients[0] == 1.);
  assert(roots[0] == 0);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{2});

  assert(vertices[2].value == 2);
  assert(vertices[2].children == std::vector<std::size_t>{3});

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{4});

  assert(vertices[4].value == 0);
  assert(vertices[4].children == std::vector<std::size_t>{});
}

void trie_insert_new_partial_path_to_nonempty()
{
  // PO_TRACE("--- Insert into non-empty trie, test 3 -------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 11.2, {3, 5, 2, 4});

  const bool new_path = trie_insert(vertices, roots, coefficients, -11.2, {3, 5, 7, 12});
  assert(new_path);
  // PO_TRACE("vertices = " << vertices);
  // PO_TRACE("roots = " << roots);
  // PO_TRACE("coefficients = " << coefficients);

  PO_ASSERT(vertices.size() == 8, vertices.size());
  assert(roots.size() == 1);
  assert(coefficients.size() == 2);

  assert(coefficients[0] == 11.2);
  assert(coefficients[1] == -11.2);

  assert(vertices[0].value == 3);
  assert(vertices[0].children == std::vector<std::size_t>{1});

  assert(vertices[1].value == 5);
  assert((vertices[1].children == std::vector<std::size_t>{2, 5}));

  assert(vertices[2].value == 2);
  assert(vertices[2].children == std::vector<std::size_t>{3});

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{4});

  assert(vertices[4].value == 0); // coefficient offset
  assert(vertices[4].children == std::vector<std::size_t>{});

  assert(vertices[5].value == 7);
  assert(vertices[5].children == std::vector<std::size_t>{6});

  assert(vertices[6].value == 12);
  assert(vertices[6].children == std::vector<std::size_t>{7});

  assert(vertices[7].value == 1); // coefficient offset
  assert(vertices[7].children == std::vector<std::size_t>{});

  assert(coefficients[vertices[4].value] == 11.2);
  assert(coefficients[vertices[7].value] == -11.2);
}

void trie_insert_extant_path_to_nonempty()
{
  // PO_TRACE("--- Insert into a trie which already has the given path, test 4 ------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 11.2, {3, 5, 2, 4});
  trie_insert(vertices, roots, coefficients, 10.2, {3, 5, 1, 4});
  trie_insert(vertices, roots, coefficients,  9.2, {6, 5, 1, 4});
  trie_insert(vertices, roots, coefficients,  8.2, {6, 1, 1, 4});
  trie_insert(vertices, roots, coefficients,  7.2, {6, 1, 6, 4});

  assert(roots.size() == 2);
  assert(coefficients.size() == 5);
  assert(vertices.size() == 20);

  assert(coefficients[2] == 9.2);

  const bool new_path = trie_insert(vertices, roots, coefficients, -11.2, {6, 5, 1, 4});
  assert(!new_path);

  assert(roots.size() == 2);
  assert(coefficients.size() == 5);
  assert(vertices.size() == 20);

  assert(coefficients[2] == 9.2 - 11.2);

  PO_ASSERT((coefficients == decltype(coefficients){11.2, 10.2, 9.2 - 11.2, 8.2, 7.2}), coefficients);
}

void trie_insert_new_path_to_nonempty()
{
  // PO_TRACE("--- Insert into non-empty trie, test 3 -------------------------------");
  std::vector<po::trie_vertex> vertices;
  std::vector<std::size_t> roots;
  std::vector<po::scalar_type> coefficients;

  trie_insert(vertices, roots, coefficients, 11.2, {7, 5, 2, 4});
// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);

  trie_insert(vertices, roots, coefficients, 12.2, {7, 1, 1, 1});

  assert(roots.size() == 1);
  assert(roots[0] == 0);
  PO_ASSERT(vertices.size() == 7 + 2, vertices.size());
  assert(coefficients.size() == 2);

  const bool new_path = trie_insert(vertices, roots, coefficients, 13.2, {4, 5, 1, 8});
  assert(new_path);
// PO_LINE;
  // PO_TRACE(" vertices = " << vertices);
  // PO_TRACE("roots = " << roots);
  // PO_TRACE("coefficients = " << coefficients);

  PO_ASSERT(vertices.size() == 11 + 3, vertices.size());
  assert(roots.size() == 2);
  assert((roots == std::vector<std::size_t>{0, 9}));
  assert(coefficients.size() == 3);

  assert(coefficients[0] == 11.2);
  assert(coefficients[1] == 12.2);
  assert(coefficients[2] == 13.2);

  assert(vertices[0].value == 7);
  assert((vertices[0].children == std::vector<std::size_t>{1, 5}));

  assert(vertices[1].value == 5);
  assert(vertices[1].children == std::vector<std::size_t>{2});

  assert(vertices[2].value == 2);
  assert(vertices[2].children == std::vector<std::size_t>{3});

  assert(vertices[3].value == 4);
  assert(vertices[3].children == std::vector<std::size_t>{4});

  assert(vertices[4].value == 0); // coefficient offset
  assert(vertices[4].children == std::vector<std::size_t>{});
  assert(coefficients[vertices[4].value] == 11.2);

  assert(vertices[5].value == 1);
  assert(vertices[5].children == std::vector<std::size_t>{6});

  assert(vertices[6].value == 1);
  assert(vertices[6].children == std::vector<std::size_t>{7});

  assert(vertices[7].value == 1);
  assert(vertices[7].children == std::vector<std::size_t>{8});

  assert(vertices[8].value == 1); // coefficient offset
  assert(vertices[8].children == std::vector<std::size_t>{});
  assert(coefficients[vertices[7].value] == 12.2);

  assert(vertices[9].value == 4);
  assert(vertices[9].children == std::vector<std::size_t>{10});

  PO_ASSERT(vertices[10].value == 5, vertices[10]);
  assert(vertices[10].children == std::vector<std::size_t>{11});

  assert(vertices[11].value == 1);
  assert(vertices[11].children == std::vector<std::size_t>{12});

  assert(vertices[12].value == 8);
  assert(vertices[12].children == std::vector<std::size_t>{13});

  assert(vertices[13].value == 2); // coefficient offset
  assert(vertices[13].children == std::vector<std::size_t>{});
  assert(coefficients[vertices[13].value] == 13.2);
}
