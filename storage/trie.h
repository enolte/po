#ifndef PO_STORAGE_TRIE_H
#define PO_STORAGE_TRIE_H

#include "trie/trie.h"


namespace po
{
  inline namespace trie_model
  {
    using storage = po::trie;
  }
}

#include "trie/find_coefficient.h"
#include "trie/nterms.h"
#include "trie/constant.h"
#include "trie/accumulate_add.h"
#include "trie/accumulate_mult.h"


#endif

