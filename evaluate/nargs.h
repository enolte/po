#ifndef PO_NARGS_H
#define PO_NARGS_H

namespace po
{
  struct nargs
  {
    const std::size_t value;

    constexpr operator std::size_t() { return value; }
  };

}

#endif


