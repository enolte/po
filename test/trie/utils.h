#ifndef PO_TRIE_TEST_UTILS_H
#define PO_TRIE_TEST_UTILS_H

#include <algorithm>
#include <list>
#include <sstream>
#include <iomanip>

#include "../../ostream/vector_ostream.h"
#include "../../ostream/valarray_ostream.h"
#include "../../ostream/trie_vertex_ostream.h"

#include "../../storage/trie/trie.h"

using po::operator<<;

inline bool unique_coefficient_offsets(const std::vector<po::trie_vertex>& vertices)
{
  std::vector<std::size_t> offsets;
  for(const auto& v : vertices)
  {
    if(v.children.size() == 0)
      offsets.push_back(v.value);
  }

  const std::size_t num_found = offsets.size();

  std::ranges::sort(offsets);
  std::ranges::unique(offsets);

  return offsets.size() == num_found && offsets.front() == 0 && offsets.back() < offsets.size();
}


// TODO iterative instead of recursive
void get_paths(const po::trie& t, std::size_t root, std::string&& s, std::stringstream& ss)
{
  if(t.vertices[root].children.empty())
  {
    s += std::to_string(root) + "  --->  " + std::to_string(t.coefficients[t.vertices[root].value]);
    ss << s << std::endl;
  }
  else
  {
    if(t.vertices[root].children.size() == 1 && t.vertices[t.vertices[root].children[0]].children.size() == 0)
    {
      for(std::size_t child : t.vertices[root].children)
      {
        get_paths(t, child, s + std::to_string(root) + " : ", ss);
      }
    }
    else
    {
      for(std::size_t child : t.vertices[root].children)
      {
        get_paths(t, child, s + std::to_string(root) + ", ", ss);
      }
    }
  }
}

void get_paths(const po::trie& t, std::stringstream& ss)
{
  for(std::size_t root : t.roots)
  {
    get_paths(t, root, {}, ss);
  }
}

// TODO iterative instead of recursive
void get_paths(const po::trie& t, std::size_t root, std::vector<std::size_t>&& path, std::list<std::vector<std::size_t>>& paths)
{
  if(t.vertices[root].children.size() == 1 && t.vertices[t.vertices[root].children[0]].children.size() == 0)
  {
    paths.push_back(path);
  }
  else
  {
    for(std::size_t child : t.vertices[root].children)
    {
      path.push_back(child);
      get_paths(t, child, std::move(path), paths);
      path.pop_back();
    }
  }
}

void get_paths(const po::trie& t, std::list<std::vector<std::size_t>>& paths)
{
  for(std::size_t root : t.roots)
  {
    get_paths(t, root, {}, paths);
  }
}


// TODO Test with this.
// TODO iterative instead of recursive
void get_exponents(const po::trie& t, std::size_t root, po::exponents exponents, std::list<po::exponents>& list)
{
  exponents.resize(exponents.size() + 1);
  exponents[exponents.size() - 1] = root;

  if(t.vertices[root].children.empty())
  {
    list.push_back(exponents);
  }
  else
  {
    for(std::size_t child : t.vertices[root].children)
    {
      get_exponents(t, child, exponents, list);
    }
  }
}

void get_exponents(const po::trie& t, std::list<po::exponents>& list)
{
  for(std::size_t root : t.roots)
  {
    get_exponents(t, root, {}, list);
  }
}



void write_trie_data_to_stdout(const po::trie& t)
{
  std::cout << " ** vertices" << std::endl;
  for(std::size_t i{0zu}; i < t.vertices.size(); ++i)
  {
    std::cout << "[" << std::right << std::setw(3) << i << "]     " << t.vertices[i] << std::endl;
  }
  std::cout << " **" << std::endl;

  std::cout << " ** roots" << std::endl
            << t.roots << std::endl
            << " **" << std::endl;

  std::cout << " ** coefficients" << std::endl;
  for(std::size_t i{0zu}; i < t.coefficients.size(); ++i)
  {
    std::cout << "[" << std::right << std::setw(3) << i << "]     " << t.coefficients[i] << std::endl;
  }
  std::cout << " **" << std::endl;

  std::stringstream ss;
  get_paths(t, ss);
  std::cout << " ** paths" << std::endl
            << ss.str() << std::endl
            << " **" << std::endl;
}


std::size_t get_vertex_offset(
  std::size_t level,
  const std::vector<std::size_t>& index,
  const po::trie& t)
{
  std::size_t n = t.roots[index[0]];
  std::size_t k = 0;
  while(k != level)
  {
    n = t.vertices[n].children[index[k]];
    ++k;
  }

  return index[k];
}


const po::trie::vertex& get_vertex_at_level(
  std::size_t level,
  std::size_t& offset,
  const std::vector<std::size_t>& index,
  const po::trie& t)
{
  std::size_t n = t.roots[index[0]];
  std::size_t k = 0;
  while(k != level)
  {
    n = t.vertices[n].children[index[k]];
    ++k;
  }

  offset = n;

  return t.vertices[n];
}

/*
std::size_t get_level(
  const po::trie::vertex& v,
  const std::vector<std::size_t>& index,
  const po::trie& t)
{
  std::size_t offset = t.roots[index[0]];

  std::size_t level = 0;
  while(v != t.vertices[offset])
  {
    offset = t.vertices[offset].children[index[level]];
    ++level;
  }

  if(v != t.vertices[offset])
    return trie_constants::ABSENT;
  else
    return offset;
}
*/

inline bool is_exponent_vertex(const po::trie_vertex& v)
{
  return v.children.size() > 0;
}

inline bool is_coefficient_vertex(const po::trie_vertex& v)
{
  return v.children.size() == 0;
}

inline bool is_terminal_vertex(const po::trie_vertex& v, const po::trie& t)
{
  return v.children.size() == 1 && is_coefficient_vertex(t.vertices[v.children[0]]);
}



#endif

