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
        wifiList->unk_1C0[i].unk_10[0] = 0xffff;
        wifiList->unk_1C0[i].unk_00[0] = 0xffff;
        wifiList->unk_1C0[i].unk_2E = 2;
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
        result = wifiList->unk_1C0[wifiId].unk_20;
        break;
    case 1:
        result = wifiList->unk_1C0[wifiId].unk_24;
        break;
    case 2:
        result = wifiList->unk_1C0[wifiId].unk_26;
        break;
    case 3:
        result = wifiList->unk_1C0[wifiId].unk_28;
        break;
    case 4:
        result = wifiList->unk_1C0[wifiId].year;
        break;
    case 5:
        result = wifiList->unk_1C0[wifiId].month;
        break;
    case 6:
        result = wifiList->unk_1C0[wifiId].day;
        break;
    case 8:
        result = wifiList->unk_1C0[wifiId].unk_2E;
        break;
    case 7:
        result = wifiList->unk_1C0[wifiId].unk_2F;
        break;
    case 9:
        result = wifiList->unk_1C0[wifiId].unk_30;
        break;
    case 10:
        result = wifiList->unk_1C0[wifiId].unk_32;
        break;
    case 11:
        result = wifiList->unk_1C0[wifiId].unk_34;
        break;
    case 12:
        result = wifiList->unk_1C0[wifiId].unk_36;
        break;
    }

    return result;
}

void sub_0202AE2C(WiFiList *wifiList, int param1, int param2, u32 param3)
{
    GF_ASSERT(param1 < 32);

    switch (param2) {
    case 0:
        wifiList->unk_1C0[param1].unk_20 = param3;
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
        wifiList->unk_1C0[param1].year = param3;
        break;
    case 5:
        wifiList->unk_1C0[param1].month = param3;
        break;
    case 6:
        wifiList->unk_1C0[param1].day = param3;
        break;
    case 8:
        wifiList->unk_1C0[param1].unk_2E = param3;
        break;
    case 7:
        wifiList->unk_1C0[param1].unk_2F = param3;
        break;
    case 9:
        GF_ASSERT(0);
        break;
    }
}

DWCFriendData *GetFriendDataById(WiFiList *wifiList, int wifiId)
{
    GF_ASSERT(wifiId < 32);
    return &(wifiList->friendData[wifiId]);
}

u16 *GetFriendTrainerName(WiFiList *param0, int param1)
{
    GF_ASSERT(param1 < 32);
    return param0->unk_1C0[param1].unk_10;
}

void sub_0202AF0C(WiFiList *param0, int param1, Strbuf *param2)
{
    GF_ASSERT(param1 < 32);
    Strbuf_ToChars(param2, param0->unk_1C0[param1].unk_10, sizeof(param0->unk_1C0[param1].unk_10));
}

u16 *sub_0202AF34(WiFiList *param0, int param1)
{
    GF_ASSERT(param1 < 32);
    return param0->unk_1C0[param1].unk_00;
}

void sub_0202AF50(WiFiList *param0, int param1, Strbuf *param2)
{
    GF_ASSERT(param1 < 32);
    Strbuf_ToChars(param2, param0->unk_1C0[param1].unk_00, sizeof(param0->unk_1C0[param1].unk_00));
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

int sub_0202AFB4(WiFiList *param0)
{
    int i, v1 = 0;

    for (i = 0; i < 32; i++) {
        if (wifiSlotHasValidFriendData(param0, i)) {
            v1 = i + 1;
        }
    }

    return v1;
}

void sub_0202AFD4(WiFiList *wifiList, int wifiId)
{
    int i;

    GF_ASSERT(wifiId < 32);

    for (i = wifiId; i < (32 - 1); i++) {
        MI_CpuCopy8(&wifiList->unk_1C0[i + 1], &wifiList->unk_1C0[i], sizeof(UnkStruct_0202B370_sub1));
        MI_CpuCopy8(&wifiList->friendData[i + 1], &wifiList->friendData[i], sizeof(DWCFriendData));
    }

    i = 32 - 1;

    MI_CpuClearFast(&wifiList->unk_1C0[i], sizeof(UnkStruct_0202B370_sub1));
    MI_CpuClearFast(&wifiList->friendData[i], sizeof(DWCFriendData));

    wifiList->unk_1C0[i].unk_10[0] = 0xffff;
    wifiList->unk_1C0[i].unk_00[0] = 0xffff;
    wifiList->unk_1C0[i].unk_2E = 2;
}

static void sub_0202B088(WiFiList *param0, int param1, int param2)
{
    int v0;

    MI_CpuCopy8(&param0->unk_1C0[param2], &param0->unk_1C0[param1], sizeof(UnkStruct_0202B370_sub1));
    MI_CpuCopy8(&param0->friendData[param2], &param0->friendData[param1], sizeof(DWCFriendData));
    MI_CpuClearFast(&param0->unk_1C0[param2], sizeof(UnkStruct_0202B370_sub1));
    MI_CpuClearFast(&param0->friendData[param2], sizeof(DWCFriendData));

    param0->unk_1C0[param2].unk_10[0] = 0xffff;
    param0->unk_1C0[param2].unk_00[0] = 0xffff;
    param0->unk_1C0[param2].unk_2E = 2;
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

    wifiList->unk_1C0[wifiId].year = rtcDate.year + 2000;
    wifiList->unk_1C0[wifiId].month = rtcDate.month;
    wifiList->unk_1C0[wifiId].day = rtcDate.day;
}

void sub_0202B174(WiFiList *wifiList, int wifiId, int param2, int param3, int param4)
{
    wifiList->unk_1C0[wifiId].unk_24 += param2;

    if (wifiList->unk_1C0[wifiId].unk_24 > 9999) {
        wifiList->unk_1C0[wifiId].unk_24 = 9999;
    }

    wifiList->unk_1C0[wifiId].unk_26 += param3;

    if (wifiList->unk_1C0[wifiId].unk_26 > 9999) {
        wifiList->unk_1C0[wifiId].unk_26 = 9999;
    }

    wifiList->unk_1C0[wifiId].unk_28 += param4;

    if (wifiList->unk_1C0[wifiId].unk_28 > 9999) {
        wifiList->unk_1C0[wifiId].unk_28 = 9999;
    }

    sub_0202B13C(wifiList, wifiId);
}

void sub_0202B1D0(WiFiList *wifiList, int param1, int param2)
{
    wifiList->unk_1C0[param1].unk_30 += param2;

    if (wifiList->unk_1C0[param1].unk_30 > 9999) {
        wifiList->unk_1C0[param1].unk_30 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B1F8(WiFiList *wifiList, int param1, int param2)
{
    wifiList->unk_1C0[param1].unk_32 += param2;

    if (wifiList->unk_1C0[param1].unk_32 > 9999) {
        wifiList->unk_1C0[param1].unk_32 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B220(WiFiList *wifiList, int param1, int param2)
{
    wifiList->unk_1C0[param1].unk_34 += param2;

    if (wifiList->unk_1C0[param1].unk_34 > 9999) {
        wifiList->unk_1C0[param1].unk_34 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B248(WiFiList *wifiList, int param1, int param2)
{
    wifiList->unk_1C0[param1].unk_36 += param2;

    if (wifiList->unk_1C0[param1].unk_36 > 9999) {
        wifiList->unk_1C0[param1].unk_36 = 9999;
    }

    sub_0202B13C(wifiList, param1);
}

void sub_0202B270(WiFiList *param0, int param1, int param2)
{
    param0->unk_1C0[param2].unk_24 += param0->unk_1C0[param1].unk_24;

    if (param0->unk_1C0[param2].unk_24 > 9999) {
        param0->unk_1C0[param2].unk_24 = 9999;
    }

    param0->unk_1C0[param2].unk_26 += param0->unk_1C0[param1].unk_26;

    if (param0->unk_1C0[param2].unk_26 > 9999) {
        param0->unk_1C0[param2].unk_26 = 9999;
    }

    param0->unk_1C0[param2].unk_28 += param0->unk_1C0[param1].unk_28;

    if (param0->unk_1C0[param2].unk_28 > 9999) {
        param0->unk_1C0[param2].unk_28 = 9999;
    }

    param0->unk_1C0[param2].unk_30 += param0->unk_1C0[param1].unk_30;

    if (param0->unk_1C0[param2].unk_30 > 9999) {
        param0->unk_1C0[param2].unk_30 = 9999;
    }

    param0->unk_1C0[param2].unk_32 += param0->unk_1C0[param1].unk_32;

    if (param0->unk_1C0[param2].unk_32 > 9999) {
        param0->unk_1C0[param2].unk_32 = 9999;
    }

    param0->unk_1C0[param2].unk_34 += param0->unk_1C0[param1].unk_34;

    if (param0->unk_1C0[param2].unk_34 > 9999) {
        param0->unk_1C0[param2].unk_34 = 9999;
    }

    param0->unk_1C0[param2].unk_36 += param0->unk_1C0[param1].unk_36;

    if (param0->unk_1C0[param2].unk_36 > 9999) {
        param0->unk_1C0[param2].unk_36 = 9999;
    }

    MI_CpuCopyFast(param0->unk_1C0[param1].unk_00, param0->unk_1C0[param2].unk_00, (sizeof(u16) * (7 + 1)));
    MI_CpuClearFast(&param0->unk_1C0[param1], sizeof(UnkStruct_0202B370_sub1));

    param0->unk_1C0[param1].unk_10[0] = 0xffff;
    param0->unk_1C0[param1].unk_00[0] = 0xffff;
    param0->unk_1C0[param1].unk_2E = 2;
}

WiFiList *SaveData_GetWiFiList(SaveData *saveData)
{
    return SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_WIFI_LIST);
}
