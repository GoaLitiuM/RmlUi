# RmlUi for Flax Engine

This is the [RmlUi](https://github.com/mikke89/RmlUi) plugin for [Flax Engine](https://flaxengine.com/).

The plugin is still under development and currently has support for C++-scripting.

Minimum supported Flax version: `1.6`.

## Installation

1. Clone the repository into `<game-project>\Plugins\RmlUi`, or add the repository as a submodule to the game repository.

2. Add a reference to *RmlUi* project in your game by modifying `<game-project>.flaxproj` as follows:

```
...
"References": [
    {
        "Name": "$(EnginePath)/Flax.flaxproj"
    },
    {
        "Name": "$(ProjectPath)/Plugins/RmlUi/RmlUi.flaxproj"
    }
]
```

3. Add a reference to RmlUi plugin module in you game code module by modifying `Source/Game/Game.Build.cs` as follows (or any other game modules using the plugin):

```cs
/// <inheritdoc />
public override void Setup(BuildOptions options)
{
    base.Setup(options);

    ...

    switch (options.Platform.Target)
    {
    case TargetPlatform.Windows:
    case TargetPlatform.Linux:
    case TargetPlatform.Mac:
        options.PublicDependencies.Add("RmlUi");
        break;
    }
}
```

This will add reference to `RmlUi` module on Windows/Linux/Mac platforms.

4. Test it out!

In Flax Editor, the plugin should be listed in the Plugins window under the GUI category.

TODO: Add simple instructions how to use the plugin here.
TODO: Add links to example Flax-projects using the plugin here.

## License

This plugin is released under the **MIT License**.