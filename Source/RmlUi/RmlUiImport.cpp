#if USE_EDITOR

#include "RmlUiImport.h"
#include "RmlUiAsset.h"
#include "RmlUiDocumentAsset.h"

#include <Engine/ContentImporters/AssetsImportingManager.h>
#include <Engine/Platform/File.h>
#include <Engine/Scripting/ManagedCLR/MClass.h>
#include <Engine/Scripting/ManagedCLR/MMethod.h>
#include <Engine/Scripting/Scripting.h>

CreateAssetResult ImportRmlUiAsset(CreateAssetContext& context)
{
    IMPORT_SETUP(RmlUiAsset, 1);

    StringAnsi inputData;
    if (File::ReadAllText(context.InputPath, inputData))
        return CreateAssetResult::InvalidPath;

    if (context.AllocateChunk(0))
        return CreateAssetResult::CannotAllocateChunk;
    auto chunk = context.Data.Header.Chunks[0];
    chunk->Data.Allocate(inputData.Length() * sizeof(char));
    Platform::MemoryCopy(chunk->Get(), inputData.Get(), chunk->Data.Length());

    return CreateAssetResult::Ok;
}

CreateAssetResult ImportRmlUiDocumentAsset(CreateAssetContext& context)
{
    IMPORT_SETUP(RmlUiDocumentAsset, 1);

    StringAnsi inputData;
    if (File::ReadAllText(context.InputPath, inputData))
        return CreateAssetResult::InvalidPath;

    if (context.AllocateChunk(0))
        return CreateAssetResult::CannotAllocateChunk;
    auto chunk = context.Data.Header.Chunks[0];
    chunk->Data.Allocate(inputData.Length() * sizeof(char));
    Platform::MemoryCopy(chunk->Get(), inputData.Get(), chunk->Data.Length());

    return CreateAssetResult::Ok;
}

void AddOrUpdateImporter(AssetImporter customImporter)
{
    for (auto& importer : AssetsImportingManager::Importers)
    {
        if (importer.FileExtension == customImporter.FileExtension)
        {
            importer.Callback = customImporter.Callback;
            return;
        }
    }
    AssetsImportingManager::Importers.Add(customImporter);
}

void RegisterRmlUiImporters()
{
    // Register importers in managed side
    MClass* importer = Scripting::FindClass("RmlUi.RmlUiImport");
    if (importer)
    {
        MMethod* method = importer->GetMethod("RegisterManagedImporters");
        if (method)
            method->Invoke(nullptr, nullptr, nullptr);
    }

    AddOrUpdateImporter({TEXT("rml"), ASSET_FILES_EXTENSION, ImportRmlUiDocumentAsset});
    AddOrUpdateImporter({TEXT("rcss"), ASSET_FILES_EXTENSION, ImportRmlUiAsset});
}

#endif
