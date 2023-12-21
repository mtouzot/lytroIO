// Copyright (c) 2023-present, Martin TOUZOT & lytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)

#include <lytroIO/lytrostream/lytroelement.hpp>

namespace lytroIO
{
LytroElement::LytroElement (enum LytroElement::LytroElementType type)
    : type_ (type)
{
}

LytroElement::~LytroElement () {}

const char *
LytroElement::type () const
{
  switch (this->type_)
    {
    case LytroElement::LytroElementType::LFP:
      return "LFP";
    case LytroElement::LytroElementType::LFC:
      return "LFC";
    case LytroElement::LytroElementType::LFM:
      return "LFM";
    case LytroElement::LytroElementType::NUL:
    default:
      return "NUL";
    }
}

const int
LytroElement::version () const
{
  return this->version_;
}

const int
LytroElement::length () const
{
  return this->length_;
}

const std::string
LytroElement::sha () const
{
  return this->sha_;
}

const std::string
LytroElement::data () const
{
  return this->data_;
}

const std::filesystem::path
LytroElement::filepath () const
{
  return this->filepath_;
}

void
LytroElement::set_type (enum LytroElement::LytroElementType type)
{
  this->type_ = type;
}

void
LytroElement::set_version (int &version)
{
  this->version_ = version;
}

void
LytroElement::set_length (int &length)
{
  this->length_ = length;
}

void
LytroElement::set_sha (std::string sha)
{
  this->sha_ = sha;
}

void
LytroElement::set_data (std::string data)
{
  this->data_ = data;
}

void
LytroElement::set_filepath (std::filesystem::path filepath)
{
  if (this->filepath_.empty ())
    this->filepath_ = filepath;
  else
    {
      this->filepath_.replace_filename (filepath);
    }
}

bool
LytroElement::empty ()
{
  return (this->length_ == 0);
}

void
LytroElement::save ()
{
  std::ofstream file;
  file.open (this->filepath_, std::ios::binary);
  file << this->data_;
  file.close ();
  std::cout << "Element saved at " << this->filepath_ << std::endl;
}

std::ostream &
operator<< (std::ostream &os, const LytroElement &element)
{
  os << "LytroElement" << std::endl
     << "type : " << element.type () << " version : " << element.version ()
     << " length : " << element.length () << std::endl;
  if (!element.sha ().empty ())
    os << "sha-1 : " << element.sha () << std::endl;
  if (!element.filepath ().empty ())
    os << "filename :" << element.filepath () << std::endl;

  return os;
}
} // namespace lytroIO