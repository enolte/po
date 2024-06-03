#pragma once

#include <ios>
#include <iomanip>

#include "../../induction/ls/concepts.h"

namespace po_test
{
  static constexpr unsigned int width = 30;
  static constexpr unsigned int precision = 12;
  struct {} format;
  struct {} unformat;

  template<typename ostream>
  ostream& operator<<(ostream& o, decltype(unformat))
  {
    o << std::defaultfloat << std::noshowpos;
    return o;
  }

  template<typename ostream>
  ostream& operator<<(ostream& o, decltype(format))
  {
    const std::size_t default_precision = o.precision();
    o.precision(precision);
    o << std::fixed << std::showpos << std::setw(width);
    return o;
  }

  template<typename ostream, typename M>
    requires (po::matrix<M> || po::matrix_functor<M>)
  void write(ostream& o, M&& f, std::size_t nrows, std::size_t ncols)
  {
    if(ncols > 0)
    {
      for(auto r{0zu}; r < nrows; ++r)
      {
        for(auto c{0zu}; c < ncols - 1; ++c)
          if constexpr(po::matrix_functor<M>)
            o << format << f(r, c) << ", ";
          else
            o << format << f[r, c] << ", ";


        if constexpr(po::matrix_functor<M>)
          o << format << f(r, ncols - 1)
            << std::endl;
        else
          o << format << f[r, ncols - 1]
            << std::endl;
      }

      o << unformat;
    }
  }

  template<typename ostream, po::matrix M>
  ostream& operator<<(ostream& o, const M& m)
  {
// PO_LINE;
    write(o, m, m.nrows, m.ncols);
    return o;
  }


}