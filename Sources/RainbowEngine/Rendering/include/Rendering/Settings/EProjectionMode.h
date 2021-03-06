#pragma once

#include "Rendering/API/Export.h"

namespace Rendering::Settings
{
    /**
    * Projection modes, mostly used for cameras
    * 设置投影方式
    * 正交投影或者透视投影
    */
    enum class EProjectionMode
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };
}