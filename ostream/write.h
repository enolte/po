#ifndef PO_OSTREAM_WRITE_H
#define PO_OSTREAM_WRITE_H

namespace po
{
  template<typename ostream, typename I>
  static ostream& write(ostream& o, I begin, I end)
  {
    if(begin != end)
    {
      for(; begin != std::prev(end); ++begin)
        o << *begin << ", ";
      o << *begin;
    }

    return o;
  }
}

#endif

