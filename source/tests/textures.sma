#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading textures", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Textures: %d", model[MStudio_numtextures]);

    new texture[MStudioTexture];
    new i = 0;

    while (mdl_studio_get_texture(model, i++, texture))
    {
        log_amx("Texture %d Name: ^"%s^"",  i, texture[MStudioTexture_name]);
        log_amx("Texture %d Flags: %d",     i, texture[MStudioTexture_flags]);
        log_amx("Texture %d Width: %d",     i, texture[MStudioTexture_width]);
        log_amx("Texture %d Height: %d^n",  i, texture[MStudioTexture_height]);
    }

    mdl_studio_close(model);
}