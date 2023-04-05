#ifndef PO_EXPONENTS_OSTREAM_H
#define PO_EXPONENTS_OSTREAM_H

namespace po
{
  template<typename ostream>
  ostream& operator<<(ostream& o, const exponents& x)
  {
    if(x.size() != 0)
    {
      for(auto i{0zu}; i < x.size() - 1; ++i)
        o.operator<<(x[i]) << ",";
      o.operator<<(x[x.size() - 1]);
    }

    return o;
  }
}

#endif


