#include "../../trie/trie_vertex.h"
#include "../../ostream/trie_vertex_ostream.h"

#include <iostream>
#include <sstream>

void test_trie_vertex_ostream()
{
  {
    po::trie_vertex v{2, {0, 4, 3}};

    std::stringstream ss;
    ss << v << std::endl;

    std::cout << ss.str();
  }

  {
    po::trie_vertex v{2, {0, 4, 3}};

    std::stringstream ss;
    ss << v;

    std::cout << ss.str() << std::endl;
  }

  {
    po::trie_vertex v{2, {0, 4, 3}};

    std::stringstream ss;
    ::operator<<(ss, v);

    std::cout << ss.str() << std::endl;
  }
}