//
// Created by Zaiyang Li on 11/02/2018.
//

#ifndef RENDERER_AXISALIGNEDPLANE_HPP
#define RENDERER_AXISALIGNEDPLANE_HPP

namespace McRenderFace {
    struct AxisAlignedPlane {
        int axis;
        static const int X_AXIS;
        static const int Y_AXIS;
        static const int Z_AXIS;
        static const int W_AXIS;
        float value;
    };
    static const int X_AXIS = 0;
    static const int Y_AXIS = 1;
    static const int Z_AXIS = 2;
    static const int W_AXIS = 3;
}


#endif //RENDERER_AXISALIGNEDPLANE_HPP
