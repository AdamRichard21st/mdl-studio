#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading bones", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Bones: %d^n", model[MStudio_numbones]);

    new bone[MStudioBone];
    new i = 0;

    while (mdl_studio_get_bone(model, i++, bone))
    {
        log_amx("Bone %d Name: ^"%s^"", i, bone[MStudioBone_name]);
        log_amx("Bone %d Parent: %d", i, bone[MStudioBone_parent]);
        log_amx("Bone %d Flags: %d", i, bone[MStudioBone_flags]);

        log_amx("Bone %d Bonecontroller: %d %d %d %d %d %d", i,
            bone[MStudioBone_bonecontroller][0],
            bone[MStudioBone_bonecontroller][1],
            bone[MStudioBone_bonecontroller][2],
            bone[MStudioBone_bonecontroller][3],
            bone[MStudioBone_bonecontroller][4],
            bone[MStudioBone_bonecontroller][5]
        );

        log_amx("Bone %d Value: %f %f %f %f %f %f", i,
            bone[MStudioBone_value][0],
            bone[MStudioBone_value][1],
            bone[MStudioBone_value][2],
            bone[MStudioBone_value][3],
            bone[MStudioBone_value][4],
            bone[MStudioBone_value][5]
        );

        log_amx("Bone %d Scale: %f %f %f %f %f %f^n", i,
            bone[MStudioBone_scale][0],
            bone[MStudioBone_scale][1],
            bone[MStudioBone_scale][2],
            bone[MStudioBone_scale][3],
            bone[MStudioBone_scale][4],
            bone[MStudioBone_scale][5]
        );
    }

    mdl_studio_close(model);
}