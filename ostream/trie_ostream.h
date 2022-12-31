#ifndef PO_TRIE_OSTREAM_H
#define PO_TRIE_OSTREAM_H

#include "vector_ostream.h"
#include "trie_vertex_ostream.h"
#include "../storage/trie/trie.h"

namespace po
{
  template<typename ostream>
  ostream& operator<<(ostream& o, const po::trie& t)
  {
    o << '[' << t.vertices << ']';
    return o;
  }
}

#endif
