#include < amxmodx >
#include < mdl_studio >


public plugin_init()
{
    register_plugin("Example: Reading sequences", "1.0.0", "AdamRichard21st");

    new model[MStudio];

    if (!mdl_studio_open("models/player.mdl", model))
    {
        log_amx("Could not open models/player.mdl for reading.");
        return;
    }

    log_amx("Number of Sequences: %d^n", model[MStudio_numseq]);

    new sequence[MStudioSequence];
    new i = 0;

    while (mdl_studio_get_sequence(model, i++, sequence))
    {
        log_amx("Sequence %d Label: ^"%s^"",        i, sequence[MStudioSeq_label]);
        log_amx("Sequence %d Frames per sec: %f",   i, sequence[MStudioSeq_fps]);
        log_amx("Sequence %d Flags: %d",            i, sequence[MStudioSeq_flags]);
        log_amx("Sequence %d events: %d^n",         i, sequence[MStudioSeq_numevents]);
    }

    mdl_studio_close(model);
}