#ifndef PO_EXPONENTS_ISTREAM_H
#define PO_EXPONENTS_ISTREAM_H



namespace po
{
  /*
   * Deserialize a CSV sequence of exponent values into a po::exponents instance.
   * Processing halts at `]`, with `]` as the next character to be extracted.
   *
   * Ex. With the stream carat indicated by '^', if the input string is
   *
   *   "5, 2, 3, 4]"
   *    ^
   *
   * then the string is parsed into the exponent sequence
   *
   *    5, 2, 3, 4
   *
   * and at exit, the stream is
   *
   *   "5, 2, 3, 4]"
   *              ^
   *
   * with the indicated carat for the next character.
   *
   * assumes: the exponents sequence is terminated with ']'
   */
  template<typename istream>
  istream& operator>>(istream& i, exponents& x)
  {
    std::vector<exponent_type> v;
    exponent_type exponent;
    char next = -1;

    while(next != ']' && i.good())
    {
      i >> std::ws >> exponent >> std::ws;
      v.push_back(exponent);
      i >> std::ws >> next >> std::ws;
    }

    i.putback(next);

    std::size_t k = 0;
    x.resize(v.size());
    for(auto&& exponent : v)
      x[k++] = std::move(exponent);

    return i;
  }

}

#endif

