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
#include <fstream>

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
        void decode(LytroElement *element, int element_idx);

    private:
        /**
         * @brief Decode data from LytroElement and save it as an image
         *
         * @param data Data from the LytroElement
         * @param filepath Filepath of the image to be saved
         */
        void decode_image(std::string filepath, std::string data, size_t begin, size_t end);

        /**
         * @brief Check if LytroElement's data contains json
         *
         * @param data Data to check
         * @return true if LytroElement's data contains json, false otherwise
         */
        bool contains_json(std::string data);

        /**
         * @brief Check if LytroElement's data contains jpeg and where
         *
         * @param data Data to check
         * @param begin Start of image
         * @param end End of image
         * @return true if LytroElement's data contains jpeg, false otherwire
         */
        bool contains_jpeg(std::string data, size_t &begin, size_t &end);
};
} // namespace lytroio

#endif // LYTRODECODER_H