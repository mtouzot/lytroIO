// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytrostream/lytrofile.hpp>

namespace lytroio
{
    LytroFile::LytroFile(std::string filename) : filename_(filename)
    {
        elements_ = new std::vector<LytroElement>();
    }

    LytroFile::~LytroFile()
    {
        delete elements_;
    }

    bool LytroFile::read()
    {
        return LytroParser::parse(filename_, this->elements_);
    }

    void LytroFile::decode()
    {
        for(auto iter_element = this->begin(); iter_element != this->end(); ++iter_element)
        {
            std::cout << std::endl << "Decoding " << iter_element->type() << std::endl;
            LytroParser::decode(*iter_element);
            std::cout << std::endl;
        }
    }
} // namespace lytroio