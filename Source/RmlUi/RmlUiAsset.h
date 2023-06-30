#pragma once

#include <Engine/Content/BinaryAsset.h>

/// <summary>
/// RmlUi asset.
/// </summary>
API_CLASS(NoSpawn) class RMLUI_API RmlUiAsset : public BinaryAsset
{
    DECLARE_BINARY_ASSET_HEADER(RmlUiAsset, 1);

private:

protected:
    // [BinaryAsset]
    LoadResult load() override;
    void unload(bool isReloading) override;
    AssetChunksFlag getChunksToPreload() const override;
};
