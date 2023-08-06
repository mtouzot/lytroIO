// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#include <lytroio/lytrostream/lytrofile.hpp>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    // Check the number of parameters
    if(argc < 2) 
    {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " LYTRO_FILEPATH" << std::endl;
        return 1;
    }

    std::cout << "Decoding datas from " << argv[1] << std::endl;

    LytroFile lfile = LytroFile(argv[1]);
    
    if(lfile.read() == true)
    {
        std::cout << "Lytro filepath correctly read!" << std::endl;
        for(auto iter_element = lfile.begin(); iter_element != lfile.end(); ++iter_element)
        {
            std::cout << *iter_element << std::endl << std::endl;
        }
    }
    else
        std::cout << "Lytro filepath unreadable..." << std::endl;

    return 0;
}