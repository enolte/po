#pragma once

#include "../../storage/trie.h"

static po::trie get_test_trie_rank7(std::size_t npaths = 100)
{
/*

Construct the following forest (with the trie itself as the imputed root).
Each number in [] is the storage offset for a vertex object with the given value.

This is for npaths = 5.


                              (trie)
level                            │
             ┌───────────────────┼────────────────┐
  0          0[0]                1[14]            2[28]    ← roots       ┐
             │                   │                │                      │
  1          1[1]                2[15]            3[29]                  │
        ┌────┴────┐         ┌────┴────┐           │                      │
  2     0[2]      1[8]      2[16]     3[22]       4[30]                  │
        │         │         │         │           │                      │
  3     1[3]      2[9]      3[17]     4[23]       5[31]                  │ (values are exponents)
        │         │         │         │           │                      │
  4     2[4]      3[10]     4[18]     5[24]       6[32]                  │
        │         │         │         │           │                      │
  5     0[5]      1[11]     2[19]     3[25]       4[33]                  │
        │         │         │         │           │                      │
  6     0[6]      2[12]     4[20]     6[26]       8[34]    ← terminals   ┘
        │         │         │         │           │
        0[7]      1[13]     2[21]     3[27]       4[35]    ← leaves        (values are coefficient offsets)

  For path iteration, these are the child indices, in forward iteration order:

    0, 1, 0, 1, 2, 0, 0  ← begin
    0, 1, 1, 2, 3, 1, 2
    1, 2, 2, 3, 4, 2, 4
    1, 2, 3, 4, 5, 3, 6
    2, 3, 4, 5, 6, 4, 8
                           end


index  vertex [value : children]

[ 0]   [0 : 1],
[ 1]   [1 : 2, 8],
[ 2]   [0 : 3],
[ 3]   [1 : 4],
[ 4]   [2 : 5],
[ 5]   [0 : 6],
[ 6]   [0 : 7],
[ 7]   [0 : ]       <-- coefficient offset
[ 8]   [1 : 9],
[ 9]   [2 : 10],
[10]   [3 : 11],
[11]   [1 : 12],
[12]   [2 : 13],
[13]   [1 : ],      <-- coefficient offset
[14]   [1 : 15],
[15]   [2 : 16, 22],
[16]   [2 : 17],
[17]   [3 : 18],
[18]   [4 : 19],
[19]   [2 : 20],
[20]   [4 : 21],
[21]   [2 : ],      <-- coefficient offset
[22]   [3 : 23],
[23]   [4 : 24],
[24]   [5 : 25],
[25]   [3 : 26],
[26]   [6 : 27],
[27]   [3 : ],      <-- coefficient offset
[28]   [2 : 29],
[29]   [3 : 30],
[30]   [4 : 31],
[31]   [5 : 32],
[32]   [6 : 33],
[33]   [4 : 34],
[34]   [8 : 35],
[35]   [4 : ]       <-- coefficient offset



insert
[0]  0, 1, 0, 1, 2, 0, 0
[1]  0, 1, 1, 2, 3, 1, 2
[2]  1, 2, 2, 3, 4, 2, 4
[3]  1, 2, 3, 4, 5, 3, 6
[4]  2, 3, 4, 5, 6, 4, 8

*/

  po::trie t{7};

  for(auto i{0zu}; i < npaths; ++i)
  {
    t.insert(-1. + 2.*i / npaths, {i/2, i/2 + 1, i, i + 1, i + 2, 2*i - i, 2*i});
  }

  return t;
}
