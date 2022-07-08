#include <cstdint>

template<typename ostream, typename T, std::size_t n>
ostream& operator<<(ostream& o, T t[n])
{
  for(auto i{0ull}; i != n - 1; ++i)
    o << t[i] << ", ";
  o << t[n-1];
  return o;
}