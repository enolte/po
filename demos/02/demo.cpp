/*
To build from this file's directory:

$ g++ --std=c++23 demo.cpp
*/

#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include "../../induction/lagrange_basis.h"
#include <iostream>

#include <sstream>
#include <map>

void verify_separation_basis(const auto& basis);

// Set knots by rows
static constexpr double points[6][2]
{
  {0, 0},
  {0.5, 0.5},
  {1, 1},
  {1.5, 2},
  {2, 3},
  {1, 1.5}
};

int main()
{
  // Select knot points by column
  auto f = [](std::size_t r, std::size_t c) { return points[c][r]; };

  auto basis = po::lagrange_basis(f, 2, 2);
  verify_separation_basis(basis);

  return 0;
}

void verify_separation_basis(const auto& basis)
{
  std::size_t max_str_length{};
  std::size_t str_length[basis.size()];

  std::size_t i{};
  for(const po::polynomial& b : basis)
  {
    std::stringstream ss; ss << b;
    str_length[i] = ss.str().size();
    max_str_length = std::max(max_str_length, ss.str().size());
    ++i;
  }

  static constinit double ε = 0x1p-52;

  std::cout << std::format("{:>{}}", "basis polynomial", max_str_length/2)
            << std::format("{:>{}}", "error", 52)
            << std::endl;

  std::cout << std::format("{:─>{}}", ' ', max_str_length - 12)
            << std::format("{: >{}}", ' ', 20)
            << std::format("{:─>{}}", ' ', 18) << "  "
            << std::endl;

  double max_abs_error{-1.};
  i = {};
  for(const auto& b : basis)
  {
    std::cout << "basis[" << i << "] = " << b << std::endl;
    for(auto j{0zu}; j < basis.size(); ++j)
    {
      double y = b(points[j][0], points[j][1]);

      const double error = (i == j ? y - 1. : y);

      std::cout << "  "
                << std::format("b({:.2f}, {:.2f})",  points[j][0], points[j][1]) << " = "
                << std::format("{:>25}", y) << "   "
                << std::format("{:>35}", std::format("{:a}", error)) << " = "
                << std::format("{}ε", error/ε)
                << std::endl;

      max_abs_error = std::max(max_abs_error, error);
    }

    ++i;
  }
}