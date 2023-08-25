// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <nlohmann/json.hpp>
#include <lytroio/lytrostream/lytrodecoder.hpp>
#include "utils.hpp"

namespace lytroio
{
    using json = nlohmann::json;

    void LytroDecoder::decode(LytroElement *element)
    {
        if(!element->data().empty())
        {
            if (json::accept(element->data()))
            {
                std::cout << "LytroElement can be decoded as JSON" << std::endl;
            }
            else if(string_to_hex(element->data().substr(0, 4)).compare("FFD8FFE1") == 0)
            {
                std::cout << "LytroElement can be decoded as JPEG" << std::endl;
                this->decode_image(element);
            }
        }
        else
        {
            std::cout << "LytroElement contains no data" << std::endl;
        }
    }

    void LytroDecoder::decode_image(LytroElement *element)
    {
        std::cout << "Image data found in " << *element;
        std::ofstream image("depth_image.jpeg", std::ofstream::out | std::ofstream::binary);
        image << element->data();
        image.close();
    }
} // namespace lytroio