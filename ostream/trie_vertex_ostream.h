#ifndef PO_TRIE_VERTEX_OSTREAM_H
#define PO_TRIE_VERTEX_OSTREAM_H

#include "vector_ostream.h"
#include "../storage/trie/trie_vertex.h"

namespace po
{
  template<typename ostream>
  ostream& operator<<(ostream& o, const po::trie_vertex& v)
  {
    o << '[' << v.value << " : " << v.children << ']';
    return o;
  }
}

#endif
