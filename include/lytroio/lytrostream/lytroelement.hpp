// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrostream/lytroelement.hpp
 *
 *  \brief Implementation of a component of a Lytro files (.LPF or .LFR formats)
 *
 * Once opened, Lytro files let appear different elements. This class describes
 * each of them as they follow the same structure with a version number, the data lenght,
 * a sha-1 and the data.
 *
 */
#pragma once

//
// Lytro file element

#ifndef LYTROELEMENT_H
#define LYTROELEMENT_H

#include <iostream>
#include <cstring>
#include <string>

namespace lytroio
{
class LytroElement
{
    public:
        enum LytroHeaderType : int8_t
        {
            NUL=-1,
            LFM=3,
            LFC=5,
            LFP=6
        };

        /**
         * @brief Construct a new LytroElement object
         *
         */
        LytroElement() = default;

        /**
         * @brief Construct a new LytroElement object of a certain type
         *
         * @param type type of the LytroElement object
         */
        LytroElement(enum LytroElement::LytroHeaderType type);

        /**
         * @brief Destroy the LytroElement object
         *
         */
        ~LytroElement();

        /**
         * @brief Getter of the current LytroElement object type
         *
         * @return const char *
         */
        const char* type() const;

        /**
         * @brief Getter of the current LytroElement object version
         * 
         * @return const int
         */
        const int version() const;

        /**
         * @brief Getter of the current LytroElement object length
         * 
         * @return const int
         */
        const int length() const;

        /**
         * @brief Getter of the current LytroElement object sha
         * 
         * @return const std::string
         */
        const std::string sha() const;

        /**
         * @brief Getter of the current LytroElement object data
         * 
         * @return const std::string
         */
        const std::string data() const;

        /**
         * @brief Set the version of the current LytroElement object
         * 
         * @param version a version number
         */
        void set_version(int &version);

        /**
         * @brief Set the length of the current LytroElement object
         * 
         * @param length a lenght
         */
        void set_length(int &length);

        /**
         * @brief Set the sha of the current LytroElement object
         * 
         * @param sha a sha
         */
        void set_sha(std::string sha);

        /**
         * @brief Set the data of the current LytroElement object
         * 
         * @param data a data
         */
        void set_data(std::string data);

        /**
         * @brief Override operator << to format LytroElement display
         *
         * @param os output stream
         * @param element LytroElement to display
        */
        friend std::ostream& operator << (std::ostream &os, const LytroElement &element);

    private:
        LytroHeaderType type_ = NUL;
        int version_ = -1;
        int length_ = -1;
        std::string sha_ = "";
        std::string data_ = "";
};

} // namespace lytroio

#endif // LYTROELEMENT_H