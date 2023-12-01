// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)

#include "utils.hpp"
#include <lytroio\lytrostream\lytrodecoder.hpp>
#include <nlohmann\json.hpp>

namespace lytroio
{
using json = nlohmann::json;

void
LytroDecoder::decode (LytroElement *element, int element_idx)
{
  if (!element->data ().empty ())
    {
      size_t begin = 0;
      size_t end = 0;
      if (json::accept (element->data ()))
        {
          std::cout << "LytroElement can be decoded as JSON" << std::endl;
        }
      else if (contains_jpeg (element->data (), begin, end))
        {
          std::cout << "LytroElement can be decoded as JPEG" << std::endl;
          std::string filepath
              = "image_" + std::to_string (element_idx) + ".jpeg";
          decode_image (filepath, element->data (), begin, end);
        }
      else if (contains_png (element->data (), begin))
        {
          std::cout << "LytroElement can be decoded as PNG" << std::endl;
          std::string filepath
              = "image_" + std::to_string (element_idx) + ".png";
          decode_image (filepath, element->data (), begin, 0);
        }
      else
        {
          std::cout << "TODO" << std::endl;
        }
    }
  else
    {
      std::cout << "LytroElement contains no data" << std::endl;
    }
}

void
LytroDecoder::decode_image (std::string filepath, std::string data,
                            size_t begin, size_t end)
{
  std::ofstream image (filepath, std::ofstream::out | std::ofstream::binary);
  image << data;
  image.close ();
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