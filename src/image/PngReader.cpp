//
// Created by Zaiyang Li on 12/02/2018.
//

#include "PngReader.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
namespace McRenderFace {
    Image McRenderFace::PngReader::read(const std::string &filePath) {
        IMG_Init(IMG_INIT_PNG);
        SDL_Surface* image = IMG_Load(filePath.c_str());
        if(!image) {
            std::cerr << "Error loading png file: " << filePath << endl;
            throw runtime_error("error loading png file: " + filePath);
        }
        int width = image->w;
        int height = image->h;
        long max = 1 << image->format->BitsPerPixel - 1;

        IMG_Quit();
        SDL_FreeSurface(image);
        return McRenderFace::Image(nullptr, 0, 0);
    }
}
