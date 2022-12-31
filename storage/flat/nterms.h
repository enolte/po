#ifndef PO_STORAGE_FLAT_NTERMS_H
#define PO_STORAGE_FLAT_NTERMS_H

namespace po
{
  inline namespace flat_model
  {
    static std::size_t nterms(const storage& terms)
    {
      return terms.size();
    }
  }
}

#endif


