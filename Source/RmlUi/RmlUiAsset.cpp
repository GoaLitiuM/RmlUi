#include "RmlUiAsset.h"

#include <Engine/Content/Factories/BinaryAssetFactory.h>

REGISTER_BINARY_ASSET(RmlUiAsset, "RmlUi.RmlUiAsset", true);

RmlUiAsset::RmlUiAsset(const SpawnParams& params, const AssetInfo* info)
    : BinaryAsset(params, info)
{
}

Asset::LoadResult RmlUiAsset::load()
{
    const auto dataChunk = GetChunk(0);
    if (dataChunk == nullptr)
        return LoadResult::MissingDataChunk;

    return LoadResult::Ok;
}

void RmlUiAsset::unload(bool isReloading)
{
}

AssetChunksFlag RmlUiAsset::getChunksToPreload() const
{
    return GET_CHUNK_FLAG(0);
}
