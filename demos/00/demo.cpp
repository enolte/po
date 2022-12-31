#include "../../polynomial.h"
#include "../../ostream/polynomial_ostream.h"
#include <iostream>

int main()
{
  po::polynomial p{{2.3, {4, 2}}, {-3.07, {5, 3}}, {1.023, {5, 9}}};
  po::polynomial q{{1, {0, 1}}, {22.4, {3, 1}}, {-5.1, {7, 1}}};
  std::cout << "p = " << p << std::endl;
  std::cout << "q = " << q << std::endl;

  const auto y = q(3, 4);
  const auto error = (p*q + q*(q - p))(3, 4) - y*y;

  std::cout << "error = " << std::hexfloat << error << std::endl;
  return 0;
}

