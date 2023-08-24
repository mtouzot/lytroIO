// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)
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

#include <lytroio/lytrostream/lytroelement.hpp>
#include <vector>

namespace lytroio
{
class LytroDecoder
{
    public:
        /**
         * @brief Decode LytroElement data to human readable data
         *
         * @param element Pointer to LytroElement to decode
         */
        static void decode(LytroElement element);
};
} // namespace lytroio

#endif // LYTRODECODER_H