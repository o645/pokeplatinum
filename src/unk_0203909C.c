#include "unk_0203909C.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0202B370_decl.h"

#include "communication_information.h"
#include "communication_system.h"
#include "savedata.h"
#include "strbuf.h"
#include "trainer_info.h"
#include "unk_0202ACE0.h"
#include "unk_020366A0.h"

int sub_0203909C(SaveData *saveData, DWCFriendData *friendData, int *result)
{
    int i;
    DWCUserData *userData = WiFiList_GetUserData(SaveData_GetWiFiList(saveData));
    DWCFriendData *newFriendData = GetFriendDataById(SaveData_GetWiFiList(saveData), 0);

    *result = -1;

    if (!DWC_IsValidFriendData(friendData)) {
        return 3;
    }

    for (i = 0; i < 32; i++) {
        if (DWC_IsEqualFriendData(friendData, newFriendData + i)) {
            *result = i;
            return 0;
        } else if ((DWC_GetGsProfileId(userData, friendData) > 0) && (DWC_GetGsProfileId(userData, friendData) == DWC_GetGsProfileId(userData, newFriendData + i))) {
            *result = i;
            return 1;
        } else if ((*result < 0) && !DWC_IsValidFriendData(newFriendData + i)) {
            *result = i;
        }
    }

    return 2;
}

int sub_02039140(SaveData *saveData, u64 friendKey, int *param2)
{
    int v0;
    DWCUserData *userData = WiFiList_GetUserData(SaveData_GetWiFiList(saveData));
    DWCFriendData *friendData = GetFriendDataById(SaveData_GetWiFiList(saveData), 0);
    DWCFriendData newFriendData;

    if (!DWC_CheckFriendKey(userData, friendKey)) {
        return 3;
    }

    DWC_CreateFriendKeyToken(&newFriendData, friendKey);

    if (DWC_GetGsProfileId(userData, &newFriendData) <= 0) {
        return 3;
    }

    *param2 = -1;

    for (v0 = 0; v0 < 32; v0++) {
        if (DWC_GetGsProfileId(userData, &newFriendData) == DWC_GetGsProfileId(userData, friendData + v0)) {
            *param2 = v0;
            return 0;
        } else if ((*param2 < 0) && !DWC_IsValidFriendData(friendData + v0)) {
            *param2 = v0;
        }
    }

    return 2;
}

BOOL sub_020391DC(SaveData *saveData, int *param1, int heapID)
{
    int v0, v1 = 0, v2;
    DWCFriendData *v3 = GetFriendDataById(SaveData_GetWiFiList(saveData), 0);
    DWCFriendData *v4;

    for (v0 = 0; v0 < CommSys_ConnectedCount(); v0++) {
        if (CommSys_CurNetId() == v0) {
            continue;
        }

        v4 = CommInfo_DWCFriendData(v0);

        if (v4 == NULL) {
            continue;
        }

        param1[v0] = sub_0203909C(saveData, v4, &v2);

        GF_ASSERT(param1[v0] != 3);

        if (param1[v0] == 0) {
            AddFriendToPalPad(saveData, v0, v2, heapID, 2);
            CommInfo_SavePlayerRecord(saveData);
        } else if (param1[v0] == 1) {
            if (!CommMan_IsConnectedToWifi()) {
                AddFriendToPalPad(saveData, v0, v2, heapID, 1);
                MI_CpuCopy8(v4, &v3[v2], sizeof(DWCFriendData));

                CommInfo_SavePlayerRecord(saveData);
            }
        } else if (param1[v0] == 2) {
            v1 = 1;
        }
    }

    return v1;
}

void AddFriendToPalPad(SaveData *saveData, int netId, int slot, int heapID, int param4)
{
    WiFiList *wifiList = SaveData_GetWiFiList(saveData);
    DWCFriendData *friendData = GetFriendDataById(wifiList, slot);
    TrainerInfo *friendInfo = CommInfo_TrainerInfo(netId);
    DWCFriendData *v3;
    Strbuf *v4;

    if (param4 != 2) {
        v3 = CommInfo_DWCFriendData(netId);
        MI_CpuCopy8(v3, friendData, sizeof(DWCFriendData));
    }

    if (param4 == 0) {
        v4 = TrainerInfo_NameNewStrbuf(friendInfo, heapID);
        SetFriendTrainerName(wifiList, slot, v4);
        Strbuf_Free(v4);
        sub_0202AE2C(wifiList, slot, 8, TrainerInfo_Gender(friendInfo));
        sub_0202AE2C(wifiList, slot, 0, TrainerInfo_ID(friendInfo));
    } else if (param4 == 1) {
        if (sub_0202AD2C(wifiList, slot, 8) == 2) {
            sub_0202AE2C(wifiList, slot, 8, TrainerInfo_Gender(friendInfo));
            sub_0202AE2C(wifiList, slot, 0, TrainerInfo_ID(friendInfo));
        }
    }

    v4 = Strbuf_Init(120, heapID);

    Strbuf_CopyChars(v4, sub_02032F54(netId));
    sub_0202AF50(wifiList, slot, v4);
    Strbuf_Free(v4);
    sub_0202AE2C(wifiList, slot, 7, TrainerInfo_Appearance(friendInfo));
    CommInfo_SavePlayerRecord(saveData);
}

int sub_02039390(SaveData *saveData, int param1)
{
    int v0, v1;
    DWCFriendData *v2 = CommInfo_DWCFriendData(param1);
    WiFiList *v3 = SaveData_GetWiFiList(saveData);

    for (v0 = 0; v0 < 32; v0++) {
        if (DWC_IsEqualFriendData(v2, GetFriendDataById(v3, v0))) {
            return v0;
        }
    }

    return 32;
}
