#ifndef PO_VALARRAY_OSTREAM_H
#define PO_VALARRAY_OSTREAM_H

#include <vector>

template<typename ostream, typename T>
ostream& operator<<(ostream& o, std::valarray<T> t)
{
  auto i{std::cbegin(t)};
  for(; std::next(i) != std::cend(t); ++i)
    o << *i << ", ";
  o << *i;
  return o;
}

#endif


