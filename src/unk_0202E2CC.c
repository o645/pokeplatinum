#include "unk_0202E2CC.h"

#include <nitro.h>
#include <string.h>

#include "constants/tv_broadcast.h"

#include "struct_defs/struct_0202440C.h"
#include "struct_defs/struct_0202E4D4.h"
#include "struct_defs/struct_0202E768.h"
#include "struct_defs/struct_0202E794.h"
#include "struct_defs/struct_0202E7D8.h"
#include "struct_defs/struct_0202E7E4.h"
#include "struct_defs/struct_0202E7F0.h"
#include "struct_defs/struct_0202E7FC.h"
#include "struct_defs/struct_0202E808.h"
#include "struct_defs/struct_0202E810.h"
#include "struct_defs/struct_0202E81C.h"
#include "struct_defs/struct_0202E828.h"
#include "struct_defs/struct_0202E834.h"

#include "inlines.h"
#include "rtc.h"
#include "savedata.h"

static void TVBroadcast_ClearPlayedSegments(TVBroadcast *broadcast);
static UnkStruct_0202E768 *sub_0202E4DC(TVBroadcast *broadcast, int param1);

int TVBroadcast_SaveSize(void)
{
    return sizeof(TVBroadcast);
}

void TVBroadcast_Init(TVBroadcast *broadcast)
{
    MI_CpuClearFast(broadcast, sizeof(TVBroadcast));
    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

void TVBoardcast_Clear(TVBroadcast *broadcast)
{
    MI_CpuClearFast(broadcast->trainerSighting, sizeof(UnkStruct_0202E768) * 4);
    MI_CpuClearFast(broadcast->record, sizeof(UnkStruct_0202E768) * 4);
    MI_CpuClearFast(broadcast->interviewData, sizeof(UnkStruct_0202E768) * 4);

    TVBroadcast_ClearWatchProgress(broadcast);
    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

void TVBroadcast_UpdateProgramTimeSlot(TVBroadcast *broadcast, int deltaMinutes, int currentMinute)
{
    int i;

    if (broadcast->timeSlotMinutesRemaining > deltaMinutes) {
        broadcast->timeSlotMinutesRemaining -= deltaMinutes;
    } else {
        broadcast->timeSlotMinutesRemaining = 15 - currentMinute % 15;

        if (broadcast->timeSlotMinutesRemaining == 0) {
            broadcast->timeSlotMinutesRemaining = 15;
        }

        broadcast->programFinished = FALSE;

        for (i = 0; i < TV_BROADCAST_MAX_PLAYED_SEGMENTS; i++) {
            broadcast->playedSegments[i] = 0;
        }
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

void TVBroadcast_ClearWatchProgress(TVBroadcast *broadcast)
{
    TVBroadcast_SetProgramFinished(broadcast, FALSE);
    TVBroadcast_ClearPlayedSegments(broadcast);
    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

void TVBroadcast_SetProgramFinished(TVBroadcast *broadcast, BOOL finished)
{
    broadcast->programFinished = finished;
    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

BOOL TVBroadcast_IsProgramFinished(const TVBroadcast *broadcast)
{
    return broadcast->programFinished;
}

void TVBroadcast_SetPlayedSegment(TVBroadcast *broadcast, int segmentID)
{
    int i;

    for (i = 0; i < TV_BROADCAST_MAX_PLAYED_SEGMENTS; i++) {
        if (broadcast->playedSegments[i] == NULL) {
            broadcast->playedSegments[i] = segmentID;
            SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
            return;
        }
    }

    GF_ASSERT(FALSE);

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

static void TVBroadcast_ClearPlayedSegments(TVBroadcast *broadcast)
{
    int i;

    for (i = 0; i < TV_BROADCAST_MAX_PLAYED_SEGMENTS; i++) {
        broadcast->playedSegments[i] = 0;
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

BOOL TVBroadcast_IsPlayedSegment(const TVBroadcast *broadcast, int segmentID)
{
    int i;

    for (i = 0; i < TV_BROADCAST_MAX_PLAYED_SEGMENTS; i++) {
        if (broadcast->playedSegments[i] == segmentID) {
            return TRUE;
        }
    }

    return FALSE;
}

int TVBroadcast_CountPlayedSegments(const TVBroadcast *broadcast)
{
    int i, playedCount;

    for (i = 0, playedCount = 0; i < TV_BROADCAST_MAX_PLAYED_SEGMENTS; i++) {
        if (broadcast->playedSegments[i] != 0) {
            playedCount++;
        }
    }

    return playedCount;
}

static void sub_0202E3F4(UnkStruct_0202E4D4 *param0, int param1, const u8 *param2)
{
    RTCDate date;

    GetCurrentDate(&date);

    param0->date = Date_Encode(&date);
    param0->unk_00 = param1;
    param0->unk_01 = 0;

    MI_CpuCopyFast(param2, param0->unk_08, 40);
    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

BOOL TVBroadcast_SaveSegmentData(TVBroadcast *broadcast, int programTypeId, int segmentId, const u8 *segment)
{
    int i;
    UnkStruct_0202E768 *v1 = sub_0202E4DC(broadcast, programTypeId);

    for (i = 0; i < 4; i++) {
        if (v1[i].unk_00.unk_00 == segmentId) {
            if (v1[i].unk_00.unk_01 >= 3) {
                sub_0202E3F4(&v1[i].unk_00, segmentId, segment);
                return 1;
            }

            return 0;
        }
    }

    for (i = 0; i < 4; i++) {
        if (v1[i].unk_00.unk_00 == 0) {
            sub_0202E3F4(&v1[i].unk_00, segmentId, segment);
            return 1;
        }
    }

    for (i = 0; i < 4; i++) {
        if (v1[i].unk_00.unk_01 >= 3) {
            sub_0202E3F4(&v1[i].unk_00, segmentId, segment);
            return 1;
        }
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);

    return 0;
}

const u16 *sub_0202E4C8(const UnkStruct_0202E794 *param0)
{
    return param0->unk_08;
}

int sub_0202E4CC(const UnkStruct_0202E794 *param0)
{
    return param0->unk_06;
}

int sub_0202E4D0(const UnkStruct_0202E794 *param0)
{
    return param0->unk_05;
}

UnkStruct_0202E4D4 *sub_0202E4D4(UnkStruct_0202E794 *param0)
{
    return &param0->unk_18;
}

UnkStruct_0202E4D4 *sub_0202E4D8(UnkStruct_0202E768 *param0)
{
    return &param0->unk_00;
}

static UnkStruct_0202E768 *sub_0202E4DC(TVBroadcast *broadcast, int programType)
{
    UnkStruct_0202E768 *res = NULL;

    switch (programType) {
    case TV_PROGRAM_TYPE_INTERVIEWS:
        res = broadcast->interviewData;
        break;
    case TV_PROGRAM_TYPE_TRAINER_SIGHTINGS:
        res = broadcast->trainerSighting;
        break;
    case TV_PROGRAM_TYPE_RECORDS:
        res = broadcast->record;
        break;
    case TV_PROGRAM_TYPE_SINNOH_NOW:
    case TV_PROGRAM_TYPE_VARIETY_HOUR:
        GF_ASSERT(0);
    }

    return res;
}

static UnkStruct_0202E794 *sub_0202E518(TVBroadcast *broadcast, int programType)
{
    UnkStruct_0202E794 *res = NULL;

    switch (programType) {
    case 2:
        res = broadcast->unk_234;
        break;
    case 3:
        res = broadcast->unk_684;
        break;
    case 1:
        res = broadcast->unk_8AC;
        break;
    case 4:
    case 5:
        GF_ASSERT(0);
    }

    return res;
}

int sub_0202E55C(const UnkStruct_0202E4D4 *param0)
{
    return param0->unk_00;
}

void sub_0202E560(UnkStruct_0202E4D4 *param0)
{
    if (param0->unk_01 < 3) {
        param0->unk_01++;
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_TV_BROADCAST);
}

void *sub_0202E574(UnkStruct_0202E4D4 *param0)
{
    return param0->unk_08;
}

static int sub_0202E578(const UnkStruct_0202E768 *segmentData, int param1, int param2, BOOL param3, u8 *param4)
{
    int i, count;

    for (count = 0, i = 0; i < param1; i++) {
        if (segmentData[i].unk_00.unk_00 == param2) {
            int v2 = segmentData[i].unk_00.unk_01;

            if (param3 && v2) {
                param4[count] = i + 1;
                count++;
            } else if (!param3 && (v2 == 0)) {
                param4[count] = i + 1;
                count++;
            }
        }
    }

    return count;
}

static int sub_0202E5B8(const UnkStruct_0202E794 *param0, int param1, int param2, BOOL param3, u8 *param4)
{
    int v0, v1;

    for (v1 = 0, v0 = 0; v0 < param1; v0++) {
        int v2 = param0[v0].unk_18.unk_01;

        if (param0[v0].unk_18.unk_00 == param2) {
            if (param3 && v2) {
                param4[v1] = sub_0202E7D0(v0 + 1);
                v1++;
            } else if (!param3 && (v2 == 0)) {
                param4[v1] = sub_0202E7D0(v0 + 1);
                v1++;
            }
        }
    }

    return v1;
}

int sub_0202E614(const TVBroadcast *broadcast, int programType, int segmentId, BOOL param3, BOOL param4, u8 *loadedPendingSegments)
{
    switch (programType) {
    case 2:
        if (param3) {
            return sub_0202E578(broadcast->trainerSighting, 4, segmentId, param4, loadedPendingSegments);
        } else {
            return sub_0202E5B8(broadcast->unk_234, 16, segmentId, param4, loadedPendingSegments);
        }
    case 3:
        if (param3) {
            return sub_0202E578(broadcast->record, 4, segmentId, param4, loadedPendingSegments);
        } else {
            return sub_0202E5B8(broadcast->unk_684, 8, segmentId, param4, loadedPendingSegments);
        }
    case 1:
        if (param3) {
            return sub_0202E578(broadcast->interviewData, 4, segmentId, param4, loadedPendingSegments);
        } else {
            return sub_0202E5B8(broadcast->unk_8AC, 8, segmentId, param4, loadedPendingSegments);
        }
    case 4:
        return 0;
    case 5:
        return 0;
    }

    return 0;
}

BOOL sub_0202E6B0(TVBroadcast *broadcast, int param1, int param2)
{
    int v0;
    int i;
    u8 v2[4];
    UnkStruct_0202E768 *v3;

    MI_CpuClear8(v2, 4);

    v0 = sub_0202E614(broadcast, param1, param2, 1, 0, v2);

    if (v0 != 0) {
        return 0;
    }

    v0 = sub_0202E614(broadcast, param1, param2, 1, 1, v2);

    if (v0 != 0) {
        for (i = 0; i < 4 & v2[i] != 0; i++) {
            v3 = sub_0202E768(broadcast, param1, v2[i]);

            if (v3->unk_00.unk_01 >= 3) {
                return 1;
            }
        }

        return 0;
    }

    for (i = 1; i <= 4; i++) {
        v3 = sub_0202E768(broadcast, param1, i);

        if ((v3->unk_00.unk_00 == 0) || (v3->unk_00.unk_01 >= 3)) {
            return 1;
        }
    }

    return 0;
}

UnkStruct_0202E768 *sub_0202E768(TVBroadcast *broadcast, int param1, int param2)
{
    UnkStruct_0202E768 *v0;

    GF_ASSERT(sub_0202E7C0(param2) == 1);

    param2 &= ~0x80;
    v0 = sub_0202E4DC(broadcast, param1);

    return &v0[param2 - 1];
}

UnkStruct_0202E794 *sub_0202E794(TVBroadcast *broadcast, int programType, int param2)
{
    UnkStruct_0202E794 *v0;

    GF_ASSERT(sub_0202E7C0(param2) == 0);

    param2 &= ~0x80;
    v0 = sub_0202E518(broadcast, programType);

    return &v0[param2 - 1];
}

BOOL sub_0202E7C0(int param0)
{
    if (param0 & 0x80) {
        return 0;
    } else {
        return 1;
    }
}

int sub_0202E7D0(int param0)
{
    return param0 | 0x80;
}

UnkStruct_0202E7D8 *sub_0202E7D8(TVBroadcast *broadcast)
{
    return &broadcast->unk_AD4;
}

UnkStruct_0202E7E4 *sub_0202E7E4(TVBroadcast *broadcast)
{
    return &broadcast->unk_ADE;
}

UnkStruct_0202E7F0 *sub_0202E7F0(TVBroadcast *broadcast)
{
    return &broadcast->unk_B02;
}

UnkStruct_0202E7FC *sub_0202E7FC(TVBroadcast *broadcast)
{
    return &broadcast->unk_B04;
}

UnkStruct_0202E808 *TVBroadcast_GetSafariGameData(TVBroadcast *broadcast)
{
    return &broadcast->safariGame;
}

UnkStruct_0202E810 *sub_0202E810(TVBroadcast *broadcast)
{
    return &broadcast->unk_B10;
}

UnkStruct_0202E81C *sub_0202E81C(TVBroadcast *broadcast)
{
    return &broadcast->unk_B2E;
}

UnkStruct_0202E828 *sub_0202E828(TVBroadcast *broadcast)
{
    return &broadcast->unk_B44;
}

UnkStruct_0202E834 *sub_0202E834(TVBroadcast *broadcast)
{
    return &broadcast->unk_B4C;
}
