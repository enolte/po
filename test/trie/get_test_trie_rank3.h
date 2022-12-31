#pragma once

#include "../../storage/trie.h"

static po::trie get_test_trie_rank3()
{
/*

Construct the following forest (with the trie itself as the imputed root).
Each number in [] is the storage offset for a vertex object with the given value.

                               (trie)
level                             │
                        ┌─────────┴─────────┐
  0                     3[0]                7[11]      ← roots       ┐
               ┌────────┴────────┐          │                        │
  1            5[1]              3[8]       1[12]                    │ (values are exponents)
        ┌──────┼──────┐          │          │                        │
  2     1[2]   5[4]   2[6]       6[9]       1[13]      ← terminals   ┘
        │      │      │          │          │
        0[3]   1[5]   2[7]       3[10]      4[14]      ← leaves        (values are coefficient offsets)


  For path iteration, these are the child indices, in forward iteration order:

    0, 0, 0  ←  begin
    0, 0, 1
    0, 0, 2
    0, 1, 0
    1, 0, 0
                end

*/



  po::trie t{3};

  t.insert(3.51, {3, 5, 1}); // 3.51 * w**3 * x**5 * y
  t.insert(3.55, {3, 5, 5}); // 3.55 * w**3 * x**5 * y**5
  t.insert(3.52, {3, 5, 2}); // 3.52 * w**3 * x**5 * y**2
  t.insert(3.36, {3, 3, 6}); // 3.36 * w**3 * x**3 * y**6
  t.insert(7.11, {7, 1, 1}); // 7.11 * w**7 * x    * y

  return t;
}
