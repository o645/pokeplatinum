#include "overlay005/ov5_021EA874.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0202B370_decl.h"

#include "field/field_system.h"

#include "bag.h"
#include "bg_window.h"
#include "communication_information.h"
#include "communication_system.h"
#include "field_message.h"
#include "field_system.h"
#include "field_task.h"
#include "game_options.h"
#include "heap.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "sound_playback.h"
#include "strbuf.h"
#include "string_list.h"
#include "string_template.h"
#include "text.h"
#include "trainer_info.h"
#include "unk_0202ACE0.h"
#include "unk_0203061C.h"
#include "unk_0203909C.h"

typedef struct {
    StringList *choices;
    ListMenu *menu;
    Strbuf *buffer;
    Strbuf *unk_0C;
    Window window;
    Window currentWindow;
    FieldSystem *fieldSystem;
    SaveData *saveData;
    StringTemplate *trainerNameTemplate;
    MessageLoader *messageLoader;
    int printerId;
    Menu *yesNoChoice;
    int unk_48;
    int unk_4C[8];
    int unk_6C[8];
    int netId;
    int unk_90;
} UnkStruct_ov5_021EAE78;

static void ov5_021EAE78(UnkStruct_ov5_021EAE78 *param0, int param1);
static void ov5_021EAF1C(UnkStruct_ov5_021EAE78 *param0);
static void ov5_021EAF90(ListMenu *param0, u32 param1, u8 param2);

static BOOL ov5_021EA874(UnkStruct_ov5_021EAE78 *param0) // Init function for this?
{
    int v0, v1 = 0;
    DWCFriendData *friendData = GetFriendDataById(SaveData_GetWiFiList(param0->saveData), 0);
    DWCFriendData *v3;

    if (0 == sub_020391DC(param0->saveData, param0->unk_4C, HEAP_ID_FIELD1)) {
        return 1;
    }

    param0->netId = 0;

    LoadMessageBoxGraphics(param0->fieldSystem->bgConfig, 3, (512 - (18 + 12)), 10, Options_Frame(SaveData_GetOptions(param0->saveData)), HEAP_ID_FIELD1);
    LoadStandardWindowGraphics(param0->fieldSystem->bgConfig, 3, 1024 - (18 + 12) - 9, 11, 0, HEAP_ID_FIELD1);

    param0->unk_48 = 1;
    return 0;
}

static BOOL ov5_021EA8F0(UnkStruct_ov5_021EAE78 *connectedSystem)
{
    int i;
    TrainerInfo *trainerInfo;

    connectedSystem->netId = -1;

    for (i = 0; i < CommSys_ConnectedCount(); i++) {
        if (connectedSystem->unk_4C[i] == 2) {
            connectedSystem->netId = i;
            connectedSystem->unk_4C[i] = 0;
            break;
        }
    }

    if (connectedSystem->netId == -1) { // no connected system
        return 1;
    }

    if (Bag_CanRemoveItem(SaveData_GetBag(connectedSystem->saveData), ITEM_PAL_PAD, 1, HEAP_ID_FIELD1) == TRUE) {
        trainerInfo = CommInfo_TrainerInfo(connectedSystem->netId);
        StringTemplate_SetPlayerName(connectedSystem->trainerNameTemplate, 0, trainerInfo);
        ov5_021EAE78(connectedSystem, 57);
        connectedSystem->unk_48 = 2;
        return 0;
    }

    {
        WiFiList *wifiLIst = SaveData_GetWiFiList(connectedSystem->saveData);

        for (i = 0; i < 32; i++) {
            if (!wifiSlotHasValidFriendData(wifiLIst, i)) {
                AddFriendToPalPad(connectedSystem->saveData, connectedSystem->netId, i, HEAP_ID_FIELD1, 0);
                break;
            }
        }
    }
    connectedSystem->unk_48 = 1;
    return 0;
}

static const WindowTemplate Unk_ov5_021FAF00 = {
    0x3,
    0x19,
    0xD,
    0x6,
    0x4,
    0xD,
    0x21F
};

static BOOL ov5_021EA9BC(UnkStruct_ov5_021EAE78 *param0)
{
    if (Text_IsPrinterActive(param0->printerId) == 0) {
        param0->yesNoChoice = Menu_MakeYesNoChoice(param0->fieldSystem->bgConfig, &Unk_ov5_021FAF00, 1024 - (18 + 12) - 9, 11, 4);
        param0->unk_48 = 3;
    }

    return 0;
}

static BOOL ov5_021EA9F8(UnkStruct_ov5_021EAE78 *param0)
{
    DWCFriendData *v0;
    Strbuf *v1;
    int v2;
    int v3 = Menu_ProcessInputAndHandleExit(param0->yesNoChoice, HEAP_ID_FIELD1);

    if (v3 == 0xffffffff) {
        return 0;
    } else if (v3 == 0) {
        WiFiList *v4 = SaveData_GetWiFiList(param0->saveData);

        for (v2 = 0; v2 < 32; v2++) {
            if (!wifiSlotHasValidFriendData(v4, v2)) {
                AddFriendToPalPad(param0->saveData, param0->netId, v2, HEAP_ID_FIELD1, 0);
                break;
            }
        }

        if (v2 == 32) {
            ov5_021EAE78(param0, 58);
            param0->unk_48 = 4;
            return 0;
        }
    }

    param0->unk_48 = 1;
    return 0;
}

static BOOL ov5_021EAA6C(UnkStruct_ov5_021EAE78 *param0)
{
    if (Text_IsPrinterActive(param0->printerId) == 0) {
        param0->yesNoChoice = Menu_MakeYesNoChoice(param0->fieldSystem->bgConfig, &Unk_ov5_021FAF00, 1024 - (18 + 12) - 9, 11, 4);
        param0->unk_48 = 5;
    }

    return 0;
}

static BOOL ov5_021EAAA8(UnkStruct_ov5_021EAE78 *param0)
{
    TrainerInfo *v0;
    DWCFriendData *v1;
    Strbuf *v2;
    int v3;
    int v4 = Menu_ProcessInputAndHandleExit(param0->yesNoChoice, 4);

    if (v4 == 0xffffffff) {
        return 0;
    } else if (v4 == 0) {
        param0->unk_48 = 8;
    } else {
        v0 = CommInfo_TrainerInfo(param0->netId);
        StringTemplate_SetPlayerName(param0->trainerNameTemplate, 0, v0);
        ov5_021EAE78(param0, 59);
        param0->unk_48 = 6;
    }

    return 0;
}

static BOOL ov5_021EAAEC(UnkStruct_ov5_021EAE78 *param0)
{
    if (Text_IsPrinterActive(param0->printerId) == 0) {
        param0->yesNoChoice = Menu_MakeYesNoChoice(param0->fieldSystem->bgConfig, &Unk_ov5_021FAF00, 1024 - (18 + 12) - 9, 11, 4);
        param0->unk_48 = 7;
    }

    return 0;
}

static BOOL ov5_021EAB28(UnkStruct_ov5_021EAE78 *param0)
{
    TrainerInfo *v0;
    DWCFriendData *v1;
    Strbuf *v2;
    int v3;
    int v4 = Menu_ProcessInputAndHandleExit(param0->yesNoChoice, 4);

    if (v4 == 0xffffffff) {
        return 0;
    } else if (v4 == 0) {
        param0->unk_48 = 12;
    } else {
        ov5_021EAE78(param0, 58);
        param0->unk_48 = 4;
    }

    return 0;
}

static const ListMenuTemplate Unk_ov5_021FAF08 = {
    NULL,
    NULL,
    NULL,
    NULL,
    0x20,
    0x20,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x1,
    0x0,
    0x0,
    NULL
};

static BOOL ov5_021EAB58(UnkStruct_ov5_021EAE78 *param0)
{
    WiFiList *wifiList = SaveData_GetWiFiList(param0->saveData);
    ListMenuTemplate v1;
    int totalValidFriendData = GetTotalValidFriendDataCount(wifiList);
    int v3 = 5;

    param0->choices = StringList_New(totalValidFriendData + 1, HEAP_ID_FIELD1);

    Window_Add(param0->fieldSystem->bgConfig, &param0->currentWindow, 3, 19, 1, 12, v3 * 2, 13, (((1024 - (18 + 12) - 9 - (32 * 8)) - (18 + 12 + 24)) - (27 * 4)) - (10 * (v3 + 2) * 2));
    Window_DrawStandardFrame(&param0->currentWindow, 1, 1024 - (18 + 12) - 9, 11);

    {
        MessageLoader *messageLoader;
        int i = 0;

        for (i = 0; i < 32; i++) {
            if (wifiSlotHasValidFriendData(wifiList, i)) {
                Strbuf_CopyChars(param0->buffer, GetFriendTrainerName(wifiList, i));
                StringList_AddFromStrbuf(param0->choices, param0->buffer, i);
            }
        }

        StringList_AddFromMessageBank(param0->choices, param0->messageLoader, 11, LIST_CANCEL);
    }

    v1 = Unk_ov5_021FAF08;

    v1.count = totalValidFriendData + 1;
    v1.maxDisplay = v3;
    v1.choices = param0->choices;
    v1.window = &param0->currentWindow;
    v1.cursorCallback = ov5_021EAF90;
    v1.parent = param0;

    param0->menu = ListMenu_New(&v1, 0, 0, HEAP_ID_FIELD1);
    Window_CopyToVRAM(&param0->currentWindow);
    param0->unk_48 = 9;

    return 0;
}

static BOOL ov5_021EAC44(UnkStruct_ov5_021EAE78 *param0)
{
    TrainerInfo *trainerInfo;
    int option = ListMenu_ProcessInput(param0->menu);

    switch (option) {
    case LIST_NOTHING_CHOSEN:
        return 0;
    case LIST_CANCEL:
        Sound_PlayEffect(SEQ_SE_CONFIRM);
        trainerInfo = CommInfo_TrainerInfo(param0->netId);
        StringTemplate_SetPlayerName(param0->trainerNameTemplate, 0, trainerInfo);
        ov5_021EAE78(param0, 59);
        param0->unk_48 = 6;
        break;
    default:
        Sound_PlayEffect(SEQ_SE_CONFIRM);
        param0->unk_90 = option;

        WiFiList *wifiList = SaveData_GetWiFiList(param0->saveData);
        TrainerInfo *trainerInfo = TrainerInfo_New(HEAP_ID_FIELD1);

        TrainerInfo_SetName(trainerInfo, GetFriendTrainerName(wifiList, option));
        StringTemplate_SetPlayerName(param0->trainerNameTemplate, 0, trainerInfo);
        Heap_Free(trainerInfo);

        ov5_021EAE78(param0, 60);
        param0->unk_48 = 10;
        break;
    }

    Window_EraseStandardFrame(&param0->currentWindow, 0);
    Window_Remove(&param0->currentWindow);
    ListMenu_Free(param0->menu, NULL, NULL);
    StringList_Free(param0->choices);

    return 0;
}

static BOOL ov5_021EACFC(UnkStruct_ov5_021EAE78 *param0)
{
    if (Text_IsPrinterActive(param0->printerId) == 0) {
        param0->yesNoChoice = Menu_MakeYesNoChoice(param0->fieldSystem->bgConfig, &Unk_ov5_021FAF00, 1024 - (18 + 12) - 9, 11, 4);
        param0->unk_48 = 11;
    }

    return 0;
}

static BOOL ov5_021EAD38(UnkStruct_ov5_021EAE78 *param0)
{
    WiFiList *v0 = SaveData_GetWiFiList(param0->saveData);
    TrainerInfo *trainerInfo;
    DWCFriendData *v2;
    Strbuf *v3;
    int optionChosen = Menu_ProcessInputAndHandleExit(param0->yesNoChoice, HEAP_ID_FIELD1);

    if (optionChosen == LIST_NOTHING_CHOSEN) {
        return 0;
    } else if (optionChosen == 0) {
        sub_02030788(SaveData_GetBattleFrontier(param0->saveData), param0->unk_90);
        sub_0202AFD4(v0, param0->unk_90);
        AddFriendToPalPad(param0->saveData, param0->netId, 32 - 1, HEAP_ID_FIELD1, 0);
        param0->unk_48 = 1;
    } else {
        trainerInfo = CommInfo_TrainerInfo(param0->netId);
        StringTemplate_SetPlayerName(param0->trainerNameTemplate, 0, trainerInfo);
        ov5_021EAE78(param0, 59);
        param0->unk_48 = 6;
    }

    return 0;
}

static BOOL ov5_021EADB4(FieldTask *param0)
{
    UnkStruct_ov5_021EAE78 *v0 = FieldTask_GetEnv(param0);
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);

    switch (v0->unk_48) {
    case 0:
        if (ov5_021EA874(v0)) {
            v0->unk_48 = 12;
        }
        break;
    case 1:
        if (ov5_021EA8F0(v0)) {
            v0->unk_48 = 12;
        }
        break;
    case 2:
        ov5_021EA9BC(v0);
        break;
    case 3:
        ov5_021EA9F8(v0);
        break;
    case 4:
        ov5_021EAA6C(v0);
        break;
    case 5:
        ov5_021EAAA8(v0);
        break;
    case 6:
        ov5_021EAAEC(v0);
        break;
    case 7:
        ov5_021EAB28(v0);
        break;
    case 8:
        ov5_021EAB58(v0);
        break;
    case 9:
        ov5_021EAC44(v0);
        break;
    case 10:
        ov5_021EACFC(v0);
        break;
    case 11:
        ov5_021EAD38(v0);
        break;
    case 12:
        ov5_021EAF1C(v0);
        Heap_Free(v0);
        FieldSystem_ResumeProcessing();
        return 1;
    }

    return 0;
}

static void ov5_021EAE78(UnkStruct_ov5_021EAE78 *system, int entryId)
{
    if (Window_IsInUse(&system->window)) {
        Window_Remove(&system->window);
    }

    MessageLoader_GetStrbuf(system->messageLoader, entryId, system->buffer);
    StringTemplate_Format(system->trainerNameTemplate, system->unk_0C, system->buffer);
    FieldMessage_AddWindow(system->fieldSystem->bgConfig, &system->window, 3);
    FieldMessage_DrawWindow(&system->window, SaveData_GetOptions(system->fieldSystem->saveData));

    system->printerId = FieldMessage_Print(&system->window, system->unk_0C, SaveData_GetOptions(system->fieldSystem->saveData), 1);
}

static void ov5_021EAEE0(UnkStruct_ov5_021EAE78 *param0)
{
    MI_CpuClear8(param0, sizeof(UnkStruct_ov5_021EAE78));

    param0->trainerNameTemplate = StringTemplate_Default(HEAP_ID_FIELD1);
    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0675, HEAP_ID_FIELD1);
    param0->unk_0C = Strbuf_Init(110, HEAP_ID_FIELD1);
    param0->buffer = Strbuf_Init(110, HEAP_ID_FIELD1);
}

static void ov5_021EAF1C(UnkStruct_ov5_021EAE78 *param0)
{
    MessageLoader_Free(param0->messageLoader);
    StringTemplate_Free(param0->trainerNameTemplate);
    Strbuf_Free(param0->unk_0C);
    Strbuf_Free(param0->buffer);

    if (Window_IsInUse(&param0->window)) {
        Window_Remove(&param0->window);
    }
}

void ov5_021EAF50(FieldSystem *fieldSystem)
{
    UnkStruct_ov5_021EAE78 *v0;
    FieldTask *v1 = fieldSystem->task;

    v0 = Heap_AllocAtEnd(HEAP_ID_FIELD2, sizeof(UnkStruct_ov5_021EAE78));
    ov5_021EAEE0(v0);

    v0->fieldSystem = fieldSystem;
    v0->saveData = fieldSystem->saveData;
    v0->unk_48 = 0;

    if (v1 == NULL) {
        FieldSystem_CreateTask(fieldSystem, ov5_021EADB4, v0);
    } else {
        FieldTask_InitCall(v1, ov5_021EADB4, v0);
    }
}

static void ov5_021EAF90(ListMenu *listMenuUnused, u32 param1Unused, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }
}
