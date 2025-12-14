#include "unk_0202F108.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_0202F10C.h"

#include "savedata.h"

int Contest_SaveSize(void)
{
    return sizeof(ContestSaveData);
}

void Contest_Init(ContestSaveData *param0)
{
    int j, i;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 4; j++) {
            param0->unk_00[i][j] = 0;
        }
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_CONTESTS);
}

void sub_0202F134(SaveData *saveData, int param1, int param2)
{
    ContestSaveData *data = SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_CONTESTS);

    if (data->unk_00[param1][param2] < 9999) {
        data->unk_00[param1][param2]++;
    }

    SaveData_SetChecksum(SAVE_TABLE_ENTRY_CONTESTS);
}

u16 sub_0202F160(SaveData *saveData, int param1, int param2)
{
    ContestSaveData *data = SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_CONTESTS);
    SaveData_Checksum(SAVE_TABLE_ENTRY_CONTESTS);

    return data->unk_00[param1][param2];
}
