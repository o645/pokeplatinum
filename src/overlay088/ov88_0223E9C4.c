#include "overlay088/ov88_0223E9C4.h"

#include <nitro.h>
#include <string.h>

#include "bg_window.h"
#include "font.h"
#include "game_options.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "message_util.h"
#include "render_window.h"
#include "sound_playback.h"
#include "strbuf.h"
#include "string_list.h"
#include "text.h"

static void ov88_0223EE14(ListMenu *param0, u32 param1, u8 param2);

static const u16 Unk_ov88_0223F1A8[][5] = {
    { 0x4, 0x1, 0x9, 0x2, 0x1 },
    { 0x14, 0x1, 0x9, 0x2, 0x13 },
    { 0x4, 0x3, 0x8, 0x2, 0x25 },
    { 0x14, 0x3, 0x8, 0x2, 0x35 },
    { 0x2, 0x13, 0x7, 0x2, 0x45 },
    { 0x12, 0x13, 0x7, 0x2, 0x53 },
    { 0x2, 0x15, 0xC, 0x2, 0x61 },
    { 0x12, 0x15, 0xC, 0x2, 0x79 }
};

static const u16 Unk_ov88_0223F170[][2] = {
    { 0x0, 0x7 },
    { 0x8, 0x7 },
    { 0x0, 0xC },
    { 0x8, 0xC },
    { 0x0, 0x11 },
    { 0x8, 0x11 },
    { 0x10, 0x7 },
    { 0x18, 0x7 },
    { 0x10, 0xC },
    { 0x18, 0xC },
    { 0x10, 0x11 },
    { 0x18, 0x11 },
    { 0x4, 0xA },
    { 0x14, 0xA }
};

void ov88_0223E9C4(BgConfig *bgConfig, Window *window, Options *options)
{
    int v0;

    Window_Add(bgConfig, &window[0], 1, 2, 1, 10, 2, 8, 1);
    Window_FillTilemap(&window[0], 0);

    Window_Add(bgConfig, &window[1], 1, 20, 1, 10, 2, 8, (1 + (10 * 2)));
    Window_FillTilemap(&window[1], 0);

    Window_Add(bgConfig, &window[6], 1, 26, 21, 5, 2, 8, ((1 + (10 * 2)) + (10 * 2)));
    Window_FillTilemap(&window[6], 0);

    LoadMessageBoxGraphics(bgConfig, BG_LAYER_MAIN_0, (512 - (9 + (18 + 12))), 10, Options_Frame(options), HEAP_ID_26);
    LoadStandardWindowGraphics(bgConfig, BG_LAYER_MAIN_0, (512 - 9), 11, 0, HEAP_ID_26);

    Window_Add(bgConfig, &window[21], 0, 2, 21, 20, 2, 13, 1);
    Window_FillTilemap(&window[21], 0);
    Window_Add(bgConfig, &window[22], 0, 2, 19, 14, 4, 13, (20 * 2));
    Window_FillTilemap(&window[22], 0);
    Window_Add(bgConfig, &window[23], 0, 2, 19, 27, 4, 13, (14 * 4));
    Window_FillTilemap(&window[23], 0);

    Window_Add(bgConfig, &window[24], 0, 20, 17, 11, 6, 13, ((14 * 4) + (27 * 4)));
    Window_FillTilemap(&window[24], 0);
    Window_Add(bgConfig, &window[25], 0, 20, 19, 11, 4, 13, (((14 * 4) + (27 * 4)) + (11 * 6)));
    Window_FillTilemap(&window[25], 0);

    for (v0 = 0; v0 < 14; v0++) {
        Window_Add(bgConfig, &window[7 + v0], 1, Unk_ov88_0223F170[v0][0], Unk_ov88_0223F170[v0][1], 8, 2, 8, (((1 + (10 * 2)) + (10 * 2)) + (5 * 2)) + v0 * (8 * 2));
        Window_FillTilemap(&window[7 + v0], 0);
    }

    for (v0 = 0; v0 < 8; v0++) {
        Window_Add(bgConfig, &window[26 + v0], 4, Unk_ov88_0223F1A8[v0][0], Unk_ov88_0223F1A8[v0][1], Unk_ov88_0223F1A8[v0][2], Unk_ov88_0223F1A8[v0][3], 8, Unk_ov88_0223F1A8[v0][4]);
        Window_FillTilemap(&window[26 + v0], 0);
    }
}

void ov88_RemoveWindows(Window *windowArray)
{
    int i;

    for (i = 0; i < 14; i++) {
        Window_Remove(&windowArray[7 + i]);
    }

    for (i = 0; i < 8; i++) {
        Window_Remove(&windowArray[26 + i]);
    }

    Window_Remove(&windowArray[0]);
    Window_Remove(&windowArray[1]);
    Window_Remove(&windowArray[6]);

    Window_Remove(&windowArray[21]);
    Window_Remove(&windowArray[22]);
    Window_Remove(&windowArray[23]);
    Window_Remove(&windowArray[24]);
    Window_Remove(&windowArray[25]);
}

void ov88_0223EC78(Window *window, Strbuf *stringBuffer, int unused, u32 renderDelay, int xOffset, int yOffset)
{
    int finalXOffset = 0;

    if (xOffset == 1) {
        int strBufWidth;

        strBufWidth = Font_CalcStrbufWidth(FONT_SYSTEM, stringBuffer, 0);
        finalXOffset = ((window->width * 8) - strBufWidth) / 2;
    } else {
        finalXOffset = xOffset;
    }

    Text_AddPrinterWithParamsAndColor(window, FONT_SYSTEM, stringBuffer, finalXOffset, yOffset, renderDelay, TEXT_COLOR(11, 12, 0), NULL);
}

int UnionTrade_DisplayMessageFromEntry(Window *window, int entryId, int fontId, MessageLoader *messageLoader, StringTemplate *stringTemplate)
{
    Strbuf *v0;
    int v1;

    v0 = MessageUtil_ExpandedStrbuf(stringTemplate, messageLoader, entryId, HEAP_ID_26);

    if (fontId == 1) {
        Window_DrawMessageBoxWithScrollCursor(window, 0, (512 - (9 + (18 + 12))), 10);
    } else {
        Window_DrawStandardFrame(window, 0, (512 - 9), 11);
    }

    Window_FillTilemap(window, 15);
    v1 = Text_AddPrinterWithParamsAndColor(window, fontId, v0, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Strbuf_Free(v0);

    return v1;
}

static const WindowTemplate Unk_ov88_YesNoWindowTemplate = {
    0x0,
    0x19,
    0xD,
    0x6,
    0x4,
    0x3,
    0x112
};

u32 ov88_handleMenu(BgConfig *bgConfig, Menu **menu, int *param2)
{
    u32 result = 0xffffffff;

    switch (*param2) {
    case 0:
        *menu = Menu_MakeYesNoChoice(bgConfig, &Unk_ov88_YesNoWindowTemplate, (512 - 9), 11, 26);
        (*param2)++;
        break;
    case 1:
        result = Menu_ProcessInputAndHandleExit(*menu, 26);

        if (result != 0xffffffff) {
            (*param2) = 0;
        }
    }

    return result;
}

void ov88_0223ED80(Window *param0)
{
    Window_DrawStandardFrame(param0, 0, (512 - 9), 11);
}

static const ListMenuTemplate Unk_ov88_0223F150 = {
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

ListMenu *ov88_0223ED94(StringList *param0, int param1, Window *param2, BgConfig *param3)
{
    ListMenu *listMenu;
    ListMenuTemplate listMenuTemplate;
    int v2 = 5;

    Window_Add(param3, param2, 0, 19, 1, 12, v2 * 2, 13, (512 - (9 + (18 + 12))) - (10 * (v2 + 2) * 2));
    Window_DrawStandardFrame(param2, 0, (512 - 9), 11);

    listMenuTemplate = Unk_ov88_0223F150;
    listMenuTemplate.count = param1 + 1;
    listMenuTemplate.maxDisplay = v2;
    listMenuTemplate.choices = param0;
    listMenuTemplate.window = param2;
    listMenuTemplate.cursorCallback = ov88_0223EE14;
    listMenu = ListMenu_New(&listMenuTemplate, 0, 0, HEAP_ID_26);

    return listMenu;
}

static void ov88_0223EE14(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }
}
