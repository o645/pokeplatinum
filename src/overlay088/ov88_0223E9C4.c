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

static void ov88_0223EE14(ListMenu *unusedMenu, u32 unused, u8 param2);

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
    int i;

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

    for (i = 0; i < 14; i++) {
        Window_Add(bgConfig, &window[7 + i], 1, Unk_ov88_0223F170[i][0], Unk_ov88_0223F170[i][1], 8, 2, 8, (((1 + (10 * 2)) + (10 * 2)) + (5 * 2)) + i * (8 * 2));
        Window_FillTilemap(&window[7 + i], 0);
    }

    for (i = 0; i < 8; i++) {
        Window_Add(bgConfig, &window[26 + i], 4, Unk_ov88_0223F1A8[i][0], Unk_ov88_0223F1A8[i][1], Unk_ov88_0223F1A8[i][2], Unk_ov88_0223F1A8[i][3], 8, Unk_ov88_0223F1A8[i][4]);
        Window_FillTilemap(&window[26 + i], 0);
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

void Trade_DisplayMessageFromStringBuffer(Window *window, Strbuf *stringBuffer, int unused, u32 renderDelay, int xOffset, int yOffset)
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

int Trade_DisplayMessageFromEntry(Window *window, int entryId, int fontId, MessageLoader *messageLoader, StringTemplate *stringTemplate)
{
    Strbuf *text;
    int Message;

    text = MessageUtil_ExpandedStrbuf(stringTemplate, messageLoader, entryId, HEAP_ID_26);

    if (fontId == 1) {
        Window_DrawMessageBoxWithScrollCursor(window, 0, (512 - (9 + (18 + 12))), 10);
    } else {
        Window_DrawStandardFrame(window, 0, (512 - 9), 11);
    }

    Window_FillTilemap(window, 15);
    Message = Text_AddPrinterWithParamsAndColor(window, fontId, text, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Strbuf_Free(text);

    return Message;
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

u32 Trade_handleMenu(BgConfig *bgConfig, Menu **menu, int *param2)
{
    u32 result = 0xffffffff;

    switch (*param2) {
    case 0:
        *menu = Menu_MakeYesNoChoice(bgConfig, &Unk_ov88_YesNoWindowTemplate, (512 - 9), 11, 26);
        (*param2)++;
        break;
    case 1:
        result = Menu_ProcessInputAndHandleExit(*menu, 26);

        if (result != MENU_NOTHING_CHOSEN) {
            (*param2) = 0;
        }
    }

    return result;
}

void Trade_DrawWindowFrame(Window *window)
{
    Window_DrawStandardFrame(window, 0, (512 - 9), 11);
}

static const ListMenuTemplate Trade_FriendRosterMenuTemplate = {
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

ListMenu *Trade_SetupFriendRosterMenu(StringList *choices, int count, Window *window, BgConfig *menuBG)
{
    ListMenu *menu;
    ListMenuTemplate mTemplate;
    int maxDisplay = 5;

    Window_Add(menuBG, window, 0, 19, 1, 12, maxDisplay * 2, 13, (512 - (9 + (18 + 12))) - (10 * (maxDisplay + 2) * 2));
    Window_DrawStandardFrame(window, 0, (512 - 9), 11);

    mTemplate = Trade_FriendRosterMenuTemplate;
    mTemplate.count = count + 1;
    mTemplate.maxDisplay = maxDisplay;
    mTemplate.choices = choices;
    mTemplate.window = window;
    mTemplate.cursorCallback = ov88_0223EE14;
    menu = ListMenu_New(&mTemplate, 0, 0, HEAP_ID_26);

    return menu;
}

static void ov88_0223EE14(ListMenu *unusedMenu, u32 unused, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SEQ_SE_CONFIRM);
    }
}
