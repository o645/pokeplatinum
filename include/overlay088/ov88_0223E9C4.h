#ifndef POKEPLATINUM_OV88_0223E9C4_H
#define POKEPLATINUM_OV88_0223E9C4_H

#include "bg_window.h"
#include "game_options.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "strbuf.h"
#include "string_list.h"
#include "string_template.h"

void ov88_0223E9C4(BgConfig *bgConfig, Window *window, Options *options);
void ov88_RemoveWindows(Window *window);
void Trade_DisplayMessageFromStringBuffer(Window *window, Strbuf *strBuffer, int unused, u32 renderDelay, int xOffset, int yOffset);
int Trade_DisplayMessageFromEntry(Window *window, int entryId, int fontId, MessageLoader *mLoader, StringTemplate *sTemplate);
u32 Trade_HandleMenu(BgConfig *menuBG, Menu **menu, int *param2);
void Trade_DrawWindowFrame(Window *window);
ListMenu *Trade_SetupFriendRosterMenu(StringList *choices, int count, Window *window, BgConfig *menuBG);

#endif // POKEPLATINUM_OV88_0223E9C4_H
