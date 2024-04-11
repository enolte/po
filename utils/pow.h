#ifndef PO_UTILS_POW_H
#define PO_UTILS_POW_H

namespace po
{
  namespace utils
  {
    constexpr double pow(double a, int n)
    {
      if(n < 8)
        return
          (n == 0) * 1. +
          (n == 1) * a +
          (n == 2) * a*a +
          (n == 3) * a*a*a +
          (n == 4) * a*a*a*a +
          (n == 5) * a*a*a*a*a +
          (n == 6) * a*a*a*a*a*a +
          (n == 7) * a*a*a*a*a*a*a;
      else
      {
        const double a0 = pow(a, n>>3);
        return
          (n%8 == 0) * a0*a0*a0*a0*a0*a0*a0*a0 +
          (n%8 == 1) * a0*a0*a0*a0*a0*a0*a0*a0 * a +
          (n%8 == 2) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a +
          (n%8 == 3) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a +
          (n%8 == 4) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a +
          (n%8 == 5) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a +
          (n%8 == 6) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a*a +
          (n%8 == 7) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a*a*a;
      }
    }

#if 0
    consteval double pow_ce(double a, int n)
    {
      double r{1};
      while(n)
      {
        if(n & 1) r *= a;
        n >>= 1;
        a *= a;
      }

      return r;
    }

    constexpr double pow_c(double a, int n)
    {
      if(n < 8)
        return
          (n == 0) * 1. +
          (n == 1) * a +
          (n == 2) * a*a +
          (n == 3) * a*a*a +
          (n == 4) * a*a*a*a +
          (n == 5) * a*a*a*a*a +
          (n == 6) * a*a*a*a*a*a +
          (n == 7) * a*a*a*a*a*a*a;
      else
      {
        const double a0 = pow(a, n/8);
        return
          (n%8 == 0) * a0*a0*a0*a0*a0*a0*a0*a0 +
          (n%8 == 1) * a0*a0*a0*a0*a0*a0*a0*a0 * a +
          (n%8 == 2) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a +
          (n%8 == 3) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a +
          (n%8 == 4) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a +
          (n%8 == 5) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a +
          (n%8 == 6) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a*a +
          (n%8 == 7) * a0*a0*a0*a0*a0*a0*a0*a0 * a*a*a*a*a*a*a;
      }
    }

    constexpr double pow(double a, int n)
    {
      // TODO (g++ 11.2.0): Available only in g++ 12 series
      if consteval
      {
        pow_ce(a, n)
      }
      else
      {
        pow_c(a, n);
      }
    }
  }
#endif
  }

}


#endif


