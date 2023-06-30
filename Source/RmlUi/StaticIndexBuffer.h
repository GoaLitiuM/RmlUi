#pragma once

#include <Engine/Graphics/DynamicBuffer.h>

/// <summary>
/// Static index buffer that allows to render any indices during multiple frames
/// </summary>
class RMLUI_API StaticIndexBuffer : public DynamicBuffer
{
public:
    /// <summary>
    /// Init
    /// </summary>
    /// <param name="initialCapacity">Initial capacity of the buffer (in bytes)</param>
    /// <param name="stride">Stride in bytes</param>
    /// <param name="name">Buffer name</param>
    StaticIndexBuffer(uint32 initialCapacity, uint32 stride, const String& name = String::Empty)
        : DynamicBuffer(initialCapacity, stride, name)
    {
    }

protected:
    // [DynamicBuffer]
    void InitDesc(GPUBufferDescription& desc, int32 numElements) override
    {
        desc = GPUBufferDescription::Index(_stride, numElements, GPUResourceUsage::Default);
    }
};
