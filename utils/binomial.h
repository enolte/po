#ifndef PO_UTILS_BINOMIAL_H
#define PO_UTILS_BINOMIAL_H

#include <cstdint>

namespace po
{
  namespace utils
  {
    // Binomial coefficients
    constexpr std::size_t C(std::size_t n, std::size_t k)
    {
      if(k > n)
        return 0;
      else if(n == 0)
        return 1;
      else if(n == 1)
          return 1;
      else if(n == 2)
        switch(k)
        {
        case 0:
        case 2: return 1;
        case 1: return n;
        default:
          return 0;
        }
      else if(n == 3)
        switch(k)
        {
        case 0:
        case 3: return 1;
        case 1:
        case 2: return n;
        default:
          return 0;
        }
      else
      {
        if(k > n/2)
          k = n-k;

        switch(k)
        {
        case 0  : return 1;
        case 1  : return n;
        case 2  :
          if(n & 1) return ((n-1)/2) * n;
          else      return (n/2) * (n-1);

        case 3  :
          switch(n % 6)
          {
          case 0: return (n/6) * (n-1) * (n-2);
          case 1: return ((n-1)/6) * n * (n-2);
          case 2: return ((n-2)/6) * n * (n-1);
          case 3: return (n/3) * ((n-1)/2) * (n-2);
          case 4: return (n/2) * ((n-1)/3) * (n-2);
          case 5: return n * ((n-1)/2) * ((n-2)/3);
          }
        }

        return n * C(n-1, k-1) / k;
      }
    }

  }
}

#endif

