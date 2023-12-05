// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)

#include "utils.hpp"
#include <lytroio/lytrostream/lytrodecoder.hpp>
#include <nlohmann/json.hpp>

namespace lytroio
{
using json = nlohmann::json;

std::vector<LytroElement> *
LytroDecoder::read (std::string data_buffer,
                    std::filesystem::path data_filepath)
{
  std::vector<LytroElement> *elements = new std::vector<LytroElement> ();
  size_t position_in_buffer = 0;

  while (position_in_buffer < data_buffer.length ())
    {
      elements->push_back (
          read_next_element (data_buffer, position_in_buffer, data_filepath));
    }
  return elements;
}

LytroElement
LytroDecoder::read_next_element (std::string data_buffer, size_t &pos,
                                 std::filesystem::path data_filepath)
{
  LytroElement element = LytroElement ();
  element.set_parent_filepath (data_filepath);

  std::string header_type = data_buffer.substr (pos, LYTRO_HEADER);
  pos += LYTRO_HEADER;
  element.set_type (allowed_headers_[header_type]);

  // version
  std::string version_str = data_buffer.substr (pos, LYTRO_VERSION);
  int version = bitsToInt (&version_str[0], LYTRO_VERSION);
  pos += LYTRO_VERSION;
  element.set_version (version);

  // lenght
  std::string length_str = data_buffer.substr (pos, LYTRO_LENGTH);
  int length = bitsToInt (&length_str[0], LYTRO_LENGTH);
  pos += LYTRO_LENGTH;
  element.set_length (length);

  if (length > 0)
    {
      // SHA-1
      std::string sha_str = data_buffer.substr (pos, LYTRO_SHA1);
      pos += LYTRO_SHA1 + LYTRO_SHA1_PADDING;
      element.set_sha (sha_str);

      // data
      std::string data_str = data_buffer.substr (pos, element.length ());
      pos += length + missingBits (length, LYTRO_STEP);
      element.set_data (data_str);
    }

  return element;
}

void
LytroDecoder::decode (LytroElement *element, int element_idx)
{
  if (!element->data ().empty ())
    {
      size_t begin = 0;
      size_t end = 0;
      std::filesystem::path filepath = "";
      if (contains_json (element->data ()))
        {
          std::cout << "LytroElement can be decoded as JSON" << std::endl;
          filepath = pathstem (element->parent_filepath ())
                         .concat ("_metadata_" + std::to_string (element_idx)
                                  + ".json");
        }
      else if (contains_jpeg (element->data (), begin, end))
        {
          std::cout << "LytroElement can be decoded as JPEG" << std::endl;
          filepath = pathstem (element->parent_filepath ())
                         .concat ("image_" + std::to_string (element_idx)
                                  + ".jpeg");
        }
      else if (contains_png (element->data (), begin))
        {
          std::cout << "LytroElement can be decoded as PNG" << std::endl;
          filepath
              = pathstem (element->parent_filepath ())
                    .concat ("image_" + std::to_string (element_idx) + ".png");
        }
      else
        {
          std::cout << "TODO" << std::endl;
        }

      element->set_filepath (filepath);
    }
  else
    {
      std::cout << "LytroElement contains no data" << std::endl;
    }
}

bool
LytroDecoder::contains_json (std::string data)
{
  return json::accept (data);
}

bool
LytroDecoder::contains_jpeg (std::string data, size_t &begin, size_t &end)
{
  begin = string_to_hex (data).find (
      "FFD8"); // JFIF file structure Start of Image
  end = string_to_hex (data).find ("FFD9"); // JFIF file structure End of Image
  int middle = string_to_hex (data).find (
      "FFDA"); // JFIF file structure Start of Scan

  if ((begin != std::string::npos) && (end != std::string::npos)
      && ((begin < middle) && (middle < end)))
    {
      end += 4;
      return true;
    }
  return false;
}

bool
LytroDecoder::contains_png (std::string data, size_t &begin)
{
  begin = string_to_hex (data).find (
      "89504E470D0A1A0A"); // PNG hexadecimal file signature

  return (begin != std::string::npos);
}
} // namespace lytroio