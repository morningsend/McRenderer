//
// Created by Zaiyang Li on 10/02/2018.
//

#include "IOUtility.hpp"

std::ostream& operator << (std::ostream& out, const glm::vec3& vec) {
    out<<'(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
}