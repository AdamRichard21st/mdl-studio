#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading model", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Bones: %d^n", model[MStudio_numbones]);

    log_amx("ID Tag: %s", model[MStudio_id] == IDSTUDIOHEADER ? "IDST" : "UNKNOWN");
    log_amx("Version: %d", model[MStudio_version]);
    log_amx("Name: ^"%s^"", model[MStudio_name]);
    log_amx("Length: %d", model[MStudio_length]);

    log_amx("Eye Position: %f %f %f",
        model[MStudio_eyeposition][0],
        model[MStudio_eyeposition][1],
        model[MStudio_eyeposition][2]
    );

    log_amx("Min: %f %f %f",
        model[MStudio_min][0],
        model[MStudio_min][1],
        model[MStudio_min][2]
    );

    log_amx("Max: %f %f %f",
        model[MStudio_max][0],
        model[MStudio_max][1],
        model[MStudio_max][2]
    );

    log_amx("Bounding Box Min: %f %f %f",
        model[MStudio_bbmin][0],
        model[MStudio_bbmin][1],
        model[MStudio_bbmin][2]
    );

    log_amx("Bounding Box Max: %f %f %f",
        model[MStudio_bbmax][0],
        model[MStudio_bbmax][1],
        model[MStudio_bbmax][2]
    );

    log_amx("Flags: %d^n", model[MStudio_flags]);

    mdl_studio_close(model);
}