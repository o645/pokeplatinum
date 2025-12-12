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
void ov88_0223EC78(Window *window, Strbuf *strBuffer, int unused, u32 renderDelay, int xOffset, int yOffset);
int UnionTrade_DisplayMessageFromEntry(Window *window, int entryId, int fontId, MessageLoader *mLoader, StringTemplate *sTemplate);
u32 ov88_handleMenu(BgConfig *param0, Menu **param1, int *param2);
void ov88_0223ED80(Window *param0);
ListMenu *ov88_0223ED94(StringList *param0, int param1, Window *param2, BgConfig *param3);

#endif // POKEPLATINUM_OV88_0223E9C4_H
