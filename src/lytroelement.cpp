// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytroelement.hpp>

LytroElement::LytroElement(enum LytroElement::LytroHeaderType type) : type_(type)
{

}

LytroElement::~LytroElement()
{

}

const char* LytroElement::type() const
{
    switch (this->type_)
    {
    case LytroElement::LytroHeaderType::LFP :
        return "LFP";
    case LytroElement::LytroHeaderType::LFC :
        return "LFC";
    case LytroElement::LytroHeaderType::LFM :
        return "LFM";
    case LytroElement::LytroHeaderType::NUL:
    default:
        return "NUL";
    }
}

const int LytroElement::version() const
{
    return this->version_;
}

const int LytroElement::length() const
{
    return this->length_;
}

const char* LytroElement::sha() const
{
    return this->sha_;
}

const char* LytroElement::data() const
{
    return this->data_;
}

void LytroElement::set_version(int &version)
{
    this->version_ = version;
}

void LytroElement::set_length(int &length)
{
    this->length_ = length;
}

void LytroElement::set_sha(char *sha, size_t sha_size)
{
    uint8_t offset = std::strlen("sha1-");
    this->sha_ = (char*)std::malloc((sha_size - offset) * sizeof(char));
    sha += offset;
    std::memcpy(this->sha_, sha, sha_size);
}

void LytroElement::set_data(char *data, size_t data_size)
{
    this->data_ = (char*)std::malloc(data_size * sizeof(char));
    std::memcpy(this->data_, data, data_size);
}

std::ostream & operator << (std::ostream& os, const LytroElement& element)
{
    os << "LytroElement" << std::endl << "type : " << element.type() << " version : " << element.version() << " length: " << element.length() << std::endl;
    if (element.sha() != nullptr)
        os << "sha-1 : " << element.sha() << std::endl;

    return os;
}