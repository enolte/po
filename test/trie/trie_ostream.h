#include <list>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

#include "../../storage/trie/trie.h"

#include "../../ostream/trie_ostream.h"
#include "../../test/macros.h"

#include "utils.h"

#include "get_test_trie_rank5.h"

void paths(const po::trie&);
void get_paths(const po::trie&, std::stringstream&);

void trie_ostream()
{
  const po::trie t = get_test_trie_rank5();

  std::stringstream ss;
  ss << t;

  const std::string s = ss.str();

  // spot tests
  PO_ASSERT(s.find("2 : 1, 6") != std::string::npos, s);
  PO_ASSERT(s.find("4 : 14, 27") != std::string::npos, s);

  // PO_TRACE("t = " << ss.str());

  // ss = {};
  // get_paths(t, ss);
  // PO_TRACE("paths(t) = " << ss.str());

  PO_LINE;
}

