//
// Created by Zaiyang Li on 11/02/2018.
//

#ifndef RENDERER_AXISALIGNEDPLANE_HPP
#define RENDERER_AXISALIGNEDPLANE_HPP

namespace McRenderFace {
    struct AxisAlignedPlane {
        int axis;
        static const X_AXIS;
        static const Y_AXIS;
        static const Z_AXIS;
        static const W_AXIS;
        float value;
    };
    static const X_AXIS = 0;
    static const Y_AXIS = 1;
    static const Z_AXIS = 2;
    static const W_AXIS = 3;
}


#endif //RENDERER_AXISALIGNEDPLANE_HPP
