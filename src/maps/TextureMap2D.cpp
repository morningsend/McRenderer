//
// Created by Zaiyang Li on 24/04/2018.
//

#include "TextureMap2D.hpp"

namespace McRenderFace {
    using namespace cv;
    void TextureMap2D::load(const std::string &path) {
        Mat texture;
        int cvColourFormat = CV_8UC3;
        size_t extensionPos = path.find_last_of(".");
        string extension;
        if(extensionPos != string::npos ) {
            extension = path.substr(extensionPos);
        }
        if(extension == ".hdr" || extension == ".exr") {
            cvColourFormat = CV_32FC3;
        }
        texture = imread(path, -1);
        if(texture.empty()) {
            return;
        }

        loaded = true;
        width = texture.cols;
        height = texture.rows;
        textureData = new vec3[width * height];
        int depth = texture.depth();
        if(depth == CV_8U) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    int index = i * width + j;
                    Vec3b& colour = texture.at<Vec3b>(i, j);
                    textureData[index] = vec3(colour[2] / 255.0f, colour[1]/255.0f, colour[0] / 255.0f);
                }
            }
        } else if(depth == CV_16U) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    int index = i * width + j;
                    Vec3w& colour = texture.at<Vec3w>(i, j);
                    textureData[index] = vec3(colour[2] / 65535.0f, colour[1]/65535.0f, colour[0] / 65535.0f);
                }
            }
        } else if(depth == CV_32F) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    int index = i * width + j;
                    Vec3f colour = texture.at<Vec3f>(i, j);
                    textureData[index] = vec3(colour[2], colour[1], colour[0]);
                }
            }
        } else {
            std::cerr << "TextureMap2D cannot load image: unrecognized image format" << endl;
        }
    }

    void TextureMap2D::convertToLinear() {
        constexpr vec3 gamma = vec3(2.2f);
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                int index = i * width + j;
                textureData[index] = glm::pow(textureData[index], gamma);
            }
        }
    }

    vec3 TextureMap2D::samplePoint(int x, int y) const {
        if(x < 0 || x >= width || y < 0 || y >= height) {
            return vec3(0);
        }
        return textureData[x + y * width];
    }

    vec3 TextureMap2D::sampleBilinear(vec2 uv) const {
        return glm::vec3();
    }

    vec3 TextureMap2D::sampleNearest(vec2 uv) const {
        uv = glm::clamp(uv, vec2(0), vec2(1));
        //uv.y = 1.0f - uv.y;
        const int x = static_cast<const int>(uv.x * (width-1));
        const int y = static_cast<const int>(uv.y * (height-1));
        const int index = y * width + x;
        return textureData[index];
    }

    TextureMap2D::~TextureMap2D() {
        if(textureData) {
            delete[] textureData;
            textureData = nullptr;
        }
    }

    void testLoadingImage(const string &path) {
        Mat image = imread(path, -1);
        namedWindow("testing");
        cout << "width: " << image.cols<< endl;
        cout << "height: " << image.rows << endl;
        cout << "channels: " << image.channels() << endl;
        cout << "depth: " << image.depth() << endl;
        const int height = image.rows;
        const int width = image.cols;
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                int index = i * width + j;
                Vec3f& f = image.at<Vec3f>(i, j);
                cout << "pixel " << f[0] << ' '<< f[1] << ' ' << f[2] << ' ' << f[3] << endl;
            }
        }
        imshow("testing", image);
        waitKey(0);
    }
}
