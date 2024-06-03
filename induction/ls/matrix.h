#ifndef PO_MATRIX_H
#define PO_MATRIX_H

#include <valarray>

namespace po
{
  namespace ls
  {
    // A simple dense matrix buffer
    struct matrix
    {
      using T = double;

      std::valarray<double> data;
      std::size_t ncols;
      std::size_t nrows;

      matrix(std::size_t _nrows, std::size_t _ncols):
        data(_nrows * _ncols),
        ncols{_ncols},
        nrows{_nrows}
      {}

      double& operator[](std::size_t r, std::size_t c)
      {
        return data[r*ncols + c];
      }

      double operator[](std::size_t r, std::size_t c) const
      {
        return data[r*ncols + c];
      }

      struct row_reference
      {
        const std::size_t r;
        std::valarray<double>& data;
        const std::size_t ncols;

        T& operator[](std::size_t c) &&      { return data[r*ncols + c]; }
        T operator[](std::size_t c) const && { return data[r*ncols + c]; }
      };

      constexpr row_reference operator[](std::size_t r) { return {r, data, ncols}; }

      struct const_row_reference
      {
        const std::size_t r;
        const std::valarray<double>& data;
        const std::size_t ncols;

        T operator[](std::size_t c) const && { return data[r*ncols + c]; }
      };

      constexpr const_row_reference operator[](std::size_t r) const { return {r, data, ncols}; }
    };
  }
}

#endif

