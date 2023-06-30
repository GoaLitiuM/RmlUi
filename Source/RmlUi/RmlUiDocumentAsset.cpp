#include "RmlUiDocumentAsset.h"

#include "Engine/Content/Factories/BinaryAssetFactory.h"

REGISTER_BINARY_ASSET(RmlUiDocumentAsset, "RmlUi.RmlUiDocumentAsset", true);

RmlUiDocumentAsset::RmlUiDocumentAsset(const SpawnParams& params, const AssetInfo* info)
    : RmlUiAsset(params, info)
{
}