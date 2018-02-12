//
// Created by Zaiyang Li on 12/02/2018.
//

#ifndef RENDERER_IMAGE_HPP
#define RENDERER_IMAGE_HPP

#include <glm/glm.hpp>
#include <memory>

namespace McRenderFace {
    using namespace glm;
    using namespace std;
    class Image {
    private:
        int _width;
        int _height;
        shared_ptr <vec3> image_data;
    public:
        Image(vec3* imageIn, int widthIn, int heightIn)
                : image_data(imageIn, std::default_delete<vec3[]>()), _width{widthIn}, _height{heightIn}
        { }
        int width() const { return _width; }
        int height() const { return _height; }
        vec3& operator()(int x, int y){ return (*image_data); }
        vec3* data() { return image_data.get(); }
    };
}


#endif //RENDERER_IMAGE_HPP
