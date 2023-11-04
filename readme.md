# Library

This is a basic Half-Life MDL parsing layer for [AmxModX](https://github.com/alliedmodders/amxmodx) plugins.

## Features

You can read few informations from a MDL. For example:

- Bones
- Bones controllers
- Hitboxes
- Sequences
- Textures
- Body parts
- Attachments

## Usage

```cpp
#include <mdl_studio>

foo()
{
    new model[MStudio];
    mdl_studio_open("models/player.mdl", model);

    for (new i = 0; i < model[MStudio_numseq]; i++)
    {
        new sequence[MStudioSequence];
        mdl_studio_get_sequence(model, i, sequence);

        print("Sequece name => %s", sequence[MStudioSeq_label]);
        print("Fps => %f", sequence[MStudioSeq_fps]);
        print("Frames => %d", sequence[MStudioSeq_numframes]);
    }

    mdl_studio_close(model);
}
```

# References

- [MDL: Half Life 1 file format](https://github.com/malortie/assimp/wiki/MDL:-Half-Life-1-file-format)
- [MDL file format (Quake's models)](http://tfc.duke.free.fr/coding/mdl-specs-en.html)
- [Rehlds: /public/rehlds/studio.h](https://github.com/dreamstalker/rehlds/blob/65c6ce593b5eabf13e92b03352e4b429d0d797b0/rehlds/public/rehlds/studio.h)

### Special thanks

- @HamletEagle, for the references and [examples](https://forums.alliedmods.net/showpost.php?p=2612285&postcount=4)
- [AmxModx](https://github.com/alliedmodders/amxmodx) devs & [community](https://forums.alliedmods.net)