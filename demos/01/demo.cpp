// g++ --std=c++23 demo.cpp

#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include "../../induction/lagrange_basis.h"
#include <iostream>

int main()
{
  static constexpr double points[3][2]
  {
    {0, 0},
    {1, 1},
    {2, 3},
  };

  // Select knot points by column
  auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

  auto basis = po::lagrange_basis(f, 2, 1);

  for(auto i{0zu}; i < basis.size(); ++i)
    std::cout << "basis[" << i << "] = " << basis[i] << std::endl;

  return 0;
}

