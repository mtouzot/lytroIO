// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrostream/lytrodecoder.hpp
 *
 *  \brief Implementation of a decoder for LytroElement
 *
 * Opening a Lytro file in binary mode let appear some patterns that are used
 * to separate its contents in three categories : package, metadata and
 * component. This class is set to decode such element in a human readable
 * data.
 *
 */

#pragma once

//
// LytroElement decoder

#ifndef LYTRODECODER_H
#define LYTRODECODER_H

#include <fstream>
#include <lytroio/lytrostream/lytroelement.hpp>
#include <map>
#include <vector>

#define LYTRO_STEP 16
#define LYTRO_HEADER 8
#define LYTRO_VERSION 4
#define LYTRO_LENGTH 4
#define LYTRO_SHA1 45
#define LYTRO_SHA1_PADDING 35

namespace lytroio
{
class LytroDecoder
{
  typedef std::map<std::string_view, LytroElement::LytroElementType>
      LytroHeaderType_t;

public:
  /**
   * @brief Read all buffer to construct a pointer to a vector of LytroElement
   *
   * @return a pointer to a vector of LytroElement
   */
  std::vector<LytroElement> *read (std::string data_buffer);

  /**
   * @brief Read the buffer from position indexed by pos to construct a
   * LytroElement
   *
   * @return a LytroElement
   */
  LytroElement read_next_element (std::string data_buffer, size_t &pos);

  /**
   * @brief Decode LytroElement data to human readable data
   *
   * @param element Pointer to LytroElement to decode
   */
  void decode (LytroElement *element, int element_idx);

private:
  /**
   * @brief Check if LytroElement's data contains json
   *
   * @param data Data to check
   * @return true if LytroElement's data contains json, false otherwise
   */
  bool contains_json (std::string data);

  /**
   * @brief Check if LytroElement's data contains jpeg and where
   *
   * @param data Data to check
   * @param begin Start of image
   * @param end End of image
   * @return true if LytroElement's data contains jpeg, false otherwire
   */
  bool contains_jpeg (std::string data, size_t &begin, size_t &end);

  /**
   * @brief Check if LytroElement's data contains png and where
   *
   * @param data Data to check
   * @param begin Start of image
   * @return true if LytroElement's data contains png, false otherwire
   */
  bool contains_png (std::string data, size_t &begin);

  LytroHeaderType_t allowed_headers_
      = { { "\x89\x4c\x46\x50\x0D\x0A\x1A\x0A",
            LytroElement::LytroElementType::LFP },
          { "\x89\x4c\x46\x43\x0D\x0A\x1A\x0A",
            LytroElement::LytroElementType::LFC },
          { "\x89\x4c\x46\x4D\x0D\x0A\x1A\x0A",
            LytroElement::LytroElementType::LFM } };
};
} // namespace lytroio

#endif // LYTRODECODER_H