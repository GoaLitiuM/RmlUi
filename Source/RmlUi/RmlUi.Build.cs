using Flax.Build;
using Flax.Build.NativeCpp;
using System.IO;

// The RmlUi library is built with following CMAKE options:
// NO_FONT_INTERFACE_DEFAULT=true
// BUILD_SHARED_LIBS=true
// ENABLE_PRECOMPILED_HEADERS=true
// MATRIX_ROW_MAJOR=false

public class RmlUi : GameModule
{
    private void AddLibrary(BuildOptions options, string libraryPath)
    {
        switch (options.Platform.Target)
        {
            case TargetPlatform.Windows:
                options.OutputFiles.Add(libraryPath + ".lib");
                options.LinkEnv.InputLibraries.Add(libraryPath + ".lib");
                options.DependencyFiles.Add(libraryPath + ".lib");
                options.DependencyFiles.Add(libraryPath + ".dll");
                break;
            default:
                options.OutputFiles.Add(libraryPath + ".a");
                options.LinkEnv.InputLibraries.Add(libraryPath + ".a");
                options.DependencyFiles.Add(libraryPath + ".a");
                options.DependencyFiles.Add(libraryPath + ".so");
                break;
        }
    }

    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        BuildNativeCode = true;

		options.PublicDependencies.Add("Core");
		options.PublicDependencies.Add("Graphics");
        options.PrivateDependencies.Add("freetype");

        if (options.Target.IsEditor)
        {
            options.PrivateDependencies.Add("Editor");
            options.PrivateDependencies.Add("ContentImporters");
            options.PrivateDefinitions.Add("COMPILE_WITH_ASSETS_IMPORTER");
        }

        options.PublicIncludePaths.Add(FolderPath);
        options.PublicIncludePaths.Add(Path.Combine(FolderPath, "..", "ThirdParty", "RmlUi"));

        //options.PrivateDefinitions.Add("USE_RMLUI_6_0");
        string libPath = Path.Combine(FolderPath, "..", "ThirdParty", "Platforms", options.Platform.Target.ToString(), "Binaries", "ThirdParty", options.Architecture.ToString());

        AddLibrary(options, Path.Combine(libPath, "RmlCore"));
        if (options.Configuration != TargetConfiguration.Release)
            AddLibrary(options, Path.Combine(libPath, "RmlDebugger"));

        // TODO: Check support in other platforms
        if (options.Platform.Target != TargetPlatform.Windows)
            throw new InvalidPlatformException(options.Platform.Target);
        if (options.Architecture != TargetArchitecture.x64)
            throw new InvalidArchitectureException(options.Architecture);
    }
}