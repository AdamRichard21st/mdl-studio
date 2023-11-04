#if defined _mdl_studio_included
	#endinput
#endif
#define _mdl_studio_included


// magic number
#define IDSTUDIOHEADER (('T'<<24)+('S'<<16)+('D'<<8)+'I')
#define STUDIO_VERSION 10


#define MSTUDIO_HEADER_BYTES 244
#define MSTUDIO_BONE_BYTES 112
#define MSTUDIO_BONE_CONTROLLER_BYTES 24
#define MSTUDIO_HITBOX_BYTES 32
#define MSTUDIO_SEQUENCE_BYTES 176
#define MSTUDIO_ANIMATION_FRAME_BYTES 12
#define MSTUDIO_SEQUENCE_GROUP_BYTES 104
#define MSTUDIO_TEXTURE_BYTES 80
#define MSTUDIO_BODYPART_BYTES 76
#define MSTUDIO_ATTACHMENT_BYTES 88


#define STUDIO_DYNAMIC_LIGHT	0x0100	// dynamically get lighting from floor or ceil (flying monsters)
#define STUDIO_TRACE_HITBOX		0x0200	// always use hitbox trace instead of bbox


// lighting options
#define STUDIO_NF_FLATSHADE		0x0001
#define STUDIO_NF_CHROME		0x0002
#define STUDIO_NF_FULLBRIGHT	0x0004
#define STUDIO_NF_NOMIPS        0x0008
#define STUDIO_NF_ALPHA         0x0010
#define STUDIO_NF_ADDITIVE      0x0020
#define STUDIO_NF_MASKED        0x0040


// motion flags
#define STUDIO_X		0x0001
#define STUDIO_Y		0x0002	
#define STUDIO_Z		0x0004
#define STUDIO_XR		0x0008
#define STUDIO_YR		0x0010
#define STUDIO_ZR		0x0020
#define STUDIO_LX		0x0040
#define STUDIO_LY		0x0080
#define STUDIO_LZ		0x0100
#define STUDIO_AX		0x0200
#define STUDIO_AY		0x0400
#define STUDIO_AZ		0x0800
#define STUDIO_AXR		0x1000
#define STUDIO_AYR		0x2000
#define STUDIO_AZR		0x4000
#define STUDIO_TYPES	0x7FFF
#define STUDIO_RLOOP	0x8000	// controller that wraps shortest distance


// bonecontroller types
#define STUDIO_MOUTH	4	// hardcoded

// sequence flags
#define STUDIO_LOOPING	0x0001


// bone flags
#define STUDIO_HAS_NORMALS	0x0001
#define STUDIO_HAS_VERTICES 0x0002
#define STUDIO_HAS_BBOX		0x0004
#define STUDIO_HAS_CHROME	0x0008	// if any of the textures have chrome on them


#define RAD_TO_STUDIO		(32768.0/M_PI)
#define STUDIO_TO_RAD		(M_PI/32768.0)

#define STUDIO_NUM_HULLS	128
#define STUDIO_NUM_PLANES	(STUDIO_NUM_HULLS * 6)
#define STUDIO_CACHE_SIZE	16
#define STUDIO_CACHEMASK	(STUDIO_CACHE_SIZE - 1)


#define RAD_TO_STUDIO		(32768.0/M_PI)
#define STUDIO_TO_RAD		(M_PI/32768.0)


/**
 * @note This is the header used when loading any MDL file.
 *       It provides global information about the model, as well
 *       as the offset to every other chunk.
 *
 * @note id should always be IDST for the main MDL file and external texture files.
 *
 * @note version should always be 10. This is the version found in the official Half-Life SDK.
 *
 * @note numtextures is the number of textures stored in the actual MDL file.
 *       If a model uses an external texture file, then this number will be
 *       0 when reading from the main MDL file.
 */
enum _:MStudio
{
	// model file pointer handle.
	MStudio_fileHandle,

	// model file path.
	MStudio_filePath [64],

	// The magic word. See above.
	MStudio_id,

	// The file format version. See above.
	MStudio_version,

	// Model name.
	MStudio_name [64],

	// The file size in bytes.
	MStudio_length,

	// The model's eye position.
	Float:MStudio_eyeposition [3],

	// Hull min extent.
	Float:MStudio_min [3],

	// Hull max extent.
	Float:MStudio_max [3],

	// Clipping box min extent.
	Float:MStudio_bbmin [3],

	// Clipping box max extent.
	Float:MStudio_bbmax [3],

	// ?
	MStudio_flags,

	// The number of bones.
	MStudio_numbones,

	// The offset of the first bone chunk.
	MStudio_boneindex,

	// The number of bone controllers.
	MStudio_numbonecontrollers,

	// The offset of the first bone controller chunk.
	MStudio_bonecontrollerindex,

	// The number of hitboxes.
	MStudio_numhitboxes,

	// The offset of the first hitbox chunk.
	MStudio_hitboxindex,

	// The number of sequences.
	MStudio_numseq,

	// The offset of the first sequence chunk.
	MStudio_seqindex,

	// The number of sequence groups.
	MStudio_numseqgroups,

	// The offset of the first sequence group chunk.
	MStudio_seqgroupindex,

	// The number of textures. See below.
	MStudio_numtextures,

	// The offset of the first texture chunk.
	MStudio_textureindex,

	// The offset of the pixel data of the first texture chunk.
	MStudio_texturedataindex,

	// The number of replacable textures.
	MStudio_numskinref,

	// The number of skin families.
	MStudio_numskinfamilies,

	// The offset of the first skin value.
	MStudio_skinindex,

	// The number of bodyparts.
	MStudio_numbodyparts,

	// The offset of the first bodypart chunk.
	MStudio_bodypartindex,

	// The number of attachments.
	MStudio_numattachments,

	// The offset of the first attachment chunk.
	MStudio_attachmentindex,

	// ?
	MStudio_soundtable,

	// ?
	MStudio_soundindex,

	// ?
	MStudio_soundgroups,

	// ?
	MStudio_soundgroupindex,

	// The number of nodes in the sequence transition graph.
	MStudio_numtransitions,

	// The offset of the first transition value of the sequence transition graph.
	MStudio_transitionindex,
}


/**
 * @note The bones are stored starting from the root node.
 *
 * @note bonecontroller, value and scale all have a fixed size of 6 elements,
 *       or 6 slots. The 6 elements slots are related to the first 6 motion types.
 *       Slot[0] <-> STUDIO_X  // pos x
 *       Slot[1] <-> STUDIO_Y  // pos y
 *       Slot[2] <-> STUDIO_Z  // pos z
 *       Slot[3] <-> STUDIO_XR // rot x
 *       Slot[4] <-> STUDIO_YR // rot y
 *       Slot[5] <-> STUDIO_ZR // rot z
 *
 *       For each slot, bonecontroller stores the index of the bone controller,
 *       with respect to the motion bone used by this bone controller.
 *       If no bone controller is associated to the slot, then the value is -1.
 *
 *       Example:
 *
 *       bonecontroller[0] => -1
 *       bonecontroller[1] => bone controller at [1] has motion type STUDIO_Y.
 *       bonecontroller[2] => -1
 *       bonecontroller[3] => -1
 *       bonecontroller[4] => -1
 *       bonecontroller[5] => bone controller at [5] has motion type STUDIO_ZR.
 *
 *       The first 3 slots of value make up the bone position and the last 3 slots
 *       make up the bone rotations.
 *
 *       The values in scale are used to scale the bone position and rotation,
 *       when reading a compressed animation value data.
 */
enum _:MStudioBone
{
	// 	The name of the bone.
	MStudioBone_name [32],

	// 	The bone's parent index.
	MStudioBone_parent,

	// 	Unused.
	MStudioBone_flags,

	// 	See below.
	MStudioBone_bonecontroller [6],

	// 	See below.
	Float:MStudioBone_value [6],

	// 	The scale value.
	Float:MStudioBone_scale [6],
}


/**
 * @note Bone controllers are used in the game to change the position
 *       or the rotation of one or more bones at run time.
 *
 * @note index is the channel of the bone controller. The following
 *       example shows two bone controllers declared in a SMD.
 *       The index value for the first bone controller would be 0
 *       and the second bone controller's index value would be 4.
 *
 *       $controller 0 "Head bone" XR -60.000000 60.000000  
 *       $controller 4 "Mouth bone" ZR 0.000000 45.000000
 */
enum _:MStudioBoneController
{
	// The bone index.
	MStudioBoneController_bone,

	// The motion type. Can be used in conjunction with STUDIO_RLOOP.
	MStudioBoneController_type,

	// The minimum value.
	Float:MStudioBoneController_start,

	// The maximum value.
	Float:MStudioBoneController_end,

	// The value at rest.
	MStudioBoneController_rest,

	// See below.
	MStudioBoneController_index,
}


enum _:MStudioHitbox
{
	// The bone index.
	MStudioBBox_bone,

	// The hit group.
	MStudioBBox_group,

	// The hitbox min extent.
	Float:MStudioBBox_bbmin [3],

	// The hitbox max extent.
	Float:MStudioBBox_bbmax [3],
}


/**
 * @note actweight is the activity weight. Many sequences may use the same activity, 
 *       but the game will pick the sequence that has the highest actweight.
 *
 * @note The nodeflags is either 0 or 1, where 0 means that the transition to this
 *       sequence can only be made from entrynode to exitnode and 1 means the sequence
 *       transition can also be made in the reverse order, that is exitnode to entrynode.
 *
 * @note Animations:
 *       An animation is used to tell how bones move. A sequence is used to group one
 *       or more animations coherently. Using more than 2 animations per sequences
 *       allows animation blending.
 *
 * @note Animation blending:
 *       Blending refers to interpolating the bone positions and rotations from multiple
 *       animations. Goldsrc supports up to 4 blend animations, but you must chose
 *       either 2 or 4 animations for your blending. The reason is because of how
 *       the game interpolates between the animations. Blend controllers are used 
 *       to determine the influence of each animation.
 *
 * @note Blend controllers:
 *       The blend controllers specify the motion type using blendtype[2], as well as the
 *       range of each blend using blendstart[2] and blendend[2]. A sequence that has 2
 *       animations will only need 1 blend controller, while a sequence that has 4 
 *       animations will use 2 blend controllers.
 *
 *       Here is an example that explains the influence of each blend controller.
 *
 *       Let A1, A2, A3, A4 be the 4 animations of the sequence, and s, t be the blend
 *       factor for the first and second blend controllers. Both s and t are between 0
 *       and 1, inclusively. R is the animation resulting from the blending.
 *
 *       // Blend between the first and second animation using the first blend factor
 *       A = A1 * (1 - s) + A2 * s
 *
 *       // Blend between the third and fourth animation using the first blend factor.
 *       B = A3 * (1 - s) + A4 * s
 *
 *       // Blend between A and B using the second blend factor.
 *       R = A * (1 - t) + B * t
 *
 *       It is important to understand that the purpose of this example is to help
 *       understand the way blend controllers influence the resulting pose of the model.
 *       You cannot directly interpolate a bone's transformation matrix with another.
 *       Orientations need to use Quaternion slerp to interpolate correctly.
 *
 */
enum _:MStudioSequence
{
	// The sequence name.
	MStudioSeq_label [32],

	// Frames per second.
	Float:MStudioSeq_fps,

	// One or more sequence flags.
	MStudioSeq_flags,

	// The activity.
	MStudioSeq_activity,

	// The activity weight.
	MStudioSeq_actweight,

	// The number of animation events.
	MStudioSeq_numevents,

	// The offset of the first animation event chunk.
	MStudioSeq_eventindex,

	// The number of frames.
	MStudioSeq_numframes,

	// Unused.
	MStudioSeq_numpivots,

	// Unused.
	MStudioSeq_pivotindex,

	// The motion type.
	MStudioSeq_motiontype,

	// The motion bone index.
	MStudioSeq_motionbone,

	// The motion bone's displacement from the first frame to the last frame of this sequence.
	Float:MStudioSeq_linearmovement [3],

	// Unused.
	MStudioSeq_automoveposindex,

	// Unused.
	MStudioSeq_automoveangleindex,

	// The sequence bounds min extent.
	Float:MStudioSeq_bbmin [3],

	// The sequence bounds min extent.
	Float:MStudioSeq_bbmax [3],

	// The number of blend controllers.
	MStudioSeq_numblends,

	// The offset of the first animation frame offsets chunk.
	MStudioSeq_animindex,

	// The motion type. One per blend controller.
	MStudioSeq_blendtype [2],

	// The start value. One per blend controller.
	Float:MStudioSeq_blendstart [2],

	// The end value. One per blend controller.
	Float:MStudioSeq_blendend [2],

	// Unused.
	MStudioSeq_blendparent,

	// The sequence group index.
	MStudioSeq_seqgroup,

	// The entry value in the sequence transition graph.
	MStudioSeq_entrynode,

	// The exit value in the sequence transition graph.
	MStudioSeq_exitnode,

	// One or more node flags.
	MStudioSeq_nodeflags,

	// Unused.
	MStudioSeq_nextseq,
}


/**
 * @note Goldsrc allows animation data to be stored in separate 
 *       files and load them on demand at run time. These files
 *       are called sequence group files.
 *
 * @note The sequence group file must be in the same directory
 *       as the main MDL file.
 *
 * @note The file name is always prepended with "models/".
 */
enum _:MStudioSequenceGroup
{
	// The sequence group name.
	MStudioSeqGroup_label [32],

	// The sequence group file name.
	MStudioSeqGroup_name [64],

	// Unused. Was "cache" - index pointer
	MStudioSeqGroup_unused1,

	// Unused. Was "data" - hack for group 0
	MStudioSeqGroup_unused2,
}


/**
 * @note Textures are stored as 8-bit color bitmaps. They are either stored
 *       in the main MDL file, or in an external MDL.
 *
 * @note Each texture chunk has a size of 80 bytes. This does not include 
 *       the size of the pixel data.
 */
enum _:MStudioTexture
{
	//	The texture name.
	MStudioTexture_name [64],

	//	One or more texture flags.
	MStudioTexture_flags,

	//	Width in pixel.
	MStudioTexture_width,

	//	Height in pixel.
	MStudioTexture_height,

	//	The offset of the pixel data.
	MStudioTexture_index,
}


/**
 * @note Bodyparts allow to group models coherently. For example, you could have multiple 
 *       head models for a single bodypart named "heads" and change the head model in
 *       code at runtime.
 *
 * @note base is the divisor used to calculate the index of a model relative to it's bodypart.
 *       In short, it is the process of converting a global model index to a local model index.
 *       Please refer to the code for an example:
 *
 *       index = m_bodynum / pbodypart->base;
 *       index = index % pbodypart->nummodels;
 *
 *       m_pmodel = (mstudiomodel_t *)((byte *)m_pstudiohdr + pbodypart->modelindex) + index;
 */
enum _:MStudioBodyPart
{
	// The name of the bodypart.
	MStudioBodyPart_name [64],

	// The number of Models.
	MStudioBodyPart_nummodels,

	// See above.
	MStudioBodyPart_base,

	// The offset of the first model chunk.
	MStudioBodyPart_modelindex,
}


/**
 * @note Attachments are a position of interest on the model that can be retrieved at runtime in
 *       the game .e.g The gun tip from where to draw the muzzle flash. Each attachment will
 *       move accordingly to the bone it is parented to.
 */
enum _:MStudioAttachment
{
	// Unused.
	MStudioAttachment_name [32],

	// Unused.
	MStudioAttachment_type,

	// The bone index.
	MStudioAttachment_bone,

	// The attachment position. (attachment point)
	Float:MStudioAttachment_org,

	// Unused.
	Float:MStudioAttachment_vectors [3],
}


/**
 * Gets the header informations of a model file.
 * Model parameter must be closed with mdl_studio_close.
 *
 * @note Registered paths ID are (in priority order):
 *         GAME           All paths related to current mod, including fallback
 *                        Depending settings, it includes: <gamedir>_lv/_addon/_<language>/_hd
 *                        and <gamedir> itself
 *         GAMECONFIG     The default writable directory (<gamedir>)
 *         GAMEDOWNLOAD   The download directory (<gamedir>_download)
 *         GAME_FALLBACK  All paths related to fallback game, same as GAME
 *         DEFAULTGAME    All paths related to the default game which is "valve", same as GAME
 *         BASE           The base path where server is installed
 *
 *         Note that some paths are non-writable. It includes all <gamedir>_* (expect _download)
 *         and DEFAULTGAME. Any file inside a non-writable path will be ignored if you try to open
 *         it in writing mode.
 *
 * @param modelPath     The model file path.
 * @param model         Array to store header information.

 * @param use_valve_fs  Optional: If true, the Valve file system will be used instead.
 *                      This can be used to finred files existing in valve
 *                      search paths, rather than solely files existing directly
 *                      in the gamedir.

 * @param valve_path_id Optional: If use_valve_fs, a search path from gameinfo or NULL_STRING for all search paths
 *
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_open(const modelPath[], model[MStudio], bool:use_valve_fs = false, const valve_path_id[] = "GAME")
{
	new file;

	if (!(file = fopen(modelPath, "rb", use_valve_fs, valve_path_id)))
	{
		return false;
	}

	copy(model[MStudio_filePath], charsmax(model[MStudio_filePath]), modelPath);

	model[MStudio_fileHandle] = file;

	fread(file, model[MStudio_id], BLOCK_INT);
	fread(file, model[MStudio_version], BLOCK_INT);

	fread_blocks(file, model[MStudio_name], sizeof(model[MStudio_name]), BLOCK_CHAR);
	fread(file, model[MStudio_length], BLOCK_INT);

	fread_blocks(file, model[MStudio_eyeposition], sizeof(model[MStudio_eyeposition]), BLOCK_INT);
	fread_blocks(file, model[MStudio_min], sizeof(model[MStudio_min]), BLOCK_INT);
	fread_blocks(file, model[MStudio_max], sizeof(model[MStudio_max]), BLOCK_INT);

	fread_blocks(file, model[MStudio_bbmin], sizeof(model[MStudio_bbmin]), BLOCK_INT);
	fread_blocks(file, model[MStudio_bbmax], sizeof(model[MStudio_bbmax]), BLOCK_INT);

	fread(file, model[MStudio_flags], BLOCK_INT);

	fread(file, model[MStudio_numbones], BLOCK_INT);
	fread(file, model[MStudio_boneindex], BLOCK_INT);

	fread(file, model[MStudio_numbonecontrollers], BLOCK_INT);
	fread(file, model[MStudio_bonecontrollerindex], BLOCK_INT);

	fread(file, model[MStudio_numhitboxes], BLOCK_INT);
	fread(file, model[MStudio_hitboxindex], BLOCK_INT);

	fread(file, model[MStudio_numseq], BLOCK_INT);
	fread(file, model[MStudio_seqindex], BLOCK_INT);

	fread(file, model[MStudio_numseqgroups], BLOCK_INT);
	fread(file, model[MStudio_seqgroupindex], BLOCK_INT);

	fread(file, model[MStudio_numtextures], BLOCK_INT);
	fread(file, model[MStudio_textureindex], BLOCK_INT);
	fread(file, model[MStudio_texturedataindex], BLOCK_INT);

	fread(file, model[MStudio_numskinref], BLOCK_INT);
	fread(file, model[MStudio_numskinfamilies], BLOCK_INT);
	fread(file, model[MStudio_skinindex], BLOCK_INT);

	fread(file, model[MStudio_numbodyparts], BLOCK_INT);
	fread(file, model[MStudio_bodypartindex], BLOCK_INT);

	fread(file, model[MStudio_numattachments], BLOCK_INT);
	fread(file, model[MStudio_attachmentindex], BLOCK_INT);

	fread(file, model[MStudio_soundtable], BLOCK_INT);
	fread(file, model[MStudio_soundindex], BLOCK_INT);
	fread(file, model[MStudio_soundgroups], BLOCK_INT);
	fread(file, model[MStudio_soundgroupindex], BLOCK_INT);

	fread(file, model[MStudio_numtransitions], BLOCK_INT);
	fread(file, model[MStudio_transitionindex], BLOCK_INT);

	return true;
}


/**
 * Closes a model file pointer.
 *
 * @note The model file handle will be set to 0.
 *
 * @noreturn
 */
stock mdl_studio_close(model[MStudio])
{
	if (!model[MStudio_fileHandle])
	{
		return;
	}

	fclose(model[MStudio_fileHandle]);

	model[MStudio_fileHandle] = 0;
}


/**
 * Gets a bone information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The bone index, from 0 (inclusive) to model[MStudio_numbones] (exclusive).
 * @param output	The array to store bone information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_bone(model[MStudio], index, output[MStudioBone])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numbones])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_BONE_BYTES + model[MStudio_boneindex], SEEK_SET);

	fread_blocks(file, output[MStudioBone_name], sizeof(output[MStudioBone_name]), BLOCK_CHAR);
	fread(file, output[MStudioBone_parent], BLOCK_INT);
	fread(file, output[MStudioBone_flags], BLOCK_INT);
	fread_blocks(file, output[MStudioBone_bonecontroller], sizeof(output[MStudioBone_bonecontroller]), BLOCK_INT);
	fread_blocks(file, output[MStudioBone_value], sizeof(output[MStudioBone_value]), BLOCK_INT);
	fread_blocks(file, output[MStudioBone_scale], sizeof(output[MStudioBone_scale]), BLOCK_INT);

	return true;
}


/**
 * Gets a bone controller information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The bone controller index, from 0 (inclusive) to model[MStudio_numbonecontrollers] (exclusive).
 * @param output	The array to store bone controller information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_bone_controller(model[MStudio], index, output[MStudioBoneController])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numbonecontrollers])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_BONE_CONTROLLER_BYTES + model[MStudio_bonecontrollerindex], SEEK_SET);

	fread(file, output[MStudioBoneController_bone], BLOCK_INT);
	fread(file, output[MStudioBoneController_type], BLOCK_INT);
	fread(file, output[MStudioBoneController_start], BLOCK_INT);
	fread(file, output[MStudioBoneController_end], BLOCK_INT);
	fread(file, output[MStudioBoneController_rest], BLOCK_INT);
	fread(file, output[MStudioBoneController_index], BLOCK_INT);

	return true;
}


/**
 * Gets a hitbox information.
 *
 * @param model     The model header generated by mdl_studio_open.
 * @param index		The hitbox index, from 0 (inclusive) to model[MStudio_numhitboxes] (exclusive).
 * @param output	The array to store hitbox information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_hitbox(model[MStudio], index, output[MStudioHitbox])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numhitboxes])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_HITBOX_BYTES + model[MStudio_hitboxindex], SEEK_SET);

	fread(file, output[MStudioBBox_bone], BLOCK_INT);
	fread(file, output[MStudioBBox_group], BLOCK_INT);
	fread_blocks(file, output[MStudioBBox_bbmin], sizeof(output[MStudioBBox_bbmin]), BLOCK_INT);
	fread_blocks(file, output[MStudioBBox_bbmax], sizeof(output[MStudioBBox_bbmax]), BLOCK_INT);

	return true;
}


/**
 * Gets a sequence information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The sequence index, from 0 (inclusive) to model[MStudio_numseq] (exclusive).
 * @param output	The array to store sequence information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_sequence(model[MStudio], index, output[MStudioSequence])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numseq])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_SEQUENCE_BYTES + model[MStudio_seqindex], SEEK_SET);

	fread_blocks(file, output[MStudioSeq_label], sizeof(output[MStudioSeq_label]), BLOCK_CHAR);

	fread(file, output[MStudioSeq_fps], BLOCK_INT);
	fread(file, output[MStudioSeq_flags], BLOCK_INT);

	fread(file, output[MStudioSeq_activity], BLOCK_INT);
	fread(file, output[MStudioSeq_actweight], BLOCK_INT);

	fread(file, output[MStudioSeq_numevents], BLOCK_INT);
	fread(file, output[MStudioSeq_eventindex], BLOCK_INT);

	fread(file, output[MStudioSeq_numframes], BLOCK_INT);

	fread(file, output[MStudioSeq_numpivots], BLOCK_INT);
	fread(file, output[MStudioSeq_pivotindex], BLOCK_INT);

	fread(file, output[MStudioSeq_motiontype], BLOCK_INT);
	fread(file, output[MStudioSeq_motionbone], BLOCK_INT);
	fread_blocks(file, output[MStudioSeq_linearmovement], sizeof(output[MStudioSeq_linearmovement]), BLOCK_INT);
	fread(file, output[MStudioSeq_automoveposindex], BLOCK_INT);
	fread(file, output[MStudioSeq_automoveangleindex], BLOCK_INT);

	fread_blocks(file, output[MStudioSeq_bbmin], sizeof(output[MStudioSeq_bbmin]), BLOCK_INT);
	fread_blocks(file, output[MStudioSeq_bbmax], sizeof(output[MStudioSeq_bbmax]), BLOCK_INT);

	fread(file, output[MStudioSeq_numblends], BLOCK_INT);
	fread(file, output[MStudioSeq_animindex], BLOCK_INT);

	fread_blocks(file, output[MStudioSeq_blendtype], sizeof(output[MStudioSeq_blendtype]), BLOCK_INT);
	fread_blocks(file, output[MStudioSeq_blendstart], sizeof(output[MStudioSeq_blendstart]), BLOCK_INT);
	fread_blocks(file, output[MStudioSeq_blendend], sizeof(output[MStudioSeq_blendend]), BLOCK_INT);
	fread(file, output[MStudioSeq_blendparent], BLOCK_INT);

	fread(file, output[MStudioSeq_seqgroup], BLOCK_INT);

	fread(file, output[MStudioSeq_entrynode], BLOCK_INT);
	fread(file, output[MStudioSeq_exitnode], BLOCK_INT);
	fread(file, output[MStudioSeq_nodeflags], BLOCK_INT);

	fread(file, output[MStudioSeq_nextseq], BLOCK_INT);

	return true;
}


/**
 * Gets a sequence group information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The sequence group index, from 0 (inclusive) to model[MStudio_numseqgroups] (exclusive).
 * @param output	The array to store sequence group information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_sequence_group(model[MStudio], index, output[MStudioSequenceGroup])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numseqgroups])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_SEQUENCE_GROUP_BYTES + model[MStudio_seqgroupindex], SEEK_SET);

	fread_blocks(file, output[MStudioSeqGroup_label], sizeof(output[MStudioSeqGroup_label]), BLOCK_CHAR);
	fread_blocks(file, output[MStudioSeqGroup_name], sizeof(output[MStudioSeqGroup_name]), BLOCK_CHAR);
	fread(file, output[MStudioSeqGroup_unused1], BLOCK_INT);
	fread(file, output[MStudioSeqGroup_unused1], BLOCK_INT);

	return true;
}


/**
 * Gets a texture information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The texture index, from 0 (inclusive) to model[MStudio_numtextures] (exclusive).
 * @param output	The array to store texture information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_texture(model[MStudio], index, output[MStudioTexture])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numtextures])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_TEXTURE_BYTES + model[MStudio_textureindex], SEEK_SET);

	fread_blocks(file, output[MStudioTexture_name], sizeof(output[MStudioTexture_name]), BLOCK_CHAR);
	fread(file, output[MStudioTexture_flags], BLOCK_INT);
	fread(file, output[MStudioTexture_width], BLOCK_INT);
	fread(file, output[MStudioTexture_height], BLOCK_INT);
	fread(file, output[MStudioTexture_index], BLOCK_INT);

	return true;
}


/**
 * Gets a body part information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The body part index, from 0 (inclusive) to model[MStudio_numbodyparts] (exclusive).
 * @param output	The array to store texture information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_bodypart(model[MStudio], index, output[MStudioBodyPart])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numbodyparts])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_TEXTURE_BYTES + model[MStudio_bodypartindex], SEEK_SET);

	fread_blocks(file, output[MStudioBodyPart_name], sizeof(output[MStudioBodyPart_name]), BLOCK_CHAR);
	fread(file, output[MStudioBodyPart_nummodels], BLOCK_INT);
	fread(file, output[MStudioBodyPart_base], BLOCK_INT);
	fread(file, output[MStudioBodyPart_modelindex], BLOCK_INT);

	return true;
}


/**
 * Gets an attachment information.
 *
 * @param model		The model header generated by mdl_studio_open.
 * @param index		The attachement index, from 0 (inclusive) to model[MStudio_numattachments] (exclusive).
 * @param output	The array to store texture information.
 *
 * @return Returns true if data could be read. False otherwise.
 */
stock bool:mdl_studio_get_attachment(model[MStudio], index, output[MStudioAttachment])
{
	new file = model[MStudio_fileHandle];

	if (!file || index < 0 || index >= model[MStudio_numattachments])
	{
		return false;
	}

	fseek(file, index * MSTUDIO_TEXTURE_BYTES + model[MStudio_attachmentindex], SEEK_SET);

	fread_blocks(file, output[MStudioAttachment_name], sizeof(output[MStudioAttachment_name]), BLOCK_CHAR);
	fread(file, output[MStudioAttachment_type], BLOCK_INT);
	fread(file, output[MStudioAttachment_bone], BLOCK_INT);
	fread(file, output[MStudioAttachment_org], BLOCK_INT);
	fread_blocks(file, output[MStudioAttachment_vectors], sizeof(output[MStudioAttachment_vectors]), BLOCK_INT);

	return true;
}