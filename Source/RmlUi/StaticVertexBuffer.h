#pragma once

#include <Engine/Graphics/DynamicBuffer.h>

/// <summary>
/// Static vertex buffer that allows to render any vertices during multiple frames
/// </summary>
class RMLUI_API StaticVertexBuffer : public DynamicBuffer
{
public:
    /// <summary>
    /// Init
    /// </summary>
    /// <param name="initialCapacity">Initial capacity of the buffer (in bytes)</param>
    /// <param name="stride">Stride in bytes</param>
    /// <param name="name">Buffer name</param>
    StaticVertexBuffer(uint32 initialCapacity, uint32 stride, const String& name = String::Empty)
        : DynamicBuffer(initialCapacity, stride, name)
    {
    }

protected:
    // [DynamicBuffer]
    void InitDesc(GPUBufferDescription& desc, int32 numElements) override
    {
        desc = GPUBufferDescription::Vertex(_stride, numElements, GPUResourceUsage::Default);
    }
};
