#if FLAX_EDITOR
using System;
using System.Linq;
using FlaxEditor.Content;
using FlaxEngine;
using FlaxEditor;
using FlaxEditor.Windows;
using FlaxEditor.Content.Import;
using System.Runtime.CompilerServices;

namespace RmlUi;

public unsafe partial struct RmlUiTransformPrimitive
{
    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformMatrix2D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformMatrix3D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformTranslateX value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformTranslateY value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformTranslateZ value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformTranslate2D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformTranslate3D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformScaleX value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformScaleY value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformScaleZ value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformScale2D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformScale3D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformRotateX value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformRotateY value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformRotateZ value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformRotate2D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformRotate3D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformSkewX value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformSkewY value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformSkew2D value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformPerspective value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }

    /// <inheritdoc />
    public static implicit operator RmlUiTransformPrimitive(RmlUiTransformDecomposedMatrix4 value)
    {
        RmlUiTransformPrimitive primitive = default;
        Unsafe.Write(Unsafe.AsPointer(ref primitive), value);
        return primitive;
    }
}

#if false
public unsafe partial class RmlUiTransform : FlaxEngine.Object
{
    public static RmlUiProperty MakeProperty(params RmlUiTransformPrimitive[] primitives)
    {
        return MakePropertyInternal(primitives);
    }
}
#endif

public partial struct RmlUiTween
{
    public RmlUiTween(RmlUiTweenType type = RmlUiTweenType.Linear, RmlUiTweenDirection direction = RmlUiTweenDirection.Out)
    {
        if (direction.HasFlag(RmlUiTweenDirection.In))
            TypeIn = type;
        if (direction.HasFlag(RmlUiTweenDirection.Out))
            TypeOut = type;
    }

    public RmlUiTween(RmlUiTweenType typeIn, RmlUiTweenType typeOut)
    {
        TypeIn = typeIn;
        TypeIn = typeOut;
    }

    //public RmlUiTween(Callback callback, RmlUiTweenDirection direction = RmlUiTweenDirection.In)
    //{
    //}
}

public partial class RmlUiTransforms
{
    
}

/// <summary>
/// Import settings for RmlUi assets.
/// </summary>
public class RmlUiAssetImportSettings
{
}

/// <summary>
/// Helper class for managing RmlUi custom assets.
/// </summary>
[Unmanaged]
public class RmlUiImport
{
    /// <summary>
    /// Asset icon.
    /// </summary>
    public static SpriteHandle RmlUiAssetIcon;

    /// <summary>
    /// Register importers and asset proxies of RmlUi assets for editor.
    /// </summary>
    public static void RegisterManagedImporters()
    {
        SpriteAtlas documentIconAtlas = Content.Load<SpriteAtlas>(FlaxEngine.Json.JsonSerializer.ParseID("0e03b8e34dfe17a0a85e0889f63b36a4"));
        RmlUiAssetIcon = documentIconAtlas.FindSprite("Icon");

        ImportFileEntry.FileTypes["rml"] = ImportRmlUiAsset;
        ImportFileEntry.FileTypes["rcss"] = ImportRmlUiAsset;

        AddOrUpdateProxy(new RmlUiAssetProxy());
        AddOrUpdateProxy(new RmlUiDocumentAssetProxy());
        Editor.Instance.ContentDatabase.Rebuild(true);
    }

    private static void AddOrUpdateProxy(ContentProxy proxy)
    {
        ContentProxy existingProxy = Editor.Instance.ContentDatabase.Proxy.FirstOrDefault(x => x.Name == proxy.Name);
        if (existingProxy != null)
            Editor.Instance.ContentDatabase.RemoveProxy(existingProxy);
        Editor.Instance.ContentDatabase.AddProxy(proxy);
    }

    private static ImportFileEntry ImportRmlUiAsset(ref Request request)
    {
        return new RmlUiAssetImportEntry(ref request);
    }
}

/// <summary>
/// RmlUi asset import entry.
/// </summary>
public partial class RmlUiAssetImportEntry : AssetImportEntry
{
    private RmlUiAssetImportSettings _settings = new RmlUiAssetImportSettings();

    /// <inheritdoc />
    public override object Settings => null;

    /// <inheritdoc />
    public RmlUiAssetImportEntry(ref Request request)
    : base(ref request)
    {
        //RmlUiAssetImportSettings.TryRestore(ref _settings, ResultUrl);
    }

    /// <inheritdoc />
    public override bool TryOverrideSettings(object settings)
    {
        if (settings is RmlUiAssetImportSettings o)
        {
            _settings = o;
            return true;
        }
        return false;
    }
}


/// <summary>
/// RmlUi asset item.
/// </summary>
class RmlUiAssetItem : BinaryAssetItem
{
    /// <inheritdoc />
    public RmlUiAssetItem(string path, ref Guid id, string typeName, Type type)
    : base(path, ref id, typeName, type, ContentItemSearchFilter.Other)
    {
    }

    /// <inheritdoc />
    public override SpriteHandle DefaultThumbnail => RmlUiImport.RmlUiAssetIcon;
}

/// <summary>
///  RmlUi document asset item.
/// </summary>
class RmlUiDocumentAssetItem : BinaryAssetItem
{
    /// <inheritdoc />
    public RmlUiDocumentAssetItem(string path, ref Guid id, string typeName, Type type)
    : base(path, ref id, typeName, type, ContentItemSearchFilter.Other)
    {
    }

    /// <inheritdoc />
    public override SpriteHandle DefaultThumbnail => RmlUiImport.RmlUiAssetIcon;
}

/// <summary>
/// RmlUi asset proxy object.
/// </summary>
public class RmlUiAssetProxy : BinaryAssetProxy
{
    /// <inheritdoc />
    public override string Name => "RmlUi Asset";

    /// <inheritdoc />
    public override bool IsProxyFor(ContentItem item)
    {
        return item is RmlUiAssetItem;
    }

    /// <inheritdoc />
    public override string FileExtension => string.Empty;

    /// <inheritdoc/>
    public override Type AssetType => typeof(RmlUiAsset);

    /// <inheritdoc />
    public override EditorWindow Open(Editor editor, ContentItem item)
    {
        return null;
    }

    /// <inheritdoc />
    public override AssetItem ConstructItem(string path, string typeName, ref Guid id)
    {
        return new RmlUiAssetItem(path, ref id, typeName, AssetType);
    }

    /// <inheritdoc />
    public override Color AccentColor => Color.FromRGB(0xF23A00);

    /// <inheritdoc />
    public override string TypeName => "RmlUi.RmlUiAsset";
}

/// <summary>
/// RmlUi document asset proxy object.
/// </summary>
public class RmlUiDocumentAssetProxy : RmlUiAssetProxy
{
    /// <inheritdoc />
    public override string Name => "RmlUi Document";

    /// <inheritdoc />
    public override bool IsProxyFor(ContentItem item)
    {
        return item is RmlUiDocumentAssetItem;
    }

    /// <inheritdoc />
    public override string FileExtension => string.Empty;

    /// <inheritdoc/>
    public override Type AssetType => typeof(RmlUiDocumentAsset);

    /// <inheritdoc />
    public override EditorWindow Open(Editor editor, ContentItem item)
    {
        return null;
    }

    /// <inheritdoc />
    public override AssetItem ConstructItem(string path, string typeName, ref Guid id)
    {
        return new RmlUiDocumentAssetItem(path, ref id, typeName, AssetType);
    }

    /// <inheritdoc />
    public override Color AccentColor => Color.FromRGB(0xF23A00);

    /// <inheritdoc />
    public override string TypeName => "RmlUi.RmlUiDocumentAsset";
}

#endif