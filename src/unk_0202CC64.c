#include "unk_0202CC64.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/chatot_cry.h"

#include "heap.h"
#include "savedata.h"

int ChatotCry_SaveSize(void)
{
    return sizeof(ChatotCry);
}

void ChatotCry_Init(ChatotCry *cry)
{
    MI_CpuClear32(cry, sizeof(ChatotCry));
    cry->exists = FALSE;
}

ChatotCry *ChatotCry_New(int heapID)
{
    ChatotCry *cry = Heap_Alloc(heapID, sizeof(ChatotCry));

    ChatotCry_Init(cry);
    return cry;
}

ChatotCry *SaveData_GetChatotCry(SaveData *saveData)
{
    return SaveData_SaveTable(saveData, SAVE_TABLE_ENTRY_CHATOT);
}

BOOL IsChatotCryDataValid(const ChatotCry *cry)
{
    return cry->exists;
}

void ResetChatotCryDataStatus(ChatotCry *cry)
{
    cry->exists = FALSE;
}

const void *GetChatotCryAudioBuffer(const ChatotCry *cry)
{
    return cry->data;
}

void ProcessChatotCryAudioData(s8 *param0, const s8 *param1)
{
    int i, v1 = 0;
    s8 v2;
    u8 v3;

    for (i = 0; i < 1000; i++) {
        v3 = param1[i] & 0xf;
        v2 = v3 - 8;

        param0[v1] = v2 * 16;

        v3 = param1[i] >> 4;
        v2 = v3 - 8;

        param0[v1 + 1] = v2 * 16;

        v1 += 2;
    }
}

void StoreProcessedAudioInChatotCryData(ChatotCry *param0, const s8 *param1)
{
    int i, count;
    s8 v2;
    u8 v3;

    param0->exists = TRUE;
    count = 0;

    for (i = 0; i < 1000 * 2; i += 2) {
        v2 = (param1[i] / 16);
        v3 = v2 + 8;

        param0->data[count] = v3;

        v2 = (param1[i + 1] / 16);
        v3 = v2 + 8;

        param0->data[count] |= (v3 << 4);

        count++;
    }
}

void CopyChatotCryData(ChatotCry *param0, const ChatotCry *param1)
{
    MI_CpuCopyFast(param1, param0, sizeof(ChatotCry));
}
