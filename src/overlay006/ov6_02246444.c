#include "overlay006/ov6_02246444.h"

#include <nitro.h>
#include <string.h>

#include "constants/tv_broadcast.h"

#include "struct_decls/struct_0202440C_decl.h"
#include "struct_decls/struct_0202E4D4_decl.h"
#include "struct_decls/struct_0202E768_decl.h"
#include "struct_decls/struct_0202E794_decl.h"

#include "field/field_system.h"
#include "savedata/save_table.h"

#include "charcode_util.h"
#include "field_battle_data_transfer.h"
#include "heap.h"
#include "save_player.h"
#include "trainer_info.h"
#include "unk_0202E2CC.h"

struct UnkStruct_ov6_022465F4_t {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 trainerGender;
    u16 trainerName[8];
    UnkStruct_0202E4D4 *unk_14;
};

static void TVSegmentData_Clear(TvSegmentData *segmentData)
{
    MI_CpuClear8(segmentData, sizeof(TvSegmentData));
}

static void TvSegmentData_SetGender(TvSegmentData *segmentData, int gender)
{
    segmentData->trainerGender = gender;
}

static void TvSegmentData_SetLang(TvSegmentData *segmentData, int language)
{
    segmentData->unk_02 = language;
}

static void TvSegmentData_SetGameVersion(TvSegmentData *segmentData, int gameVersion)
{
    segmentData->unk_01 = gameVersion;
}

static void TvSegmentData_SetTrainerName(TvSegmentData *segment, const u16 *name)
{
    CharCode_CopyNumChars(segment->trainerName, name, 7 + 1);
}

static void ov6_02246468(TvSegmentData *segment, UnkStruct_0202E4D4 *param1)
{
    segment->unk_00 = sub_0202E55C(param1);
    segment->unk_14 = param1;
}

void ov6_0224647C(TvSegmentData *param0)
{
    if (param0->unk_14 != NULL) {
        sub_0202E560(param0->unk_14);
    }
}

int ov6_0224648C(const TvSegmentData *param0)
{
    return param0->trainerGender;
}

int ov6_02246490(const TvSegmentData *param0)
{
    return param0->unk_02;
}

const u16 *ov6_02246494(const TvSegmentData *param0)
{
    return param0->trainerName;
}

void *ov6_02246498(TvSegmentData *param0)
{
    return sub_0202E574(param0->unk_14);
}

int ov6_022464A4(const TvSegmentData *param0)
{
    return param0->unk_00;
}

static TvSegmentData *ov6_022464A8(FieldSystem *fieldSystem, UnkStruct_0202E794 *param1)
{
    TvSegmentData *v0 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(TvSegmentData));

    TVSegmentData_Clear(v0);
    TvSegmentData_SetTrainerName(v0, sub_0202E4C8(param1));
    TvSegmentData_SetLang(v0, sub_0202E4CC(param1));
    TvSegmentData_SetGameVersion(v0, sub_0202E4D0(param1));
    ov6_02246468(v0, sub_0202E4D4(param1));

    return v0;
}

static TvSegmentData *ov6_022464F8(FieldSystem *fieldSystem, UnkStruct_0202E768 *param1)
{
    TrainerInfo *trainerInfo = SaveData_GetTrainerInfo(fieldSystem->saveData);
    TvSegmentData *segment = Heap_Alloc(HEAP_ID_FIELD1, sizeof(TvSegmentData));

    TVSegmentData_Clear(segment);
    TvSegmentData_SetTrainerName(segment, TrainerInfo_Name(trainerInfo));
    TvSegmentData_SetGender(segment, TrainerInfo_Gender(trainerInfo));
    TvSegmentData_SetLang(segment, GAME_LANGUAGE);
    TvSegmentData_SetGameVersion(segment, GAME_VERSION);
    ov6_02246468(segment, sub_0202E4D8(param1));

    return segment;
}

static TvSegmentData *ov6_02246550(FieldSystem *fieldSystem, int param1)
{
    TrainerInfo *trainerInfo = SaveData_GetTrainerInfo(fieldSystem->saveData);
    TvSegmentData *segmentData = Heap_Alloc(HEAP_ID_FIELD1, sizeof(TvSegmentData));

    TVSegmentData_Clear(segmentData);
    segmentData->unk_00 = param1;
    TvSegmentData_SetTrainerName(segmentData, TrainerInfo_Name(trainerInfo));
    TvSegmentData_SetGender(segmentData, TrainerInfo_Gender(trainerInfo));
    TvSegmentData_SetLang(segmentData, GAME_LANGUAGE);
    TvSegmentData_SetGameVersion(segmentData, GAME_VERSION);

    segmentData->unk_14 = NULL;
    return segmentData;
}

TvSegmentData *ov6_022465A0(FieldSystem *fieldSystem, int programType, int param2)
{
    TVBroadcast *broadcast = SaveData_GetTVBroadcast(fieldSystem->saveData);

    if ((programType == TV_PROGRAM_TYPE_SINNOH_NOW) || (programType == TV_PROGRAM_TYPE_VARIETY_HOUR)) {
        return ov6_02246550(fieldSystem, param2);
    }

    if (sub_0202E7C0(param2) == 0) {
        UnkStruct_0202E794 *v1 = sub_0202E794(broadcast, programType, param2);
        return ov6_022464A8(fieldSystem, v1);
    } else {
        UnkStruct_0202E768 *v2 = sub_0202E768(broadcast, programType, param2);
        return ov6_022464F8(fieldSystem, v2);
    }
}

void ov6_FreeTvSegment(TvSegmentData *segment)
{
    Heap_Free(segment);
}
