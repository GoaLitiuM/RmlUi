using Flax.Build;

public class RmlUiEditorTarget : GameProjectEditorTarget
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
