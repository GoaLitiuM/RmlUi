#pragma once

#include "RmlUiDocumentAsset.h"
#include "RmlUiFont.h"

#include <Engine/Content/AssetReference.h>
#include <Engine/Level/Actor.h>

namespace Rml
{
    class ElementDocument;
    class Context;
}

class RmlUiCanvas;

/// <summary>
/// RmlUi Document.
/// </summary>
API_CLASS(NoConstructor, Attributes="ActorContextMenu(\"New/UI/RmlUi Document\"), ActorToolbox(\"GUI\")")
class RMLUI_API RmlUiDocument : public Actor
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCENE_OBJECT(RmlUiDocument);

private:
    Rml::ElementDocument* elementDocument = nullptr;

public:
    /// <summary>
    /// The document asset.
    /// </summary>
    API_FIELD(Attributes="EditorDisplay(\"Document Settings\")") AssetReference<RmlUiDocumentAsset> Document;

    /// <summary>
    /// Load document when this actor is activated.
    /// </summary>
    API_FIELD(Attributes="EditorDisplay(\"Document Settings\"), DefaultValue(true)") bool AutoLoadDocument = true;

    /// <summary>
    /// Focuses the document automatically when actor is enabled.
    /// </summary>
    API_FIELD(Attributes="EditorDisplay(\"Document Settings\"), DefaultValue(false)") bool AutoFocusDocument = false;

    /// <summary>
    /// Fonts to be loaded.
    /// </summary>
    API_FIELD() Array<RmlUiFont> Fonts;

public:
    /// <summary>
    /// Returns the wrapped Rml::ElementDocument.
    /// </summary>
    Rml::ElementDocument* GetDocument() const;

    /// <summary>
    /// Loads the wrapped document asset.
    /// </summary>
    /// <returns>Returns true if the document was loaded successfully.</returns>
    bool LoadDocument();

    /// <summary>
    /// Unloads the wrapped document asset.
    /// </summary>
    void UnloadDocument();

    /// <summary>
    /// Shows the document.
    /// </summary>
    void Show() const;

    /// <summary>
    /// Hides the document.
    /// </summary>
    void Hide() const;

    /// <summary>
    /// Closes the document.
    /// </summary>
    void Close() const;

    /// <summary>
    /// Returns true if this document and the canvas is focused.
    /// </summary>
    bool HasFocus() const;

    /// <summary>
    /// Focuses the document, allowing it to receive input events.
    /// </summary>
    void Focus() const;

    /// <summary>
    /// Defocuses the document, prevents receiving any further input events.
    /// </summary>
    void Defocus() const;

private:
    RmlUiCanvas* GetCanvas() const;
    Rml::Context* GetContext() const;

protected:
    // [Actor]
    void BeginPlay(SceneBeginData* data) final override;
    void EndPlay() final override;
    void OnEnable() override;
    void OnDisable() override;
    void OnParentChanged() override;
    void OnTransformChanged() final override;
#if USE_EDITOR
    void OnActiveInTreeChanged() override;
#endif
};
