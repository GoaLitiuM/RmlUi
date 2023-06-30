// This code was auto-generated. Do not modify it.

#include "Engine/Scripting/BinaryModule.h"
#include "RmlUi.Gen.h"

StaticallyLinkedBinaryModuleInitializer StaticallyLinkedBinaryModuleRmlUi(GetBinaryModuleRmlUi);

extern "C" BinaryModule* GetBinaryModuleRmlUi()
{
    static NativeBinaryModule module("RmlUi");
    return &module;
}
