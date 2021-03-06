#pragma once

#include "Rendering/API/Export.h"

namespace Rendering::Settings
{
    /**
    * Projection modes, mostly used for cameras
    * ����ͶӰ��ʽ
    * ����ͶӰ����͸��ͶӰ
    */
    enum class EProjectionMode
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };
}