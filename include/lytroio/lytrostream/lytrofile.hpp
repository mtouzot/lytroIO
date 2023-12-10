// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrostream/lytrofile.hpp
 *
 *  \brief Implementation of a structure corresponding a Lytro files (.LPF or
 * .LFR formats)
 *
 * A Lytro file contains various elements (package, metadata, components). This
 * class acts like the
 *
 */

#pragma once

//
// Lytro file structure

#ifndef LYTROFILE_H
#define LYTROFILE_H

#include <fstream>
#include <iterator>
#include <lytroio/lytrostream/lytrodecoder.hpp>
#include <lytroio/lytrostream/lytroelement.hpp>
#include <vector>

#define LYTRO_STEP 16
#define LYTRO_HEADER 8
#define LYTRO_VERSION 4
#define LYTRO_LENGTH 4
#define LYTRO_SHA1 45
#define LYTRO_SHA1_PADDING 35

namespace lytroio
{
class LytroFile
{
public:
  // Custom LytroFile Iterator
  /**
   * @brief ForwardIterator to LytroElement type
   */
  struct LytroIterator
  {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = LytroElement;
    using pointer = LytroElement *;
    using reference = LytroElement &;

    LytroIterator (pointer ptr) : m_ptr (ptr){};

    reference
    operator* () const
    {
      return *m_ptr;
    }
    pointer
    operator->()
    {
      return m_ptr;
    }
    LytroIterator &
    operator++ ()
    {
      m_ptr++;
      return *this;
    }
    LytroIterator
    operator++ (int)
    {
      LytroIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool
    operator== (const LytroIterator &a, const LytroIterator &b)
    {
      return a.m_ptr == b.m_ptr;
    };
    friend bool
    operator!= (const LytroIterator &a, const LytroIterator &b)
    {
      return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
  };

  /**
   * @brief returns an iterator to the beginning
   *
   * @return LytroIterator to the first element
   */
  LytroIterator
  begin ()
  {
    return LytroIterator (&elements_->front ());
  }

  /**
   * @brief returns an iterator to the end
   *
   * @return LytroIterator to the element following the last element
   */
  LytroIterator
  end ()
  {
    return ++(LytroIterator (&elements_->back ()));
  }

  /**
   * @brief Construct a new Lytro File object
   *
   * @param filename filename of the lytro file to process
   */
  LytroFile (std::string filename);

  /**
   * @brief Destroy the Lytro File object
   *
   */
  ~LytroFile ();

  /**
   * @brief Read the file content
   *
   * @return true if the file is correctly read
   * @return false if there is an error during the reading
   */
  bool read ();

  /**
   * @brief Call a LytroDecoder to decode the data of each LytroElement
   * contained in the LytroFile
   */
  void decode ();

  /**
   * @brief Save the data of each LytroElement contained in the LytroFile in
   * its correct output file
   */
  void save ();

private:
  std::string filename_;
  std::vector<LytroElement> *elements_;
  LytroDecoder *ldecoder_;
};
} // namespace lytroio

#endif // LYTROFILE_H