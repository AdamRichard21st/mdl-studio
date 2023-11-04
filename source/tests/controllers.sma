#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading controllers", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Bones Controllers: %d^n", model[MStudio_numbonecontrollers]);

    new controller[MStudioBoneController];
    new i = 0;

    while (mdl_studio_get_bone_controller(model, i++, controller))
    {
        log_amx("Bone Controller %d Bone: %d", i, controller[MStudioBoneController_bone]);
        log_amx("Bone Controller %d Type: %d", i, controller[MStudioBoneController_type]);
        log_amx("Bone Controller %d Start: %f", i, controller[MStudioBoneController_start]);
        log_amx("Bone Controller %d End: %f", i, controller[MStudioBoneController_end]);
        log_amx("Bone Controller %d Rest: %d", i, controller[MStudioBoneController_rest]);
        log_amx("Bone Controller %d Index: %d^n", i, controller[MStudioBoneController_index]);
    }

    mdl_studio_close(model);
}