using System.IO;
using System;
using Flax.Build;
using Flax.Build.NativeCpp;

public class RmlUiTarget : GameProjectTarget
{
    /// <inheritdoc />
    public override void Init()
    {
        base.Init();

        Platforms = new[]
        {
            TargetPlatform.Windows,
            //TargetPlatform.Linux,
            //TargetPlatform.Mac,
        };
        Architectures = new[]
        {
            TargetArchitecture.x64,
        };

        Modules.Add("RmlUi");
    }
}