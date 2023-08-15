// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytrostream/lytroparser.hpp>
#include "utils.hpp"

namespace lytroio
{
    bool LytroParser::parse(std::string filepath, std::vector<LytroElement> *elements)
    {
        std::string_view lfp_header{"\x89\x4c\x46\x50\x0D\x0A\x1A\x0A"};
        std::string_view lfc_header{"\x89\x4c\x46\x43\x0D\x0A\x1A\x0A"};
        std::string_view lfm_header{"\x89\x4c\x46\x4D\x0D\x0A\x1A\x0A"};

        std::ifstream file(filepath, std::ios::in | std::ios::binary | std::ios::ate);

        if (!file)
            return false;

        int current_position = 0;
        int len = file.tellg();

        while(current_position < len)
        {
            file.seekg(current_position, std::ios::beg);
            char data_buffer[LYTRO_HEADER];
            if(!file.read(data_buffer, sizeof(data_buffer)))
                return false;
        
            unsigned int cmp_lfp = std::abs(lfp_header.compare(0, lfp_header.length(), data_buffer, LYTRO_HEADER));
            unsigned int cmp_lfc = std::abs(lfc_header.compare(0, lfc_header.length(), data_buffer, LYTRO_HEADER));
            unsigned int cmp_lfm = std::abs(lfm_header.compare(0, lfm_header.length(), data_buffer, LYTRO_HEADER));
            uint8_t type = ((cmp_lfp << 0) + (cmp_lfc << 1) + (cmp_lfm << 2));

            if(cmp_lfp == 0 || cmp_lfm == 0 || cmp_lfc == 0)
            {
                    LytroElement element = LytroElement(static_cast<LytroElement::LytroHeaderType>(type));

                    current_position += LYTRO_HEADER;
                    file.seekg(current_position, std::ios::beg);
                    if(!file.read(data_buffer, sizeof(data_buffer)))
                        return false;

                    int version = bitsToInt(data_buffer, LYTRO_VERSION);
                    int length = bitsToInt(data_buffer, LYTRO_LENGTH, LYTRO_VERSION);
                    current_position += (LYTRO_VERSION + LYTRO_LENGTH);

                    element.set_version(version);
                    element.set_length(length);

                    if(length > 0)
                    {
                        file.seekg(current_position, std::ios::beg);
                        char sha[LYTRO_SHA1];
                        if(!file.read(sha, sizeof(sha)))
                            return false;

                        element.set_sha(sha, sizeof(sha));

                        current_position += LYTRO_SHA1 + LYTRO_SHA1_PADDING;

                        file.seekg(current_position, std::ios::beg);
                        size_t padded_length = length + missingBits(length, LYTRO_STEP);
                        char* data_buffer = (char*)malloc(sizeof(char) * length);
                        if(!file.read(data_buffer, length*sizeof(char)))
                            return false;

                        current_position += padded_length;

                        element.set_data(data_buffer, length);
                    }

                    elements->push_back(element);
            }
        }

        file.close();
        return true;
    }
} // namespace lytroio