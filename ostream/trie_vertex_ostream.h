#include "vector_ostream.h"
#include "../trie/trie_vertex.h"

template<typename ostream>
ostream& operator<<(ostream& o, const po::trie_vertex& v)
{
  o << '[' << v.value << " : " << v.children << ']';
  return o;
}

