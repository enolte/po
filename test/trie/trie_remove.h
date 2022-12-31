#include <iostream>
#include <cassert>
#include <vector>

#include "utils.h"

#include "../../ostream/trie_vertex_ostream.h"
#include "../../test/macros.h"

#include "../../storage/trie/trie_remove.h"

void trie_remove_path_from_nonempty();
void trie_remove_nonexistent_path_from_nonempty();
void trie_remove_from_empty();

void trie_remove()
{
  trie_remove_path_from_nonempty();
  trie_remove_nonexistent_path_from_nonempty();
  trie_remove_from_empty();

  PO_LINE;
}

std::vector<po::trie_vertex> get_test_vertices_rank3();
std::vector<std::size_t> get_test_roots_rank3();


void trie_remove_nonexistent_path_from_nonempty()
{
  const std::vector<std::size_t> roots = get_test_roots_rank3();
  const std::vector<po::trie_vertex> vertices = get_test_vertices_rank3();

  std::vector<po::scalar_type> coefficients
  {
    0.6,
    1.6,
    2.6,
    3.6,
    4.6,
  };

  const std::vector<std::size_t> roots_before = roots;
  const std::vector<po::trie_vertex> vertices_before = vertices;
  const std::vector<po::scalar_type> coefficients_before = coefficients;

  const bool removed = po::trie_remove(vertices, roots, coefficients, {3, 4, 3, 1});
  assert(!removed);
  assert(roots == roots_before);
  assert(vertices == vertices_before);
  assert(coefficients == coefficients_before);
}


void trie_remove_path_from_nonempty()
{
  const std::vector<std::size_t> roots = get_test_roots_rank3();
  const std::vector<po::trie_vertex> vertices = get_test_vertices_rank3();

  std::vector<po::scalar_type> coefficients
  {
    0.6,
    1.6,
    2.6,
    3.6,
    4.6,
  };

  const std::vector<std::size_t> roots_before = roots;
  const std::vector<po::trie_vertex> vertices_before = vertices;
  const std::vector<po::scalar_type> coefficients_before = coefficients;

  const bool removed = po::trie_remove(vertices, roots, coefficients, {3, 4, 3, 2});
  assert(removed);
  assert(roots == roots_before);
  assert(vertices == vertices_before);
  assert(coefficients != coefficients_before);

  assert(coefficients[0] == coefficients_before[0]);
  assert(coefficients[1] == coefficients_before[1]);
  assert(coefficients[2] != coefficients_before[2]);
  assert(coefficients[3] == coefficients_before[3]);
  assert(coefficients[4] == coefficients_before[4]);

  assert(coefficients[2] != coefficients[2]);
}

void trie_remove_from_empty()
{
  const std::vector<std::size_t> roots;
  const std::vector<po::trie_vertex> vertices;
  std::vector<po::scalar_type> coefficients;

  const bool removed = po::trie_remove(vertices, roots, coefficients, {3, 2, 4});
  assert(!removed);
}




std::vector<po::trie_vertex> get_test_vertices_rank3()
{

/*

                                      (trie)
level                                    │
                           ┌─────────────┴─────────────┐
  0                        3[0]                        7[11]
                    ┌──────┴──────┐                    │
  1                 5[1]          4[7]                 4[12]
                    │             │             ┌──────┴──────┐
  2                 2[2]          3[8]          3[13]         1[17]
             ┌──────┴──────┐      │             │             │
  3          4[3]          1[5]   2[9]          6[14]         6[18]
             |             |      |             │             │
             0[4]          1[6]   2[10]         3[15]         4[19]



  paths        coefficient offsets

    3 5 2 4      0
    3 5 2 1      1
    3 4 3 2      2
    7 4 3 6      3
    7 1 3 6      4

*/

  return
  {
    {3, {1, 7}},    // [ 0]
    {5, {2}},       // [ 1]
    {2, {3, 5}},    // [ 2]
    {4, {4}},       // [ 3]
    {0, {}},        // [ 4] coefficient offset
    {1, {6}},       // [ 5]
    {1, {}},        // [ 6] coefficient offset
    {4, {8}},       // [ 7]
    {3, {9}},       // [ 8]
    {2, {10}},      // [ 9]
    {2, {}},        // [10] coefficient offset
    {7, {12, 16}},  // [11]
    {4, {13}},      // [12]
    {3, {14}},      // [13]
    {6, {15}},      // [14]
    {3, {}},        // [15] coefficient offset
    {1, {17}},      // [16]
    {3, {18}},      // [17]
    {6, {19}},      // [18]
    {4, {}},        // [19] coefficient offset
  };
}

/*
 * Roots for the above tree
 */
std::vector<std::size_t> get_test_roots_rank3()
{
  return
  {
    0, 11
  };
}

