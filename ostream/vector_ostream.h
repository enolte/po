#ifndef PO_VECTOR_OSTREAM_H
#define PO_VECTOR_OSTREAM_H

#include <vector>

template<typename ostream, typename T>
ostream& operator<<(ostream& o, const std::vector<T>& t)
{
  if(t.size() > 0)
  {
    auto i{t.cbegin()};
    for(; std::next(i) != t.cend(); ++i)
      o << *i << ", ";
    o << *i;
    // for(const auto& ti : t)
      // o << ti << ", ";
  }

  return o;
}

#endif

