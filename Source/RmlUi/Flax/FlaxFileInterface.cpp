#include "FlaxFileInterface.h"

#include <Engine/Content/BinaryAsset.h>
#include <Engine/Content/Content.h>
#include <Engine/Core/Collections/Dictionary.h>
#include <Engine/Core/Math/Math.h>
#include <Engine/Core/Types/Span.h>

// We assume only .rml and .rcss files are accessed through this interface,
// so we only support loading specific BinaryAsset files.

namespace
{
    // Store spans of binary assets to provide random access to the data
    Dictionary<BinaryAsset*, Span<byte>> AssetSpans;
}

Rml::FileHandle FlaxFileInterface::Open(const Rml::String& path)
{
    String assetPath = String(StringUtils::GetPathWithoutExtension(String(path.c_str()))) + ASSET_FILES_EXTENSION_WITH_DOT;
    BinaryAsset* asset = Content::Load<BinaryAsset>(assetPath);
    if (asset == nullptr)
        return Rml::FileHandle();

    if (asset->LoadChunks(ALL_ASSET_CHUNKS))
        return Rml::FileHandle();

    asset->AddReference();
    FlaxChunk* chunk = asset->GetChunk(0);
    Span<byte> span = Span<byte>(chunk->Data.Get(), chunk->Data.Length());
    AssetSpans[asset] = span;
    return (Rml::FileHandle)asset;
}

void FlaxFileInterface::Close(Rml::FileHandle file)
{
    auto asset = (BinaryAsset*)file;
    AssetSpans.Remove(asset);
    asset->RemoveReference();
}

size_t FlaxFileInterface::Read(void* buffer, size_t size, Rml::FileHandle file)
{
    auto asset = (BinaryAsset*)file;
    Span<byte>& span = AssetSpans.At(asset);
    const int32 readSize = Math::Min((int32)size, span.Length());
    Platform::MemoryCopy(buffer, span.Get(), readSize);
    span = Span<byte>(span.Get() + readSize, span.Length() - readSize);
    return readSize;
}

bool FlaxFileInterface::Seek(Rml::FileHandle file, long offset, int origin)
{
    auto asset = (BinaryAsset*)file;
    Span<byte>& span = AssetSpans.At(asset);
    FlaxChunk* chunk = asset->GetChunk(0);
    byte* start = chunk->Data.Get();
    byte* end = start + chunk->Data.Length();
    byte* ptr;
    if (origin == SEEK_CUR)
        ptr = span.Get() + offset;
    else if (origin == SEEK_SET)
        ptr = start + offset;
    else if (origin == SEEK_END)
        ptr = end + offset;
    else
        ptr = nullptr;

    ASSERT(ptr >= start);
    ASSERT(ptr < end);

    span = Span<byte>(ptr, (int32)(end - ptr));
    return true;
}

size_t FlaxFileInterface::Tell(Rml::FileHandle file)
{
    auto asset = (BinaryAsset*)file;
    Span<byte>& span = AssetSpans.At(asset);
    byte* start = asset->GetChunk(0)->Data.Get();
    size_t offset = span.Get() - start;
    return offset;
}

size_t FlaxFileInterface::Length(Rml::FileHandle file)
{
    auto asset = (BinaryAsset*)file;
    return asset->GetChunkSize(0);
}

bool FlaxFileInterface::LoadFile(const Rml::String& path, Rml::String& out_data)
{
    auto asset = (BinaryAsset*)Open(path);
    if (asset == nullptr)
        return false;

    out_data.resize(Length((Rml::FileHandle)asset));
    size_t read = Read(&out_data[0], out_data.length(), (Rml::FileHandle)asset);
    Close((Rml::FileHandle)asset);

    if (read != out_data.length())
        return false;

    return true;
}