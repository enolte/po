#ifndef PO_INDUCTION_EXPONENTS_SEQUENCE_H
#define PO_INDUCTION_EXPONENTS_SEQUENCE_H

#include <valarray>
#include <numeric>
#include <algorithm>

#include "../../utils/binomial.h"

namespace po
{
  /*
   * An ordered sequence of exponents of fixed length, generated in place
   */
  struct exponents_sequence
  {
    bool end;
    std::valarray<std::size_t> exponents;

    /*
     * Construct a exponents_sequence in either of the `begin` state or `end` state
     *
     * `npoints` : number of points in the set from which a multi-selection is chosen
     * `length` : sum of the exponents in a `multi::index` instance
     */
    exponents_sequence(std::size_t _npoints, std::size_t _length, bool _end):
      exponents(0zu, _npoints),
      end{_end}
    {
      if(_npoints > 0) [[likely]]
      {
        if(!end)
          exponents[0] = _length;
        else
          exponents[exponents.size() - 1] = _length;
      }
    }

    /*
     * Construct a exponents_sequence from a list of entries
     */
    exponents_sequence(std::initializer_list<std::size_t>&& _ilist):
      exponents{std::move(_ilist)},
      end{false}
    {}

    /*
     * Construct a exponents_sequence in the `begin` state
     *
     * `npoints` : number of points in the set from which a multi-selection is chosen
     * `length` : sum of the exponents in a `multi::index` instance
     */
    exponents_sequence(std::size_t _npoints, std::size_t _length):
      exponents_sequence(_npoints, _length, false)
    {}

    /*
     * assumes: i < exponents.size()
     */
    std::size_t operator[](std::size_t i) const
    {
      return exponents[i];
    }

    /*
     * Advance this to the next exponents_sequence in iteration order
     */
    exponents_sequence& operator++()
    {
      end = next(exponents, length());
      return *this;
    }

    /*
     * The number of non-zero exponents of this instance at time of call
     */
    std::size_t nnz() const
    {
      return std::ranges::count_if(exponents, [](std::size_t j){ return j != 0; });
    }

    /*
     * The number of points indexed by this instance
     */
    std::size_t npoints() const
    {
      return exponents.size();
    }

    /*
     * The sum of exponents in this exponents_sequence
     */
    std::size_t length() const
    {
      if (exponents.size() == 0) [[unlikely]]
        return 0;

      return exponents.sum();
    }

    /*
     * return: the number of multiindices of this length with this many points
     */
    std::size_t count() const
    {
      if(npoints() + length() == 0) [[unlikely]]
        return 1;

      return utils::C(npoints() + length() - 1, length());
    }

    /*
     * Advance the exponents_sequence exponents to the next exponents_sequence in iteration order
     *
     * return: true iff the exponents_sequence is in `end` state at exit
     */
    static bool next(std::valarray<std::size_t>& exponents, std::size_t length)
    {
      const std::size_t n = exponents.size();

      if (n == 0) [[unlikely]]
        return true;

      for(std::size_t i = 0; i < n - 1; ++i)
      {
        if(exponents[i] > 0)
        {
          exponents[i]--;
          exponents[i+1]++;
          std::fill_n(std::begin(exponents), i+1, 0);

          // N.B. Tried accumulate, reduce, and ranges::fold_left_first. accumulate was fastest (expected).
          exponents[0] = length - std::accumulate(std::cbegin(exponents) + (i+1), std::cend(exponents), 0);

          return false;
        }
      }

      // If we get to here without executing the `if` clause above, `exponents`@entry is in `end` state.
      return true;
    }
  };

  template<typename ostream>
  ostream& operator<<(ostream& o, const po::exponents_sequence& ii)
  {
    o << '[';
    if(ii.npoints() > 0)
    {
      for(std::size_t i = 0; i < ii.npoints() - 1 ; ++i)
        o << ii[i] << ", ";

      o << ii[ii.npoints() - 1];
    }
    o << ']';

    return o;
  }
}

#endif


