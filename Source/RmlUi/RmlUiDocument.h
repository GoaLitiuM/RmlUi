#pragma once

#include "RmlUiDocumentAsset.h"
#include "RmlUiElement.h"
#include "RmlUiFont.h"

#include <Engine/Content/AssetReference.h>
#include <Engine/Level/Actor.h>

namespace Rml
{
    class ElementDocument;
    class Element;
    class Context;
}

class RmlUiCanvas;

/// <summary>
/// RmlUi Document.
/// </summary>
API_CLASS(NoConstructor, Attributes = "ActorContextMenu(\"New/UI/RmlUi Document\"), ActorToolbox(\"GUI\")")
class RMLUI_API RmlUiDocument : public Actor
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCENE_OBJECT(RmlUiDocument);

private:
    RmlUiElement* element = nullptr;
    Array<Rml::ElementPtr> ownedElements;

public:
    /// <summary>
    /// The document asset.
    /// </summary>
    API_FIELD(Attributes = "EditorDisplay(\"Document Settings\")") AssetReference<RmlUiDocumentAsset> Document;

    /// <summary>
    /// Load document when this actor is activated.
    /// </summary>
    API_FIELD(Attributes = "EditorDisplay(\"Document Settings\"), DefaultValue(true)") bool AutoLoadDocument = true;

    /// <summary>
    /// Focuses the document automatically when actor is enabled.
    /// </summary>
    API_FIELD(Attributes = "EditorDisplay(\"Document Settings\"), DefaultValue(false)") bool AutoFocusDocument = false;

    /// <summary>
    /// Fonts to be loaded.
    /// </summary>
    API_FIELD() Array<RmlUiFont> Fonts;

public:
    /// <summary>
    /// Returns the element of this document.
    /// </summary>
    API_PROPERTY() RmlUiElement* Element() { return element; }

    /// <summary>
    /// Returns the wrapped Rml::Element.
    /// </summary>
    FORCE_INLINE Rml::Element* GetElement() const { return element->GetElement(); }

    /// <summary>
    /// Returns the wrapped Rml::ElementDocument.
    /// </summary>
    Rml::ElementDocument* GetDocument() const;

    /// <summary>
    /// Returns the Rml::Context of the wrapped Rml:ElementDocument.
    /// </summary>
    Rml::Context* GetContext() const;

    /// <summary>
    /// Loads the wrapped document asset.
    /// </summary>
    /// <returns>Returns true if the document was loaded successfully.</returns>
    API_FUNCTION() bool LoadDocument();

    /// <summary>
    /// Unloads the wrapped document asset.
    /// </summary>
    API_FUNCTION() void UnloadDocument();

    /// <summary>
    /// Returns true if the document was loaded previously.
    /// </summary>
    API_FUNCTION() bool IsLoaded();

    /// <summary>
    /// Shows the document.
    /// </summary>
    API_FUNCTION() void Show() const;

    /// <summary>
    /// Hides the document.
    /// </summary>
    API_FUNCTION() void Hide() const;

    /// <summary>
    /// Closes the document.
    /// </summary>
    API_FUNCTION() void Close() const;

    /// <summary>
    /// Create a new named element.
    /// </summary>
    RmlUiElement* CreateElement(const String& name);

    /// <summary>
    /// Create a new text element with given text.
    /// </summary>
    RmlUiElement* CreateTextNode(const String& text);

    /// <summary>
    /// Returns true if this document and the canvas is focused.
    /// </summary>
    API_FUNCTION() bool HasFocus() const;

    /// <summary>
    /// Focuses the document, allowing it to receive input events.
    /// </summary>
    API_FUNCTION() void Focus() const;

    /// <summary>
    /// Defocuses the document, prevents receiving any further input events.
    /// </summary>
    API_FUNCTION() void Defocus() const;


private:
    RmlUiCanvas* GetCanvas() const;

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