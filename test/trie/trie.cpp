#include "trie_ctor.h"
#include "trie_get_path.h"
#include "trie_longest_prefix.h"
#include "trie_insert.h"
#include "trie_find_coefficient.h"
#include "trie_remove.h"
#include "trie_nterms.h"
#include "trie_npaths.h"
#include "trie_scenario.h"
#include "trie_ostream.h"
#include "trie_paths_get_vertices.h"
#include "trie_path_index_iterator.h"
#include "trie_paths_iterator.h"
#include "trie_monomials_iterator.h"

int main()
{
  trie_ctor();
  trie_longest_prefix();
  trie_get_path();
  trie_insert();
  trie_find_coefficient();
  trie_remove();
  trie_nterms();
  trie_npaths();
  trie_scenario();
  trie_ostream();

  trie_paths_get_vertices();

  trie_path_index_iterator();
  trie_paths_iterator();
  trie_monomials_iterator();

  return 0;
}

