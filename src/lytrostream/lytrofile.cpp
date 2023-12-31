// Copyright (c) 2023-present, Martin TOUZOT & lytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)

#include "utils.hpp"
#include <lytroIO/lytrostream/lytrofile.hpp>

namespace lytroIO
{
LytroFile::LytroFile (std::string filename) : filename_ (filename)
{
  elements_ = new std::vector<LytroElement> ();
  ldecoder_ = new LytroDecoder ();
}

LytroFile::~LytroFile ()
{
  delete elements_;
  delete ldecoder_;
}

bool
LytroFile::read ()
{
  std::ifstream file (this->filename_,
                      std::ios::in | std::ios::binary | std::ios::ate);

  if (!file)
    return false;

  int current_position = 0;
  int len = file.tellg ();
  std::string data_buffer_temp (len, ' ');

  file.seekg (current_position, std::ios::beg);
  file.read (&data_buffer_temp[0], len);
  file.close ();

  this->elements_ = this->ldecoder_->read (data_buffer_temp);

  return (this->elements_->front ().type () == "LFP");
}

void
LytroFile::decode ()
{
  int element_idx = 0;
  for (auto iter_element = this->begin (); iter_element != this->end ();
       ++iter_element)
    {
      std::cout << std::endl
                << "Decoding [" << ++element_idx << "/"
                << this->elements_->size () << "] " << iter_element->type ()
                << std::endl;
      this->ldecoder_->decode (&*iter_element, element_idx);
      std::filesystem::path element_filepath
          = this->filename_.parent_path ().append (
              this->filename_.stem ().string ()
              + iter_element->filepath ().string ());
      iter_element->set_filepath (element_filepath);
      std::cout << std::endl;
    }
}

void
LytroFile::save ()
{
  for (auto iter_element = this->begin (); iter_element != this->end ();
       ++iter_element)
    {
      if (!iter_element->empty ())
        {
          std::ofstream output_file;
          output_file.open (iter_element->filepath (),
                            std::ios::out | std::ios::binary);
          output_file << iter_element->data ();
          output_file.close ();
        }
    }
}
} // namespace lytroIO