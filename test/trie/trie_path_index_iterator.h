#include "trie_path_index_iterator_begin.h"
#include "trie_path_index_iterator_level_to_increment.h"
#include "trie_path_index_iterator_set_first_path.h"
#include "trie_path_index_iterator_next.h"
#include "trie_path_index_iterator_ctor.h"
#include "trie_path_index_iteration.h"

void trie_path_index_iterator()
{
  trie_path_index_iterator_begin();
  trie_path_index_iterator_level_to_increment();
  trie_path_index_iterator_set_first_path();
  trie_path_index_iterator_next();

  trie_path_index_iterator_ctor();
  trie_path_index_iteration();

  PO_LINE;
}

