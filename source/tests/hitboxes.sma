#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading hitboxes", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Hitboxes: %d^n", model[MStudio_numhitboxes]);

    new hitbox[MStudioHitbox];
    new i = 0;

    while (mdl_studio_get_hitbox(model, i++, hitbox))
    {
        log_amx("Hitbox %d Bone: %d", i, hitbox[MStudioBBox_bone]);
        log_amx("Hitbox %d Group: %d", i, hitbox[MStudioBBox_group]);

        log_amx("Hitbox %d Bounding Box Min: %f %f %f", i,
            hitbox[MStudioBBox_bbmin][0],
            hitbox[MStudioBBox_bbmin][1],
            hitbox[MStudioBBox_bbmin][2]
        );

        log_amx("Hitbox %d Bounding Box Max: %f %f %f^n", i,
            hitbox[MStudioBBox_bbmax][0],
            hitbox[MStudioBBox_bbmax][1],
            hitbox[MStudioBBox_bbmax][2]
        );
    }

    mdl_studio_close(model);
}