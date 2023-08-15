// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrostream/lytroparser.hpp
 *
 *  \brief Implementation of a parser for Lytro files (.LPF or .LFR formats)
 *
 * Opening a Lytro file in binary mode let appear some patterns that are used
 * to separate its contents in three categories : package, metadata and
 * component. This class is set to parse such files and create each element
 * with the corresponding data.
 *
 */

#pragma once

//
// Lytro file parser

#ifndef LYTROPARSER_H
#define LYTROPARSER_H

#include <lytroio/lytrostream/lytroelement.hpp>
#include <fstream>
#include <vector>

#define LYTRO_STEP 16
#define LYTRO_HEADER 8
#define LYTRO_VERSION 4
#define LYTRO_LENGTH 4
#define LYTRO_SHA1 45
#define LYTRO_SHA1_PADDING 35

namespace lytroio
{
class LytroParser
{
    public:
        /**
         * @brief Parse the Lytro file contents into a vector of LytroElement.
         *
         * @param filepath The filepath to the Lytro file to parse.
         * @param elements Pointer to a vector of LytroElement object contained in the file.
         * @return true if the file have been fully read, false otherwise.
         */
        static bool parse(std::string filepath, std::vector<LytroElement> *elements);
};
} // namespace lytroio

#endif // LYTROPARSER_H