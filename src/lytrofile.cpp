// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytrofile.hpp>

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
    LytroParser parser = LytroParser();
    return parser.parse(filename_, this->elements_);
}
