#pragma once

#include "../../storage/trie.h"

static po::trie get_test_trie_rank5()
{
/*

Construct the following forest (with the trie itself as the imputed root).
Each number in [] is the storage offset for a vertex object with the given value.

                               (trie)
level                             │
               ┌──────────────────┴───────────────────┐
  0            2[0]                                   3[11]               ← roots       ┐
        ┌──────┴──────┐               ┌───────────────┼───────────┐                     │
  1     1[1]          2[6]            2[12]           1[17]       3[22]                 │
        │             │               │               │           │                     │
  2     4[2]          4[7]            4[13]           4[18]       4[23]                 │ (values are exponents)
        │             │        ┌──────┴──────┐        │           │                     │
  3     4[3]          4[8]     4[14]         5[27]    4[19]       4[24]                 │
        │             │        │             │        │           │                     │
  4     4[4]          4[9]     4[15]         4[28]    4[20]       4[25]   ← terminals   ┘
        │             │        │             │        │           │
        0[5]          1[10]    2[16]         5[29]    3[21]       4[26]   ← leaves        (values are coefficient offsets)

  For path iteration, these are the child indices, in forward iteration order:

    0, 0, 0, 0, 0  ←  begin
    0, 1, 0, 0, 0
    1, 0, 0, 0, 0
    1, 0, 0, 1, 0
    1, 1, 0, 0, 0
    1, 2, 0, 0, 0
                      end

*/



  po::trie t{5};

  t.insert(2.1444, {2, 1, 4, 4, 4});
  t.insert(2.2444, {2, 2, 4, 4, 4});
  t.insert(3.2444, {3, 2, 4, 4, 4});
  t.insert(3.1444, {3, 1, 4, 4, 4});
  t.insert(3.3444, {3, 3, 4, 4, 4});
  t.insert(3.2454, {3, 2, 4, 5, 4});

  return t;
}