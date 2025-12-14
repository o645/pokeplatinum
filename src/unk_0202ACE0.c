#include "unk_0202ACE0.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_0202B370.h"
#include "struct_defs/struct_0202B370_sub1.h"

#include "assert.h"
#include "rtc.h"
#include "savedata.h"
#include "strbuf.h"
#include "unk_02038FFC.h"

int WiFiList_SaveSize(void)
{
    return sizeof(WiFiList);
}

void WiFiList_Init(WiFiList *wifiList)
{
    int i;

    MI_CpuClearFast(wifiList, sizeof(WiFiList));

    for (i = 0; i < 32; i++) {
        wifiList->friendTrainerData[i].trainerName[0] = 0xffff;
        wifiList->friendTrainerData[i].unk_00[0] = 0xffff;
        wifiList->friendTrainerData[i].unk_gender = 2;
    }

    sub_02039034(wifiList);
}

DWCUserData *WiFiList_GetUserData(WiFiList *wifiList)
{
    return &(wifiList->userData);
}

u32 sub_0202AD2C(WiFiList *wifiList, int wifiId, int param2)
{
    u32 result;

    GF_ASSERT(wifiId < 32);

    switch (param2) {
    case 0:
        result = wifiList->friendTrainerData[wifiId].unk_20;
        break;
    case 1:
        result = wifiList->friendTrainerData[wifiId].unk_24;
        break;
    case 2:
        result = wifiList->friendTrainerData[wifiId].unk_26;
        break;
    case 3:
        result = wifiList->friendTrainerData[wifiId].unk_28;
        break;
    case 4:
        result = wifiList->friendTrainerData[wifiId].metYear;
        break;
    case 5:
        result = wifiList->friendTrainerData[wifiId].metMonth;
        break;
    case 6:
        result = wifiList->friendTrainerData[wifiId].metDay;
        break;
    case 8:
        result = wifiList->friendTrainerData[wifiId].unk_gender;
        break;
    case 7:
        result = wifiList->friendTrainerData[wifiId].unk_2F;
        break;
    case 9:
        result = wifiList->friendTrainerData[wifiId].unk_30;
        break;
    case 10:
        result = wifiList->friendTrainerData[wifiId].unk_32;
        break;
    case 11:
        result = wifiList->friendTrainerData[wifiId].unk_34;
        break;
    case 12:
        result = wifiList->friendTrainerData[wifiId].unk_36;
        break;
    }

    return result;
}

void sub_0202AE2C(WiFiList *wifiList, int slot, int param2, u32 param3)
{
    GF_ASSERT(slot < 32);

    switch (param2) {
    case 0:
        wifiList->friendTrainerData[slot].unk_20 = param3;
        break;
    case 1:
        GF_ASSERT(0);
        break;
    case 2:
        GF_ASSERT(0);
        break;
    case 3:
        GF_ASSERT(0);
        break;
    case 4:
        wifiList->friendTrainerData[slot].metYear = param3;
        break;
    case 5:
        wifiList->friendTrainerData[slot].metMonth = param3;
        break;
    case 6:
        wifiList->friendTrainerData[slot].metDay = param3;
        break;
    case 8:
        wifiList->friendTrainerData[slot].unk_gender = param3;
        break;
    case 7:
        wifiList->friendTrainerData[slot].unk_2F = param3;
        break;
    case 9:
        GF_ASSERT(0);
        break;
    }
}

DWCFriendData *GetFriendDataById(WiFiList *wifiList, int friendSlot)
{
    GF_ASSERT(friendSlot < 32);
    return &(wifiList->friendData[friendSlot]);
}

u16 *GetFriendTrainerName(WiFiList *wifiList, int friendSlot)
{
    GF_ASSERT(friendSlot < 32);
    return wifiList->friendTrainerData[friendSlot].trainerName;
}

void SetFriendTrainerName(WiFiList *wifiList, int slot, Strbuf *newFriendName)
{
    GF_ASSERT(slot < 32);
    Strbuf_ToChars(newFriendName, wifiList->friendTrainerData[slot].trainerName, sizeof(wifiList->friendTrainerData[slot].trainerName));
}

u16 *sub_0202AF34(WiFiList *wifiList, int param1)
{
    GF_ASSERT(param1 < 32);
    return wifiList->friendTrainerData[param1].unk_00;
}

void sub_0202AF50(WiFiList *wifiList, int slot, Strbuf *param2)
{
    GF_ASSERT(slot < 32);
    Strbuf_ToChars(param2, wifiList->friendTrainerData[slot].unk_00, sizeof(wifiList->friendTrainerData[slot].unk_00));
}

BOOL wifiSlotHasValidFriendData(WiFiList *wifiList, int wifiId)
{
    GF_ASSERT(wifiId < 32);
    return DWC_IsValidFriendData(&wifiList->friendData[wifiId]);
}

int GetTotalValidFriendDataCount(WiFiList *wifiList)
{
    int i, total = 0;

    for (i = 0; i < 32; i++) {
        if (wifiSlotHasValidFriendData(wifiList, i)) {
            total++;
        }
    }

    return total;
}

int sub_0202AFB4(WiFiList *wifiList)
{
    int counter, v1 = 0;

    for (counter = 0; counter < 32; counter++) {
        if (wifiSlotHasValidFriendData(wifiList, counter)) {
            v1 = counter + 1;
        }
    }

    return v1;
}

void sub_0202AFD4(WiFiList *wifiList, int wifiSlot)
{
    int i;

    GF_ASSERT(wifiSlot < 32);

    for (i = wifiSlot; i < (32 - 1); i++) {
        MI_CpuCopy8(&wifiList->friendTrainerData[i + 1], &wifiList->friendTrainerData[i], sizeof(FriendTrainerData));
        MI_CpuCopy8(&wifiList->friendData[i + 1], &wifiList->friendData[i], sizeof(DWCFriendData));
    }

    i = 32 - 1;

    MI_CpuClearFast(&wifiList->friendTrainerData[i], sizeof(FriendTrainerData));
    MI_CpuClearFast(&wifiList->friendData[i], sizeof(DWCFriendData));

    wifiList->friendTrainerData[i].trainerName[0] = 0xffff;
    wifiList->friendTrainerData[i].unk_00[0] = 0xffff;
    wifiList->friendTrainerData[i].unk_gender = 2;
}

static void sub_0202B088(WiFiList *wifiList, int destSlot, int srcSlot)
{
    int v0;

    MI_CpuCopy8(&wifiList->friendTrainerData[srcSlot], &wifiList->friendTrainerData[destSlot], sizeof(FriendTrainerData));
    MI_CpuCopy8(&wifiList->friendData[srcSlot], &wifiList->friendData[destSlot], sizeof(DWCFriendData));
    MI_CpuClearFast(&wifiList->friendTrainerData[srcSlot], sizeof(FriendTrainerData));
    MI_CpuClearFast(&wifiList->friendData[srcSlot], sizeof(DWCFriendData));

    wifiList->friendTrainerData[srcSlot].trainerName[0] = 0xffff;
    wifiList->friendTrainerData[srcSlot].unk_00[0] = 0xffff;
    wifiList->friendTrainerData[srcSlot].unk_gender = 2;
}

void sub_0202B0F8(WiFiList *wifiList)
{
    int i, v1 = -1;

    for (i = 0; i < 32; i++) {
        if (wifiSlotHasValidFriendData(wifiList, i)) {
            if (v1 != -1) {
                sub_0202B088(wifiList, v1, i);

                i = -1;
                v1 = -1;
            }
        } else {
            if (v1 == -1) {
                v1 = i;
            }
        }
    }
}

void sub_0202B13C(WiFiList *wifiList, int wifiId)
{
    RTCDate rtcDate;

    GetCurrentDate(&rtcDate);

    wifiList->friendTrainerData[wifiId].metYear = rtcDate.year + 2000;
    wifiList->friendTrainerData[wifiId].metMonth = rtcDate.month;
    wifiList->friendTrainerData[wifiId].metDay = rtcDate.day;
}

void sub_0202B174(WiFiList *wifiList, int wifiId, int param2, int param3, int param4)
{
    wifiList->friendTrainerData[wifiId].unk_24 += param2;

    if (wifiList->friendTrainerData[wifiId].unk_24 > 9999) {
        wifiList->friendTrainerData[wifiId].unk_24 = 9999;
    }

    wifiList->friendTrainerData[wifiId].unk_26 += param3;

    if (wifiList->friendTrainerData[wifiId].unk_26 > 9999) {
        wifiList->friendTrainerData[wifiId].unk_26 = 9999;
    }

    wifiList->friendTrainerData[wifiId].unk_28 += param4;

    if (wifiList->friendTrainerData[wifiId].unk_28 > 9999) {
        wifiList->friendTrainerData[wifiId].unk_28 = 9999;
    }

    sub_0202B13C(wifiList, wifiId);
}

void sub_0202B1D0(WiFiList *wifiList, int param1, int param2)
{
    wifiList->friendTrainerData[param1].unk_30 += param2;

    if (wifiList->friendTrainerData[param1].unk_30 > 9999) {
        wifiList->friendTrainerData[param1].unk_30 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B1F8(WiFiList *wifiList, int param1, int param2)
{
    wifiList->friendTrainerData[param1].unk_32 += param2;

    if (wifiList->friendTrainerData[param1].unk_32 > 9999) {
        wifiList->friendTrainerData[param1].unk_32 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B220(WiFiList *wifiList, int param1, int param2)
{
    wifiList->friendTrainerData[param1].unk_34 += param2;

    if (wifiList->friendTrainerData[param1].unk_34 > 9999) {
        wifiList->friendTrainerData[param1].unk_34 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B248(WiFiList *wifiList, int param1, int param2)
{
    wifiList->friendTrainerData[param1].unk_36 += param2;

    if (wifiList->friendTrainerData[param1].unk_36 > 9999) {
        wifiList->friendTrainerData[param1].unk_36 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B270(WiFiList *param0, int param1, int param2)
{
    param0->friendTrainerData[param2].unk_24 += param0->friendTrainerData[param1].unk_24;

    if (param0->friendTrainerData[param2].unk_24 > 9999) {
        param0->friendTrainerData[param2].unk_24 = 9999;
    }

    param0->friendTrainerData[param2].unk_26 += param0->friendTrainerData[param1].unk_26;

    if (param0->friendTrainerData[param2].unk_26 > 9999) {
        param0->friendTrainerData[param2].unk_26 = 9999;
    }

    param0->friendTrainerData[param2].unk_28 += param0->friendTrainerData[param1].unk_28;

    if (param0->friendTrainerData[param2].unk_28 > 9999) {
        param0->friendTrainerData[param2].unk_28 = 9999;
    }

    param0->friendTrainerData[param2].unk_30 += param0->friendTrainerData[param1].unk_30;

    if (param0->friendTrainerData[param2].unk_30 > 9999) {
        param0->friendTrainerData[param2].unk_30 = 9999;
    }

    param0->friendTrainerData[param2].unk_32 += param0->friendTrainerData[param1].unk_32;

    if (param0->friendTrainerData[param2].unk_32 > 9999) {
        param0->friendTrainerData[param2].unk_32 = 9999;
    }

    param0->friendTrainerData[param2].unk_34 += param0->friendTrainerData[param1].unk_34;

    if (param0->friendTrainerData[param2].unk_34 > 9999) {
        param0->friendTrainerData[param2].unk_34 = 9999;
    }

    param0->friendTrainerData[param2].unk_36 += param0->friendTrainerData[param1].unk_36;

    if (param0->friendTrainerData[param2].unk_36 > 9999) {
        param0->friendTrainerData[param2].unk_36 = 9999;
    }

    MI_CpuCopyFast(param0->friendTrainerData[param1].unk_00, param0->friendTrainerData[param2].unk_00, (sizeof(u16) * (7 + 1)));
    MI_CpuClearFast(&param0->friendTrainerData[param1], sizeof(FriendTrainerData));

    param0->friendTrainerData[param1].trainerName[0] = 0xffff;
    param0->friendTrainerData[param1].unk_00[0] = 0xffff;
    param0->friendTrainerData[param1].unk_gender = 2;
}

WiFiList *SaveData_GetWiFiList(SaveData *saveData)
{
    return SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_WIFI_LIST);
}
