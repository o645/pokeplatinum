#include "overlay088/ov88_0223B140.h"

#include <nitro.h>
#include <string.h>

#include "generated/game_records.h"
#include "generated/species.h"

#include "struct_decls/struct_0202B370_decl.h"
#include "struct_decls/struct_02095E80_decl.h"
#include "struct_defs/chatot_cry.h"
#include "struct_defs/struct_02095E80_t.h"
#include "struct_defs/struct_02099F80.h"

#include "applications/pokemon_summary_screen/main.h"
#include "overlay088/ov88_0223E9C4.h"
#include "overlay088/struct_ov88_0223C370.h"
#include "overlay088/struct_ov88_0223C8AC.h"

#include "bag.h"
#include "bg_window.h"
#include "brightness_controller.h"
#include "char_transfer.h"
#include "character_sprite.h"
#include "charcode_util.h"
#include "communication_information.h"
#include "communication_system.h"
#include "font.h"
#include "game_options.h"
#include "game_records.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "inlines.h"
#include "item.h"
#include "journal.h"
#include "list_menu.h"
#include "math_util.h"
#include "menu.h"
#include "message.h"
#include "message_util.h"
#include "narc.h"
#include "overlay_manager.h"
#include "pal_pad.h"
#include "party.h"
#include "pltt_transfer.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "render_oam.h"
#include "render_window.h"
#include "rtc.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_chatot.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "strbuf.h"
#include "string_list.h"
#include "string_template.h"
#include "system.h"
#include "system_vars.h"
#include "text.h"
#include "touch_screen.h"
#include "trainer_info.h"
#include "unk_0202ACE0.h" //wifi friend data
#include "unk_0202CC64.h" //chatot cry data
#include "unk_0202D778.h" //ribbon data
#include "unk_0202F180.h" //catch records
#include "unk_0203061C.h" //battle frontier data
#include "unk_020363E8.h" //communication commands
#include "unk_020366A0.h" //commmunication manager
#include "unk_02038ED4.h" //save data state communication?
#include "unk_02038F8C.h"
#include "unk_0203909C.h"
#include "unk_020393C8.h"
#include "unk_02092494.h"
#include "unk_02095CD4.h"
#include "vars_flags.h"
#include "vram_transfer.h"

#include "constdata/const_020F410C.h"

static void Trade_LoadPokemonSprite(NNSG2dCharacterData *characterData, int species, int form, int isEgg, int spriteSlot, Sprite *sprite);
static void ov88_0223B320(Trade *unionTrade);
static void ov88_0223C0E0(void *param0);
static void Trade_SetSubScreenBanks(void);
static void Trade_BGInit(BgConfig *param0);
static void ov88_InitTransfer(void);
static void ov88_0223C370(Trade *unionTrade, ApplicationManager *appMan);
static void ov88_FreeBgTileMapBuffers(BgConfig *param0);
static void ov88_0223C4E0(BgConfig *param0, int param1, int param2);
static void ov88_0223C504(Trade *trade, NARC *narc);
static void ov88_0223C66C(Trade *trade, NARC *narc);
static void ov88_0223CBA0(Trade *trade);
static void ov88_0223CE34(u32 *param0);
static void Trade_AnimateSelectedPokemonOnTouch(Trade *unionTrade);
static void ov88_0223CEF0(u16 *angle);
static int ov88_0223CF30(int slot, int param1, Trade_PokemonData *tradePokemonData);
static void Trade_AnimatePartyPokemon(int slot, Sprite *sprite, int spriteId);
static int ov88_0223CFF4(u32 *param0, int *param1, Sprite *monSprite, Trade_PokemonData *tradePokemonData, int spriteId);
static int ov88_0223C800(int spriteTemplateLoadCount, Pokemon *pokemon, u8 *startAddress, PokemonSpriteTemplate *monSpriteTemplate);
static void Trade_WriteTradeJournalEntry(JournalEntry *journalEntry, Pokemon *mon);
static void ov88_sendChatotCry(ChatotCry *cry);
static void Trade_AddWaitDial(Trade *trade);
static void Trade_RemoveWaitDial(Trade *trade);
static int Trade_PlayerHasNonEggMonsRemaining(Trade *trade);
static int Trade_CheckForInvalidMons(Trade *trade);
static void ov88_0223E984(Trade *unionTrade);
static void ov88_0223E998(Trade *unionTrade);
static void ov88_0223B710(StringTemplate *nickTemplate, Party *party, int slot);
static void ov88_0223B748(Window *window, StringTemplate *stringTemplate, MessageLoader *messageLoader, Party *party, int firstEntryId);
static void ov88_0223C8D8(Window *window, int param1, Party *param2, int param3, Trade *param4);
static void Trade_TradePokemon(Party *playerParty, Party *friendParty, int playerSelectedSlot, int friendSelectedSlot, UnkStruct_ov88_playerData *playerData);
static void UnionTrade_ClearSprites(Trade *unionTrade);
static void ov88_0223B4F0(Trade *unionTrade);
static void ov88_0223BFD8(Trade *unionTrade);
static void ov88_0223BE28(Trade *unionTrade);
static void ov88_0223CB34(Window *param0, int param1, Trade *unionTrade);
static void UnionTrade_getTradePokemonFromMon(Pokemon *mon, Trade_PokemonData *tradeMon);
static void Trade_SetSpritePosition(Sprite *sprite, int xMult, int yMult);
static int UnionTrade_GetDisplayGender(Trade_PokemonData *tradeMon, Party *party, int slot, int gender);
static void UnionTrade_SendRibbonData(SaveData *saveData);
static int ov88_0223B914(Trade *unionTrade);
static int ov88_0223BED8(Trade *unionTrade);
static void UnionTrade_drawPartySprites(Party *party, int offset, Trade *unionTrade);
static int ov88_0223D150(Trade *unionTrade);
static int ov88_0223DA00(Trade *unionTrade);
static int UnionTrade_SelectPlayerMon(Trade *unionTrade);
static int Trade_SelectFriendsPokemon(Trade *unionTrade);
static int ov88_0223D318(Trade *unionTrade);
static int ov88_0223D2C4(Trade *unionTrade);
static int ov88_0223DB48(Trade *unionTrade);
static int Trade_SelectMonForTrade(Trade *unionTrade);
static int ov88_0223DCE0(Trade *unionTrade);
static int Trade_HandleSelectingFriendsMon(Trade *unionTrade);
static int ov88_0223D434(Trade *unionTrade);
static int ov88_0223D3E0(Trade *unionTrade);
static int ov88_ConfirmTradeMessage(Trade *unionTrade);
static int ov88_0223E20C(Trade *unionTrade);
static int ov88_0223E41C(Trade *unionTrade);
static int ov88_0223E478(Trade *unionTrade);
static int ov88_0223DD1C(Trade *unionTrade);
static int ov88_0223DF00(Trade *unionTrade);
static int ov88_HandleBallCapsuleRemovalMenu(Trade *unionTrade);
static int ov88_WarnAboutBallCapsuleRemoval(Trade *unionTrade);
static void ov88_0223DFF4(Trade *unionTrade);
static void ov88_0223E1AC(Trade *unionTrade);
static void Trade_DisplayTradeMessage(Trade *unionTrade, int param1, int param2);
static void ov88_0223DE68(VecFx32 param0[], int param1, int param2, int param3, int param4);
static void ov88_0223DE7C(Sprite *pokemonSprite, Sprite *mailSprite, Sprite *capsuleSprite, int param3, VecFx32 offsets[], Trade_PokemonData *tradePokemonData);
static void ov88_0223BDA4(Trade *trade, int slot);
static void ov88_0223E848(Trade *unionTrade);
static void ov88_0223C860(Window *window, Party *party, int param2, int param3, int param4);
static int Trade_AskToDeleteFriendFromFullRoster(Trade *unionTrade);
static int ov88_AskToRegisterFriendInPalPad(Trade *unionTrade);
static int ov88_0223D854(Trade *unionTrade);
static int Trade_ShowFriendRosterMenuForReplacement(Trade *unionTrade);
static void Trade_InitPokemonSummary(Trade *unionTrade, int param1);
static void Trade_CreateNetworkObject(TrainerInfo *trainerInfo, PalPad *palPad1, PalPad *palPad2);

static const int UnionTrade_SpritePositions[][2] = {
    { 0x0, 0x20 },
    { 0x40, 0x20 },
    { 0x0, 0x48 },
    { 0x40, 0x48 },
    { 0x0, 0x70 },
    { 0x40, 0x70 },
    { 0x80, 0x20 },
    { 0xC0, 0x20 },
    { 0x80, 0x48 },
    { 0xC0, 0x48 },
    { 0x80, 0x70 },
    { 0xC0, 0x70 },
    { 0xC0, 0xA0 }
};

static const int Unk_ov88_0223EF54[][3] = {
    { 0x3F, 0x58, 0x0 },
    { 0xC0, 0x58, 0x1 },
    { 0x10, 0x8, 0x6 },
    { 0x90, 0x8, 0x6 },
    { 0x63, 0x8, 0x16 },
    { 0xE3, 0x8, 0x16 }
};

static const u8 Unk_ov88_0223F004[][4][6] = {
    {
        { 0x4, 0x2, 0xC, 0xC },
        { 0x2, 0x4, 0xC, 0xC },
        { 0x7, 0x6, 0x1, 0x0 },
        { 0x1, 0x6, 0x7, 0x0 },
    },
    {
        { 0x5, 0x3, 0xC, 0xC },
        { 0x3, 0x5, 0xC, 0xC },
        { 0x0, 0x7, 0x6, 0x1 },
        { 0x6, 0x7, 0x0, 0x1 },
    },
    {
        { 0x0, 0x0, 0x0, 0x0 },
        { 0x4, 0x0, 0x0, 0x0 },
        { 0x9, 0x8, 0x7, 0x6 },
        { 0x3, 0x1 },
    },
    {
        { 0x1, 0x1, 0x1, 0x1 },
        { 0x5, 0x1, 0x1, 0x1 },
        { 0x2, 0x9, 0x8, 0x7 },
        { 0x8, 0x9, 0x6, 0x6 },
    },
    {
        { 0x2, 0x2, 0x2, 0x2 },
        { 0x0, 0x0, 0x0, 0x0 },
        { 0xB, 0xA, 0x9, 0x8, 0x7, 0x6 },
        { 0x5, 0x3, 0x1 },
    },
    {
        { 0x3, 0x3, 0x3, 0x3 },
        { 0x1, 0x1, 0x1, 0x1 },
        { 0x4, 0x4, 0x4, 0x4 },
        { 0xA, 0x8, 0x6 },
    },
    {
        { 0xA, 0x8, 0xC },
        { 0x8, 0xA, 0xC },
        { 0x1, 0x0 },
        { 0x7, 0x0, 0x1 },
    },
    {
        { 0xC },
        { 0x9, 0xC },
        { 0x6 },
        { 0x0 },
    },
    {
        { 0x6 },
        { 0xA, 0x6 },
        { 0x3, 0x2, 0x1, 0x0 },
        { 0x9, 0x7 },
    },
    {
        { 0x7 },
        { 0xB, 0xC },
        { 0x8 },
        { 0x2, 0x0, 0x1 },
    },
    {
        { 0x8 },
        { 0x6 },
        { 0x5, 0x4, 0x3, 0x2, 0x1, 0x0 },
        { 0xB, 0x9, 0x7 },
    },
    {
        { 0x9 },
        { 0xC },
        { 0xA },
        { 0x4, 0x2, 0x0 },
    },
    {
        { 0xB, 0x9, 0x7, 0x6 },
        { 0x7, 0x6 },
        { 0xC },
        { 0xC },
    },
};

int ov88_0223B140(ApplicationManager *appMan, int *param1)
{
    Trade *unionTrade;
    NARC *NARC_TradeList;

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_26, 0x50000 + 0x20000 + 2000);

    NARC_TradeList = NARC_ctor(NARC_INDEX_DATA__TRADELIST, HEAP_ID_26);
    unionTrade = ApplicationManager_NewData(appMan, sizeof(Trade), HEAP_ID_26);

    MI_CpuClearFast(unionTrade, sizeof(Trade));

    unionTrade->bgConfig = BgConfig_New(HEAP_ID_26);
    unionTrade->tradeStrTemplate = StringTemplate_New(12, (10 + 1) * 2, HEAP_ID_26);
    unionTrade->nicknameTemplate = StringTemplate_Default(HEAP_ID_26);
    unionTrade->stringTemplate2 = StringTemplate_Default(HEAP_ID_26);
    unionTrade->tradeMessages = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0354, HEAP_ID_26);
    unionTrade->appMan = NULL;

    ov88_0223C370(unionTrade, appMan);
    SetAutorepeat(4, 8);
    Trade_SetSubScreenBanks();
    Trade_BGInit(unionTrade->bgConfig);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 16, 1, HEAP_ID_26);
    ov88_0223C504(unionTrade, NARC_TradeList);
    SetVBlankCallback(ov88_0223C0E0, unionTrade);
    ov88_InitTransfer();
    ov88_0223C66C(unionTrade, NARC_TradeList);
    ov88_0223CBA0(unionTrade);
    ov88_0223E9C4(unionTrade->bgConfig, unionTrade->windows, unionTrade->playerData->options);

    unionTrade->fieldSystem = unionTrade->playerData->fieldSystem;

    sub_02095E60(unionTrade->fieldSystem, unionTrade);
    Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_COMMUNICATING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
    sub_02095CD4(unionTrade->fieldSystem);
    Bg_ToggleLayer(BG_LAYER_MAIN_0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    sub_02038A1C(26, unionTrade->bgConfig);
    sub_02039734();

    if (IsNight() == FALSE) {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_FIELD, SEQ_PC_01, 1);
        Sound_AdjustVolumeForVoiceChat(1085);
    } else {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_FIELD, SEQ_PC_02, 1);
        Sound_AdjustVolumeForVoiceChat(1086);
    }

    NARC_dtor(NARC_TradeList);

    return 1;
}

static void Trade_LoadPokemonSprite(NNSG2dCharacterData *characterData, int species, int form, int isEgg, int spriteSlot, Sprite *sprite)
{
    u8 *unused;

    GX_LoadOBJ(characterData->pRawData, ((4 * 32 + 18) + spriteSlot * (4 * 4)) * 0x20, (4 * 4) * 0x20);
    Sprite_SetExplicitPaletteOffset(sprite, PokeIconPaletteIndex(species, form, isEgg) + 10);
}

// makes choice ([playername]/[friendname]/quit) ???
static void ov88_0223B320(Trade *trade)
{
    Strbuf *playerName, *friendName, *quitMessage;
    TrainerInfo *playerInfo, *friendInfo;

    playerInfo = CommInfo_TrainerInfo(CommSys_CurNetId());
    friendInfo = CommInfo_TrainerInfo(CommSys_CurNetId() ^ 1);
    playerName = TrainerInfo_NameNewStrbuf(playerInfo, 26);
    friendName = TrainerInfo_NameNewStrbuf(friendInfo, 26);
    quitMessage = MessageLoader_GetNewStrbuf(trade->tradeMessages, MSG_QUIT);

    Trade_DisplayMessageFromStringBuffer(&trade->windows[0], playerName, 10, TEXT_SPEED_INSTANT, 1, 1);
    Trade_DisplayMessageFromStringBuffer(&trade->windows[1], friendName, 10, TEXT_SPEED_INSTANT, 1, 1);
    Trade_DisplayMessageFromStringBuffer(&trade->windows[6], quitMessage, 5, TEXT_SPEED_INSTANT, 1, 1);

    Strbuf_Free(quitMessage);
    Strbuf_Free(friendName);
    Strbuf_Free(playerName);
}

static void ov88_0223B3C0(Trade *trade)
{
    NARC *narc_TradeList = NARC_ctor(NARC_INDEX_DATA__TRADELIST, HEAP_ID_26);

    Trade_SetSubScreenBanks();
    Trade_BGInit(trade->bgConfig);
    ov88_0223C504(trade, narc_TradeList);
    ov88_0223B4F0(trade);
    ov88_0223B320(trade); // setup trainer names + quit option button?

    LoadMessageBoxGraphics(trade->bgConfig, BG_LAYER_MAIN_0, 512 - (9 + (18 + 12)), 10, Options_Frame(trade->playerData->options), HEAP_ID_26);
    LoadStandardWindowGraphics(trade->bgConfig, BG_LAYER_MAIN_0, 512 - 9, 11, 0, HEAP_ID_26);

    Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, trade->tradeMessages, trade->tradeStrTemplate);

    Bg_ToggleLayer(BG_LAYER_SUB_0, 1);
    Bg_ToggleLayer(BG_LAYER_SUB_1, 1);
    Bg_ToggleLayer(BG_LAYER_SUB_2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    Bg_ToggleLayer(BG_LAYER_MAIN_0, 1);
    Bg_ToggleLayer(BG_LAYER_MAIN_1, 1);
    Bg_ToggleLayer(BG_LAYER_MAIN_2, 1);
    Bg_ToggleLayer(BG_LAYER_MAIN_3, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);

    ov88_InitTransfer();
    ov88_0223C66C(trade, narc_TradeList);
    ov88_0223CBA0(trade);
    UnionTrade_drawPartySprites(trade->playerParty, 0, trade);
    UnionTrade_drawPartySprites(trade->friendParty, 6, trade);

    Sprite_SetDrawFlag(trade->sprites[0], TRUE);
    Sprite_SetDrawFlag(trade->sprites[1], TRUE);
    SetVBlankCallback(ov88_0223C0E0, trade);
    NARC_dtor(narc_TradeList);
}

static void ov88_0223B4F0(Trade *unionRoom)
{
    ov88_0223B710(unionRoom->tradeStrTemplate, unionRoom->playerParty, 0);
    ov88_0223B710(unionRoom->tradeStrTemplate, unionRoom->friendParty, 6);
    ov88_0223B748(&unionRoom->windows[7], unionRoom->tradeStrTemplate, unionRoom->tradeMessages, unionRoom->playerParty, 0);
    ov88_0223B748(&unionRoom->windows[13], unionRoom->tradeStrTemplate, unionRoom->tradeMessages, unionRoom->friendParty, 6);
    ov88_0223C4E0(unionRoom->bgConfig, Party_GetCurrentCount(unionRoom->playerParty), Party_GetCurrentCount(unionRoom->friendParty));
}

int ov88_0223B57C(ApplicationManager *appMan, int *step)
{
    Trade *trade = ApplicationManager_Data(appMan);
    int v1 = 0;

    switch (*step) {
    case 0:
        if (IsScreenFadeDone()) {
            *step = 1;

            ov88_0223B320(trade);
        }
        break;
    case 1:
        switch (trade->unk_48) {
        case 0:
            trade->unk_48 = ov88_0223B914(trade);
            break;
        case 1:
            trade->unk_48 = ov88_0223BED8(trade);
            Trade_AnimateSelectedPokemonOnTouch(trade);
            break;
        case 2:
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 8, 1, HEAP_ID_26);
            *step = 2;
            break;
        case 3:
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 8, 1, HEAP_ID_26);
            trade->unk_48 = 4;
            break;
        case 4:
            if (IsScreenFadeDone()) {
                ov88_0223BFD8(trade);
                UnionTrade_ClearSprites(trade);
                ov88_FreeBgTileMapBuffers(trade->bgConfig);

                trade->unk_44 = 1;
                trade->unk_48 = 5;

                Trade_InitPokemonSummary(trade, trade->selectedMonId[0] / 6);
            }
            break;
        case 5:
            if (ApplicationManager_Exec(trade->appMan)) {
                ApplicationManager_Free(trade->appMan);
                ov88_0223B3C0(trade);

                trade->unk_44 = 0;
                trade->selectedMonId[0] = trade->pokemonSummary.monIndex + trade->isChatot * 6;

                ov88_0223BE28(trade);
                Trade_AnimatePartyPokemon(trade->selectedMonId[0], trade->sprites[0], 0);
                sub_02039734(); // updates network icon

                trade->unk_48 = 6;
            }
            break;
        case 6:
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 8, 1, HEAP_ID_26);
            trade->unk_48 = 7;
            break;
        case 7:
            if (IsScreenFadeDone()) {
                trade->unk_48 = 1;
            }
            break;
        }
        break;
    case 2:
        if (IsScreenFadeDone()) {
            v1 = 1;
        }
        break;
    }

    if (!trade->unk_44) {
        ov88_0223E848(trade);
        SpriteList_Update(trade->spriteList);
    }

    sub_02038A1C(26, trade->bgConfig);

    return v1;
}

// something w/ setting nicknames for all of party?
static void ov88_0223B710(StringTemplate *nickTemplate, Party *party, int param2)
{
    int i;

    for (i = 0; i < Party_GetCurrentCount(party); i++) {
        StringTemplate_SetNickname(nickTemplate, i + param2, Pokemon_GetBoxPokemon(Party_GetPokemonBySlotIndex(party, i)));
    }
}

static void ov88_0223B748(Window *window, StringTemplate *stringTemplate, MessageLoader *messageLoader, Party *party, int firstEntryId)
{
    int i;

    for (i = 0; i < Party_GetCurrentCount(party); i++) {
        Strbuf *msg = MessageUtil_ExpandedStrbuf(stringTemplate, messageLoader, 1 + firstEntryId + i, HEAP_ID_26);

        Trade_DisplayMessageFromStringBuffer(&window[i], msg, 8, TEXT_SPEED_INSTANT, 1, 0);
        Strbuf_Free(msg);
    }
}

static void UnionTrade_drawPartySprites(Party *party, int offset, Trade *unionTrade)
{
    int i;
    int slot;

    for (i = 0; i < Party_GetCurrentCount(party); i++) {
        slot = i + offset;

        unionTrade->unk_7E8_pokemon[slot] = Graphics_GetCharData(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconSpriteIndex(unionTrade->tradePokemonData[slot].species, unionTrade->tradePokemonData[slot].isEgg, unionTrade->tradePokemonData[slot].form), 0, &unionTrade->charData[slot], HEAP_ID_26);

        DC_FlushRange(unionTrade->charData[slot]->pRawData, 0x20 * 4 * 4);

        Trade_LoadPokemonSprite(unionTrade->charData[slot], unionTrade->tradePokemonData[slot].species, unionTrade->tradePokemonData[slot].form, unionTrade->tradePokemonData[slot].isEgg, slot, unionTrade->partySprites[slot]);
        Sprite_SetDrawFlag(unionTrade->partySprites[slot], TRUE);

        if (unionTrade->tradePokemonData[slot].holdsMail == 0) {
            Sprite_SetDrawFlag(unionTrade->heldMailSprites[slot], FALSE);
        } else {
            Sprite_SetDrawFlag(unionTrade->heldMailSprites[slot], TRUE);
            Sprite_SetAnim(unionTrade->heldMailSprites[slot], 3 + unionTrade->tradePokemonData[slot].holdsMail - 1);
        }

        if (unionTrade->tradePokemonData[slot].hasBallCapsule == 0) {
            Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[slot], FALSE);
        } else {
            Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[slot], TRUE);
            Sprite_SetAnim(unionTrade->ballCapsuleSprites[slot], 21);
        }
    }

    for (; i < 6; i++) {
        Sprite_SetDrawFlag(unionTrade->partySprites[i + offset], FALSE);
        Sprite_SetDrawFlag(unionTrade->heldMailSprites[i + offset], FALSE);
        Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[i + offset], FALSE);
    }
}

static int ov88_0223B914(Trade *unionTrade)
{
    ov88_0223E998(unionTrade);

    switch (unionTrade->currentTradeStep) {
    case TRADE_START:
        CommTiming_StartSync(80);
        ResetLock(RESET_LOCK_0x2);
        Trade_AddWaitDial(unionTrade);

        int i, form, species;

        for (i = 0; i < Party_GetCurrentCount(unionTrade->playerData->currentParty); i++) {
            Pokemon *mon = Party_GetPokemonBySlotIndex(unionTrade->playerData->currentParty, i);

            species = Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (species == SPECIES_SHAYMIN) {
                form = Pokemon_GetValue(mon, MON_DATA_FORM, NULL);

                if (form != SHAYMIN_FORM_LAND) {
                    Pokemon_SetShayminForm(mon, SHAYMIN_FORM_LAND);
                }
            }
        }

        unionTrade->currentTradeStep++;
        break;
    case 1:
        if (CommTiming_IsSyncState(80)) {
            if (unionTrade->playerData->unk_34 == 0) {
                unionTrade->currentTradeStep = 6;
            } else {
                unionTrade->currentTradeStep = 2;
            }

            if (CommSys_CurNetId() == 0) {
                Trade_SendByteData(CommSys_CurNetId(), 31, LCRNG_RandMod(60) + 3);
            }

            UnionTrade_SendRibbonData(unionTrade->saveData);
            ov88_0223E984(unionTrade);
        }
        break;
    case 2:
        if (unionTrade->unk_2318 != 0) {
            unionTrade->currentTradeStep++;
        }
        break;
    case 3:
        unionTrade->unk_2318--;

        if (unionTrade->unk_2318 == 0) {
            unionTrade->currentTradeStep = 4;
        }
        break;
    case 4:
        sub_02038ED4(&unionTrade->unk_36F4);
        unionTrade->currentTradeStep++;
        break;
    case 5:
        if (sub_02038EDC(unionTrade->saveData, 2, &unionTrade->unk_36F4)) {
            unionTrade->currentTradeStep++;
        }
        break;
    case 6:
        sub_0203632C(1);
        CommTiming_StartSync(81);
        unionTrade->currentTradeStep++;
        break;
    case 7:
        if (CommTiming_IsSyncState(81)) {
            unionTrade->currentTradeStep++;
        }
        break;
    case 8:
        unionTrade->unk_50 = 0;
        unionTrade->unk_54 = 0;
        unionTrade->unk_58 = 0;

        if (CommSys_CurNetId() == 1) {
            ov88_0223D098(CommSys_CurNetId(), unionTrade->playerParty, unionTrade->unk_50);
            unionTrade->unk_50++;
        }

        unionTrade->currentTradeStep++;
        break;
    case 9:
        if (unionTrade->unk_54 != 0) {
            unionTrade->currentTradeStep = 10;
        }
        break;
    case 10:
        unionTrade->currentTradeStep++;
        ov88_0223B4F0(unionTrade);
        break;
    case 11: {
        int i, v6;

        for (i = 0; i < 13; i++) {
            unionTrade->tradePokemonData[i].species = 0;
        }

        for (i = 0; i < Party_GetCurrentCount(unionTrade->playerParty); i++) {
            Pokemon *playerPokemon = Party_GetPokemonBySlotIndex(unionTrade->playerParty, i);
            UnionTrade_getTradePokemonFromMon(playerPokemon, &unionTrade->tradePokemonData[i]);
        }

        for (i = 0; i < Party_GetCurrentCount(unionTrade->friendParty); i++) {
            Pokemon *friendPokemon = Party_GetPokemonBySlotIndex(unionTrade->friendParty, i);
            UnionTrade_getTradePokemonFromMon(friendPokemon, &unionTrade->tradePokemonData[i + 6]);
        }

        unionTrade->tradePokemonData[12].species = 1;
    }
        unionTrade->currentTradeStep++;
        break;
    case 12:
        Trade_CreateNetworkObject(CommInfo_TrainerInfo(CommSys_CurNetId()), unionTrade->playerPalPad, &unionTrade->friendPalPad);
        unionTrade->currentTradeStep++;
        break;
    case 13:
        if (unionTrade->unk_54 == 3) {
            unionTrade->currentTradeStep++;
        }
        break;
    case TRADE_SEND_CHATOT_CRY:
        ov88_sendChatotCry(SaveData_GetChatotCry(unionTrade->saveData));
        unionTrade->currentTradeStep++;
        break;
    case 15:
        if (unionTrade->unk_54 == 4) {
            unionTrade->currentTradeStep++;

            GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);
            UnionTrade_drawPartySprites(unionTrade->playerParty, 0, unionTrade);
            UnionTrade_drawPartySprites(unionTrade->friendParty, 6, unionTrade);

            {
                int i;

                for (i = 0; i < 2; i++) {
                    Sprite_SetDrawFlag(unionTrade->sprites[i], TRUE);
                }
            }
        }
        break;
    case 16:
        BrightnessController_StartTransition(8, 0, -16, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, BRIGHTNESS_MAIN_SCREEN);
        Bg_ToggleLayer(BG_LAYER_MAIN_1, 1);
        Bg_ToggleLayer(BG_LAYER_MAIN_2, 1);
        Bg_ToggleLayer(BG_LAYER_MAIN_3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);

        unionTrade->currentTradeStep++;
        break;
    case 17:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN)) {
            Pokemon *firstMonInPlayerParty = Party_GetPokemonBySlotIndex(unionTrade->playerParty, 0);

            unionTrade->unk_2168 = ov88_0223C800(0, firstMonInPlayerParty, unionTrade->unk_848[0], &unionTrade->unk_2148[0]);
            ov88_0223C8D8(unionTrade->windows, 0, unionTrade->playerParty, 0, unionTrade);
            unionTrade->currentTradeStep++;
        }
        break;
    case 18:
        BrightnessController_StartTransition(8, 0, -16, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, BRIGHTNESS_SUB_SCREEN);
        Bg_ToggleLayer(BG_LAYER_SUB_0, 1);
        Bg_ToggleLayer(BG_LAYER_SUB_1, 1);
        Bg_ToggleLayer(BG_LAYER_SUB_2, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

        unionTrade->currentTradeStep++;
        Trade_RemoveWaitDial(unionTrade);
        break;
    case 19:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN)) {
            Window_EraseMessageBox(&unionTrade->windows[WINDOW_MAIN_MESSAGES], 0);
            Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
            Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
            ResetUnlock(RESET_LOCK_0x2);

            return 1;
        }

        break;
    }

    return 0;
}

static void UnionTrade_getTradePokemonFromMon(Pokemon *pokemon, Trade_PokemonData *tradePokemon)
{
    int encryptionState, heldItem;

    encryptionState = Pokemon_EnterDecryptionContext(pokemon);

    tradePokemon->pokeball = Pokemon_GetValue(pokemon, MON_DATA_POKEBALL, NULL);
    tradePokemon->species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
    tradePokemon->form = Pokemon_GetValue(pokemon, MON_DATA_FORM, NULL);
    tradePokemon->isEgg = Pokemon_GetValue(pokemon, MON_DATA_IS_EGG, NULL);
    tradePokemon->gender = Pokemon_GetValue(pokemon, MON_DATA_GENDER, NULL);
    tradePokemon->hasBallCapsule = Pokemon_GetValue(pokemon, MON_DATA_BALL_CAPSULE_ID, NULL);

    heldItem = Pokemon_GetValue(pokemon, MON_DATA_HELD_ITEM, NULL);

    Pokemon_ExitDecryptionContext(pokemon, encryptionState);

    if (tradePokemon->species != 0) {
        tradePokemon->formValue = SpeciesData_GetFormValue(tradePokemon->species, tradePokemon->form, 28);
    }

    if (heldItem != 0) {
        tradePokemon->holdsMail = Item_IsMail(heldItem) + 1;
    }
}

static void ov88_0223BDA4(Trade *trade, int slot)
{
    Pokemon *friendSelectedMon = Party_GetPokemonBySlotIndex(trade->friendParty, slot % 6);

    trade->unk_2168 = ov88_0223C800(1, friendSelectedMon, trade->unk_848[slot / 6], &trade->unk_2148[slot / 6]);

    ov88_0223C8D8(trade->windows, 1, trade->friendParty, slot % 6, trade);
    Sprite_SetAnim(trade->pokemonBattleSprites[3], trade->tradePokemonData[slot].pokeball + 6 - 1);
}

static void ov88_0223BE28(Trade *unionTrade)
{
    if (unionTrade->selectedMonId[0] != 12) {
        if (unionTrade->selectedMonId[0] < 6) {
            Pokemon *playerSelectedMon = Party_GetPokemonBySlotIndex(unionTrade->playerParty, unionTrade->selectedMonId[0]);

            unionTrade->unk_2168 = ov88_0223C800(0, playerSelectedMon, unionTrade->unk_848[unionTrade->selectedMonId[0] / 6], &unionTrade->unk_2148[unionTrade->selectedMonId[0] / 6]);

            ov88_0223C8D8(unionTrade->windows, 0, unionTrade->playerParty, unionTrade->selectedMonId[0], unionTrade);
            ov88_0223CB34(unionTrade->windows, 1, unionTrade);
            Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[3], FALSE);
        } else {
            ov88_0223BDA4(unionTrade, unionTrade->selectedMonId[0]);
            ov88_0223CB34(unionTrade->windows, 0, unionTrade);
            Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[2], FALSE);
        }
    }
}

static int ov88_0223BED8(Trade *unionTrade)
{
    if (unionTrade->nextFunction != NULL) {
        unionTrade->unk_140 = unionTrade->nextFunction(unionTrade);
    }

    switch (unionTrade->unk_140) {
    case 0:
        break;
    case 2:
        return 2;
        break;
    case 1:
        break;
    case 3:
        return 3;
        break;
    }

    if (ov88_0223CFF4(&unionTrade->unk_14C[0], &unionTrade->selectedMonId[0], unionTrade->sprites[0], unionTrade->tradePokemonData, 0)) {
        ov88_0223BE28(unionTrade);
    }

    ov88_0223CFF4(&unionTrade->unk_14C[1], &unionTrade->selectedMonId[1], unionTrade->sprites[1], unionTrade->tradePokemonData, 1);
    ov88_0223CEF0(&unionTrade->unk_90);
    Trade_SendData(unionTrade, 23, unionTrade->selectedMonId[0]);

    return 1;
}

static void UnionTrade_ClearSprites(Trade *unionTrade)
{
    int i;

    SpriteTransfer_ResetCharTransfer(unionTrade->spriteResource[0][0]);
    SpriteTransfer_ResetCharTransfer(unionTrade->spriteResource[1][0]);

    SpriteTransfer_ResetPlttTransfer(unionTrade->spriteResource[0][1]);
    SpriteTransfer_ResetPlttTransfer(unionTrade->spriteResource[1][1]);

    for (i = 0; i < 4; i++) {
        SpriteResourceCollection_Delete(unionTrade->unk_324[i]);
    }

    SpriteList_Delete(unionTrade->spriteList);
    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();
}

static void ov88_0223BFD8(Trade *unionTrade)
{
    int i;

    for (i = 0; i < Party_GetCurrentCount(unionTrade->playerParty); i++) {
        Heap_Free(unionTrade->unk_7E8_pokemon[i]);
    }

    for (i = 0; i < Party_GetCurrentCount(unionTrade->friendParty); i++) {
        Heap_Free(unionTrade->unk_7E8_pokemon[i + 6]);
    }
}

// clean up
int ov88_0223C03C(ApplicationManager *appMan, int *unused)
{
    Trade *unionTrade = ApplicationManager_Data(appMan);
    UnkStruct_ov88_playerData *playerData = ApplicationManager_Args(appMan);
    int unused2;

    playerData->unk_28 = unionTrade->unk_5C;

    ov88_0223BFD8(unionTrade);

    Strbuf_Free(unionTrade->itemMessage);
    Heap_Free(unionTrade->friendParty);

    UnionTrade_ClearSprites(unionTrade);
    ov88_RemoveWindows(unionTrade->windows);
    ov88_FreeBgTileMapBuffers(unionTrade->bgConfig);

    Heap_FreeExplicit(HEAP_ID_26, unionTrade->bgConfig);
    MessageLoader_Free(unionTrade->tradeMessages);
    StringTemplate_Free(unionTrade->stringTemplate2);
    StringTemplate_Free(unionTrade->nicknameTemplate);
    StringTemplate_Free(unionTrade->tradeStrTemplate);
    Strbuf_Free(unionTrade->trainerName);
    ApplicationManager_FreeData(appMan);
    SetVBlankCallback(NULL, NULL);
    Heap_Destroy(HEAP_ID_26);

    return 1;
}

static void ov88_0223C0E0(void *unionTradePointer)
{
    Trade *unionTrade = (Trade *)unionTradePointer;

    Bg_RunScheduledUpdates(unionTrade->bgConfig);

    if (unionTrade->unk_2168) {
        int v1 = unionTrade->unk_2168 - 1;

        GXS_LoadOBJ(unionTrade->unk_848[v1], 0 + v1 * (0x20 * 10 * 10), 0x20 * 10 * 10);
        Graphics_LoadPalette(unionTrade->unk_2148[v1].narcID, unionTrade->unk_2148[v1].palette, 5, 0x20 * (2 + v1), 32, HEAP_ID_26);

        unionTrade->unk_2168 = 0;
    }

    VramTransfer_Process();
    RenderOam_Transfer();

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void Trade_SetSubScreenBanks(void)
{
    UnkStruct_02099F80 banks = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_128_B,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE
    };

    GXLayers_SetBanks(&banks);
}

static void Trade_BGInit(BgConfig *bgConfig)
{
    {
        GraphicsModes graphicsModes = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&graphicsModes);
    }

    {
        BgTemplate bgMain0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_0, &bgMain0, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate bgMain1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_1, &bgMain1, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate bgMain2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_2, &bgMain2, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate bgMain3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_3, &bgMain3, 0);
    }

    {
        BgTemplate bgSub0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_SUB_0, &bgSub0, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_SUB_0);
    }

    {
        BgTemplate bgSub1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_SUB_1, &bgSub1, 0);
    }

    {
        BgTemplate bgSub2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_SUB_2, &bgSub2, 0);
    }

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_26);
    Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_26);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_26);

    {
        int i;

        for (i = 0; i < 4; i++) {
            Bg_SetOffset(bgConfig, BG_LAYER_MAIN_0 + i, 0, 0);
            Bg_SetOffset(bgConfig, BG_LAYER_MAIN_0 + i, 3, 0);
            Bg_SetOffset(bgConfig, BG_LAYER_SUB_0 + i, 0, 0);
            Bg_SetOffset(bgConfig, BG_LAYER_SUB_0 + i, 3, 0);
        }
    }

    Bg_ToggleLayer(BG_LAYER_MAIN_0, 0);
    Bg_ToggleLayer(BG_LAYER_MAIN_1, 0);
    Bg_ToggleLayer(BG_LAYER_MAIN_2, 0);
    Bg_ToggleLayer(BG_LAYER_MAIN_3, 0);
    Bg_ToggleLayer(BG_LAYER_SUB_0, 0);
    Bg_ToggleLayer(BG_LAYER_SUB_1, 0);
    Bg_ToggleLayer(BG_LAYER_SUB_2, 0);

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
}

static void ov88_0223C370(Trade *unionTrade, ApplicationManager *appMan)
{
    UnkStruct_ov88_playerData *tradeAppMan = ApplicationManager_Args(appMan);

    unionTrade->playerData = tradeAppMan;
    unionTrade->unused = 4;
    unionTrade->unk_44 = 0;
    unionTrade->unk_6C8 = 0;
    unionTrade->unk_16C = 6;
    unionTrade->unk_170 = 6;
    unionTrade->selectedMonId[0] = 0; // player's selected mon
    unionTrade->selectedMonId[1] = 6; // friend's selected mon.
    unionTrade->unk_140 = 0;
    unionTrade->unk_48 = 0;
    unionTrade->currentTradeStep = 0;
    unionTrade->nextFunction = ov88_0223D150;
    unionTrade->unk_60[0] = 0;
    unionTrade->unk_60[1] = 0;
    unionTrade->unk_5C = 0;
    unionTrade->unk_2168 = 0;
    unionTrade->lastSentData = -1;
    unionTrade->lastSentCmd = -1;
    unionTrade->unk_2318 = 0;
    unionTrade->unk_3704 = 0;
    unionTrade->unk_3708 = 0;
    unionTrade->playerParty = tradeAppMan->currentParty;
    unionTrade->playerPalPad = tradeAppMan->palPad;
    unionTrade->saveData = tradeAppMan->saveData;
    unionTrade->friendParty = Heap_Alloc(HEAP_ID_26, Party_SaveSize());

    Party_InitWithCapacity(unionTrade->friendParty, 6);
    memset(unionTrade->friendParty, 0xff, Party_SaveSize());

    unionTrade->trainerName = TrainerInfo_NameNewStrbuf(tradeAppMan->trainerInfo, 26);
    unionTrade->itemMessage = MessageLoader_GetNewStrbuf(unionTrade->tradeMessages, MSG_ITEM);

    WiFiHistory_FlagGeonetLinkInfo(tradeAppMan->wiFiHistory);
}

static void ov88_FreeBgTileMapBuffers(BgConfig *bgConfig)
{
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_SUB_0);

    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(bgConfig, BG_LAYER_MAIN_0);
}

static void ov88_0223C488(NARC *narc, u32 narcMemberId, BgConfig *bgConfig, u32 param3, u32 param4, u32 param5, BOOL compressed, u32 heapID)
{
    void *pNscrFile = LoadMemberFromOpenNARC(narc, narcMemberId, compressed, heapID, 1);

    if (pNscrFile != NULL) {
        NNSG2dScreenData *screenData;

        if (NNS_G2dGetUnpackedScreenData(pNscrFile, &screenData)) {
            if (param5 == 0) {
                param5 = screenData->szByte;
            }

            if (Bg_GetTilemapBuffer(bgConfig, param3) != NULL) {
                Bg_LoadTilemapBuffer(bgConfig, param3, screenData->rawData, param5);
            }
        }

        Heap_Free(pNscrFile);
    }
}

static void ov88_0223C4E0(BgConfig *param0, int param1, int param2)
{
    int v0;
    Bg_CopyTilemapBufferRangeToVRAM(param0, 2, Bg_GetTilemapBuffer(param0, 2), 32 * 24 * 2, 0);
}

static void ov88_0223C504(Trade *unionRoom, NARC *narc)
{
    BgConfig *bgConfig = unionRoom->bgConfig;

    Graphics_LoadPaletteFromOpenNARC(narc, 0, 4, 0, 16 * 9 * 2, HEAP_ID_26);
    Graphics_LoadPaletteFromOpenNARC(narc, 0, 0, 0, 16 * 9 * 2, HEAP_ID_26);
    Bg_MaskPalette(BG_LAYER_MAIN_0, 0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0);
    Font_LoadScreenIndicatorsPalette(0, 13 * 32, HEAP_ID_26);
    Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 1, bgConfig, 2, 0, 16 * 18 * 0x20, 1, HEAP_ID_26);

    ov88_0223C488(narc, 3, bgConfig, 2, 0, 32 * 24 * 2, 1, HEAP_ID_26);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 4, bgConfig, 3, 0, 32 * 24 * 2, 1, HEAP_ID_26);
    Font_LoadScreenIndicatorsPalette(0, 2 * 32, HEAP_ID_26);
    Font_LoadTextPalette(0, 3 * 32, HEAP_ID_26);
    Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 2, bgConfig, 5, 0, 16 * 4 * 0x20, 1, HEAP_ID_26);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 5, bgConfig, 5, 0, 32 * 24 * 2, 1, HEAP_ID_26);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 6, bgConfig, 6, 0, 32 * 24 * 2, 1, HEAP_ID_26);
    Font_LoadScreenIndicatorsPalette(4, 2 * 32, HEAP_ID_26);
    Font_LoadTextPalette(4, 3 * 32, HEAP_ID_26);
    Bg_ClearTilemap(bgConfig, BG_LAYER_SUB_0);
}

static void ov88_InitTransfer(void)
{
    {
        CharTransferTemplate v0 = {
            20, 2048, 2048, HEAP_ID_26
        };

        CharTransfer_Init(&v0);
    }

    PlttTransfer_Init(20, HEAP_ID_26);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void ov88_0223C66C(Trade *unionTrade, NARC *param1)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 127, 0, 32, 0, 127, 0, 32, 26);

    unionTrade->spriteList = SpriteList_InitRendering(2 + 12 + 12 + 12 + 2 + 2 + 2 + 1, &unionTrade->renderer, HEAP_ID_26);

    for (v0 = 0; v0 < 4; v0++) {
        unionTrade->unk_324[v0] = SpriteResourceCollection_New(2, v0, HEAP_ID_26);
    }

    unionTrade->spriteResource[0][0] = SpriteResourceCollection_AddTilesFrom(unionTrade->unk_324[0], param1, 7, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_26);
    unionTrade->spriteResource[0][1] = SpriteResourceCollection_AddPaletteFrom(unionTrade->unk_324[1], param1, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAP_ID_26);
    unionTrade->spriteResource[0][2] = SpriteResourceCollection_AddFrom(unionTrade->unk_324[2], param1, 8, 1, 0, 2, HEAP_ID_26);
    unionTrade->spriteResource[0][3] = SpriteResourceCollection_AddFrom(unionTrade->unk_324[3], param1, 9, 1, 0, 3, HEAP_ID_26);
    unionTrade->spriteResource[1][0] = SpriteResourceCollection_AddTilesFrom(unionTrade->unk_324[0], param1, 10, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAP_ID_26);
    unionTrade->spriteResource[1][1] = SpriteResourceCollection_AddPaletteFrom(unionTrade->unk_324[1], param1, 0, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 10, HEAP_ID_26);
    unionTrade->spriteResource[1][2] = SpriteResourceCollection_AddFrom(unionTrade->unk_324[2], param1, 11, 1, 1, 2, HEAP_ID_26);
    unionTrade->spriteResource[1][3] = SpriteResourceCollection_AddFrom(unionTrade->unk_324[3], param1, 12, 1, 1, 3, HEAP_ID_26);

    SpriteTransfer_RequestChar(unionTrade->spriteResource[0][0]);
    SpriteTransfer_RequestChar(unionTrade->spriteResource[1][0]);
    SpriteTransfer_RequestPlttWholeRange(unionTrade->spriteResource[0][1]);
    SpriteTransfer_RequestPlttWholeRange(unionTrade->spriteResource[1][1]);
    Graphics_LoadPalette(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconPalettesFileIndex(), 1, 10 * 0x20, 0x20 * 4, HEAP_ID_26);
}

static int ov88_0223C800(int loadCount, Pokemon *pokemon, u8 *startAddress, PokemonSpriteTemplate *spriteTemplate)
{
    Pokemon_BuildSpriteTemplate(spriteTemplate, pokemon, 2);
    {
        int personality = Pokemon_GetValue(pokemon, MON_DATA_PERSONALITY, NULL);
        enum Species species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);

        CharacterSprite_LoadPokemonSpriteRect(spriteTemplate->narcID, spriteTemplate->character, HEAP_ID_26, 0, 0, 10, 10, startAddress, personality, FALSE, FACE_FRONT, species);
    }

    DC_FlushRange(startAddress, 0x20 * 10 * 10);

    return loadCount + 1;
}

static void ov88_0223C860(Window *window, Party *party, int slot, int unused, int xOffset)
{
    Strbuf *strBuffer = Strbuf_Init(20, HEAP_ID_26);

    Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, slot), MON_DATA_NICKNAME_STRING, strBuffer);
    Window_FillTilemap(window, 0);
    Trade_DisplayMessageFromStringBuffer(window, strBuffer, unused, TEXT_SPEED_INSTANT, xOffset, 1);
    Strbuf_Free(strBuffer);
}

/**
 * Gets if gender should be displayed for this pokemon.
 */
static int UnionTrade_GetDisplayGender(Trade_PokemonData *tradePokemon, Party *party, int slot, int gender)
{

    if ((tradePokemon->species == SPECIES_NIDORAN_F) || (tradePokemon->species == SPECIES_NIDORAN_M)) {
        Pokemon *pokemon = Party_GetPokemonBySlotIndex(party, slot);
        int hasNickname = Pokemon_GetValue(pokemon, MON_DATA_HAS_NICKNAME, NULL);

        if (hasNickname == 0) {
            return 2;
        }
    }

    return gender;
}

static void ov88_0223C8D8(Window *window, int playerId, Party *party, int partySlot, Trade *unionRoom)
{
    Strbuf *strBuffer, *heldItemName;
    u16 item, pokemonLevel;
    int v4;
    Pokemon *v5 = Party_GetPokemonBySlotIndex(party, partySlot);
    v4 = Pokemon_SpriteYOffset(v5, 2);

    Sprite_SetDrawFlag(unionRoom->pokemonBattleSprites[playerId], TRUE);
    Trade_SetSpritePosition(unionRoom->pokemonBattleSprites[playerId], Unk_ov88_0223EF54[playerId][0], Unk_ov88_0223EF54[playerId][1] + v4 + 192);

    if (playerId == 0) {
        Sprite_SetFlipMode(unionRoom->pokemonBattleSprites[playerId], unionRoom->tradePokemonData[partySlot].formValue);
    }

    Sprite_SetAnim(unionRoom->pokemonBattleSprites[2 + playerId], unionRoom->tradePokemonData[partySlot].pokeball + 6 - 1);
    Sprite_SetDrawFlag(unionRoom->pokemonBattleSprites[2 + playerId], TRUE);
    ov88_0223C860(&window[26 + playerId], party, partySlot, 9, 6);

    {
        int monDisplayGender = unionRoom->tradePokemonData[playerId * 6 + partySlot].gender;

        monDisplayGender = UnionTrade_GetDisplayGender(&unionRoom->tradePokemonData[playerId * 6 + partySlot], party, partySlot, monDisplayGender);

        if (unionRoom->tradePokemonData[playerId * 6 + partySlot].isEgg) {
            monDisplayGender = 2;
        }

        switch (monDisplayGender) {
        case 2: // don't display gender
            Sprite_SetDrawFlag(unionRoom->pokemonBattleSprites[4 + playerId], FALSE);
            break;
        case 0:
            Sprite_SetDrawFlag(unionRoom->pokemonBattleSprites[4 + playerId], TRUE);
            Sprite_SetAnim(unionRoom->pokemonBattleSprites[4 + playerId], 22 + 1);
            break;
        case 1:
            Sprite_SetDrawFlag(unionRoom->pokemonBattleSprites[4 + playerId], TRUE);
            Sprite_SetAnim(unionRoom->pokemonBattleSprites[4 + playerId], 22);
            break;
        }
    }

    if (!unionRoom->tradePokemonData[playerId * 6 + partySlot].isEgg) {
        strBuffer = Strbuf_Init(10, HEAP_ID_26);
        Window_FillTilemap(&window[28 + playerId], 0);
        MessageLoader_GetStrbuf(unionRoom->tradeMessages, MSG_LV, strBuffer);
        Trade_DisplayMessageFromStringBuffer(&window[28 + playerId], strBuffer, 9, TEXT_SPEED_NO_TRANSFER, 6, 0);

        pokemonLevel = Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, partySlot), MON_DATA_LEVEL, NULL);
        Strbuf_FormatInt(strBuffer, pokemonLevel, 3, 0, 1);
        Trade_DisplayMessageFromStringBuffer(&window[28 + playerId], strBuffer, 9, TEXT_SPEED_INSTANT, 24 + 6, 0);
        Strbuf_Free(strBuffer);
    } else {
        Window_ClearAndCopyToVRAM(&window[28 + playerId]);
    }

    Trade_DisplayMessageFromStringBuffer(&window[30 + playerId], unionRoom->itemMessage, 7, TEXT_SPEED_INSTANT, 3, 0);

    item = Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, partySlot), MON_DATA_HELD_ITEM, NULL);
    Window_FillTilemap(&window[32 + playerId], 0);

    heldItemName = Strbuf_Init(20, HEAP_ID_26);
    Item_LoadName(heldItemName, item, HEAP_ID_26);
    Trade_DisplayMessageFromStringBuffer(&window[32 + playerId], heldItemName, 9, TEXT_SPEED_INSTANT, 3, 0);
    Strbuf_Free(heldItemName);
}

static void ov88_0223CB34(Window *window, int slot, Trade *unionTrade)
{
    Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[slot], FALSE);
    Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[2 + slot], FALSE);
    Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[4 + slot], FALSE);
    Window_ClearAndCopyToVRAM(&window[26 + slot]);
    Window_ClearAndCopyToVRAM(&window[28 + slot]);
    Window_ClearAndCopyToVRAM(&window[30 + slot]);
    Window_ClearAndCopyToVRAM(&window[32 + slot]);
}

static void ov88_0223CBA0(Trade *unionTrade)
{
    SpriteResourcesHeader_Init(&unionTrade->resourceHeader, 0, 0, 0, 0, 0xffffffff, 0xffffffff, 0, 2, unionTrade->unk_324[0], unionTrade->unk_324[1], unionTrade->unk_324[2], unionTrade->unk_324[3], NULL, NULL);
    SpriteResourcesHeader_Init(&unionTrade->unk_378, 1, 1, 1, 1, 0xffffffff, 0xffffffff, 0, 0, unionTrade->unk_324[0], unionTrade->unk_324[1], unionTrade->unk_324[2], unionTrade->unk_324[3], NULL, NULL);

    {
        AffineSpriteListTemplate sprite;
        int i;

        sprite.list = unionTrade->spriteList;
        sprite.resourceData = &unionTrade->resourceHeader;
        sprite.position.x = FX32_CONST(32);
        sprite.position.y = FX32_CONST(96);
        sprite.position.z = 0;
        sprite.affineScale.x = FX32_ONE;
        sprite.affineScale.y = FX32_ONE;
        sprite.affineScale.z = FX32_ONE;
        sprite.affineZRotation = 0;
        sprite.priority = 0;
        sprite.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        sprite.heapID = HEAP_ID_26;

        // drawing the nameplates for player + friend?
        for (i = 0; i < 2; i++) {
            sprite.position.x = FX32_ONE * UnionTrade_SpritePositions[i][0];
            sprite.position.y = FX32_ONE * UnionTrade_SpritePositions[i][1];
            unionTrade->sprites[i] = SpriteList_AddAffine(&sprite);
            Sprite_SetAnimateFlag(unionTrade->sprites[i], 1);
            Trade_AnimatePartyPokemon(unionTrade->selectedMonId[i], unionTrade->sprites[i], i);
            Sprite_SetPriority(unionTrade->sprites[i], 100);
            Sprite_SetDrawFlag(unionTrade->sprites[i], FALSE);
        }

        for (i = 0; i < 12; i++) {
            sprite.position.x = FX32_ONE * (UnionTrade_SpritePositions[i][0] + 16);
            sprite.position.y = FX32_ONE * (UnionTrade_SpritePositions[i][1] - 6);
            unionTrade->partySprites[i] = SpriteList_AddAffine(&sprite);
            Sprite_SetAnimateFlag(unionTrade->partySprites[i], 1);
            Sprite_SetAnim(unionTrade->partySprites[i], 5 + i);
            Sprite_SetPriority(unionTrade->partySprites[i], 5);
            Sprite_SetDrawFlag(unionTrade->partySprites[i], FALSE);
        }

        // setup held mail sprites
        for (i = 0; i < 12; i++) {
            sprite.position.x = FX32_ONE * (UnionTrade_SpritePositions[i][0] + 16 + 20);
            sprite.position.y = FX32_ONE * (UnionTrade_SpritePositions[i][1] + 16);
            sprite.priority = 0;
            unionTrade->heldMailSprites[i] = SpriteList_AddAffine(&sprite);
            Sprite_SetPriority(unionTrade->heldMailSprites[i], 3);
            Sprite_SetDrawFlag(unionTrade->heldMailSprites[i], FALSE);
        }

        // setup ball capsule sprites
        for (i = 0; i < 12; i++) {
            sprite.position.x = FX32_ONE * (UnionTrade_SpritePositions[i][0] + 16 + 20 + 9);
            sprite.position.y = FX32_ONE * (UnionTrade_SpritePositions[i][1] + 16);
            sprite.priority = 0;
            unionTrade->ballCapsuleSprites[i] = SpriteList_AddAffine(&sprite);
            Sprite_SetPriority(unionTrade->ballCapsuleSprites[i], 3);
            Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[i], FALSE);
        }

        sprite.position.x = FX32_ONE * (128 - 4 * 8);
        sprite.position.y = FX32_ONE * (8 * 8 + 2);
        unionTrade->unk_47C = SpriteList_AddAffine(&sprite);
        Sprite_SetAnimateFlag(unionTrade->unk_47C, 1);
        Sprite_SetAnim(unionTrade->unk_47C, 20);
        Sprite_SetDrawFlag(unionTrade->unk_47C, FALSE);

        // setup bottom screen selected pokemon sprites
        for (i = 0; i < 6; i++) {
            sprite.resourceData = &unionTrade->unk_378;
            sprite.position.x = FX32_ONE * Unk_ov88_0223EF54[i][0];
            sprite.position.y = FX32_ONE * (Unk_ov88_0223EF54[i][1]) + (192 << FX32_SHIFT);
            sprite.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
            unionTrade->pokemonBattleSprites[i] = SpriteList_AddAffine(&sprite);
            Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[i], FALSE);
            Sprite_SetAnimateFlag(unionTrade->pokemonBattleSprites[i], 0);
            Sprite_SetAnim(unionTrade->pokemonBattleSprites[i], Unk_ov88_0223EF54[i][2]);
        }
    }
}

static void ov88_0223CE34(u32 *pressedKey)
{
    int repeats = 0;
    int key = 0;

    if (gSystem.pressedKeysRepeatable & PAD_KEY_UP) {
        key = 1;
        repeats++;
    }

    if (gSystem.pressedKeysRepeatable & PAD_KEY_DOWN) {
        key = 2;
        repeats++;
    }

    if (gSystem.pressedKeysRepeatable & PAD_KEY_LEFT) {
        key = 3;
        repeats++;
    }

    if (gSystem.pressedKeysRepeatable & PAD_KEY_RIGHT) {
        key = 4;
        repeats++;
    }

    if (repeats) {
        *pressedKey = key;
    }
}

static const TouchScreenRect Trade_BottomScreenPokemonDisplay[] = {
    { 0x38, 0x88, 0x18, 0x68 },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static void Trade_AnimateSelectedPokemonOnTouch(Trade *unionTrade)
{
    u16 species, form;
    int selectedPokemonPressed = -1, unused;

    if (unionTrade->selectedMonId[0] >= 6) {
        return;
    }

    selectedPokemonPressed = TouchScreen_CheckRectanglePressed(Trade_BottomScreenPokemonDisplay);

    if (selectedPokemonPressed != TOUCHSCREEN_INPUT_NONE) {
        if (unionTrade->tradePokemonData[unionTrade->selectedMonId[0]].isEgg) {
            return;
        }

        species = unionTrade->tradePokemonData[unionTrade->selectedMonId[0]].species;
        form = unionTrade->tradePokemonData[unionTrade->selectedMonId[0]].form;

        if (species == SPECIES_CHATOT) {
            Sound_PlayChatotCry(SaveData_GetChatotCry(unionTrade->saveData), 0, 100, 0);
        } else {
            Sound_PlayPokemonCry(species, form);
        }

        Sprite_SetAnimateFlag(unionTrade->pokemonBattleSprites[selectedPokemonPressed], 1);
        Sprite_SetAnim(unionTrade->pokemonBattleSprites[selectedPokemonPressed], 4 + selectedPokemonPressed);
    }
}

static void ov88_0223CEF0(u16 *angle)
{
    fx32 degrees;
    GXRgb color;
    int v2, green, v4;

    *angle += 20;

    if (*angle > 360) {
        *angle = 0;
    }

    degrees = CalcSineDegrees_Wraparound(*angle);
    green = 15 + (degrees * 10) / FX32_ONE;
    color = GX_RGB(29, green, 0);

    GX_LoadOBJPltt((u16 *)&color, (16 + 13) * 2, 2);
}

static int ov88_0223CF30(int param0, int param1, Trade_PokemonData *tradePokemonData)
{
    int i, v1 = 0;

    for (i = 0; i < 6; i++) {
        if (tradePokemonData[Unk_ov88_0223F004[param0][param1][i]].species != 0) {
            v1 = Unk_ov88_0223F004[param0][param1][i];
            break;
        }
    }

    return v1;
}

static const int Unk_ov88_animIds[][3] = {
    { 0x0, 0x1, 0x2 },
    { 0x11, 0x12, 0x13 }
};

// something with setting positions and animations??
static void Trade_AnimatePartyPokemon(int slot, Sprite *sprite, int spriteId)
{
    VecFx32 position;

    GF_ASSERT(slot < 13);

    position.x = FX32_ONE * UnionTrade_SpritePositions[slot][0];
    position.y = FX32_ONE * UnionTrade_SpritePositions[slot][1];

    if (slot == 12) {
        Sprite_SetPosition(sprite, &position);
        Sprite_SetAnim(sprite, Unk_ov88_animIds[spriteId][2]);
    } else {
        Sprite_SetPosition(sprite, &position);

        if (slot < 6) {
            Sprite_SetAnim(sprite, Unk_ov88_animIds[spriteId][0]);
        } else {
            Sprite_SetAnim(sprite, Unk_ov88_animIds[spriteId][1]);
        }
    }
}

static int ov88_0223CFF4(u32 *param0, int *selectedSlot, Sprite *monSprite, Trade_PokemonData *tradePokemonData, int spriteId)
{
    int v0 = *param0 - 1;
    int tradeMonSlot = 0;
    int v2 = 0;

    if (spriteId == 0) {
        if (*param0) {
            tradeMonSlot = ov88_0223CF30(*selectedSlot, v0, tradePokemonData);
            Trade_AnimatePartyPokemon(tradeMonSlot, monSprite, spriteId);

            if (*selectedSlot != tradeMonSlot) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                *selectedSlot = tradeMonSlot;
                v2 = 1;
            }
        }

        *param0 = 0;
    } else {
        Trade_AnimatePartyPokemon(*selectedSlot, monSprite, spriteId);
    }

    return v2;
}

void Trade_SendByteData(int netId, int cmd, int data)
{
    u8 dataU8 = data;
    CommSys_SendData(cmd, &dataU8, 1);
}

void Trade_SendData(Trade *trade, int cmd, int data)
{
    if ((data != trade->lastSentData) || (cmd != trade->lastSentCmd)) {
        Trade_SendByteData(CommSys_CurNetId(), cmd, data);
        trade->lastSentData = data;
        trade->lastSentCmd = cmd;
    }
}

static void *Trade_TurnPartyIntoSendableData(Party *party, int param1)
{

    u32 partyData = (u32)party;

    return (void *)(partyData + param1 * (236 * 6 + 4 * 2));
}

void ov88_0223D098(int netId, Party *party, int param2)
{
    if (CommSys_IsPlayerConnected(netId)) {
        u8 v0 = param2;

        CommSys_SendDataHuge(22, Trade_TurnPartyIntoSendableData(party, param2), 236 * 6 + 4 * 2);
    }
}

static void UnionTrade_SendRibbonData(SaveData *saveData)
{
    u8 *ribbonData = GetRibbonData(saveData);
    int unused;

    CommSys_SendData(32, ribbonData, 14);
}

static void Trade_CreateNetworkObject(TrainerInfo *trainerInfo, PalPad *source, PalPad *destination)
{
    // this is the exact same as PalPad_CreateNetworkObject ?
    int i;

    CharCode_Copy(destination->trainerName, TrainerInfo_Name(trainerInfo));

    destination->trainerId = TrainerInfo_ID(trainerInfo);
    destination->regionCode = TrainerInfo_RegionCode(trainerInfo);
    destination->gameCode = TrainerInfo_GameCode(trainerInfo);
    destination->gender = TrainerInfo_Gender(trainerInfo);

    for (i = 0; i < 16; i++) {
        destination->associatedTrainerIds[i] = source[i].trainerId;
        destination->associatedTrainerGameCodes[i] = source[i].gameCode;
        destination->associatedTrainerRegionCodes[i] = source[i].regionCode;
        destination->associatedTrainerGenders[i] = source[i].gender;
    }

    CommSys_SendDataHuge(28, destination, sizeof(PalPad));
}

static void ov88_sendChatotCry(ChatotCry *cry)
{
    CommSys_SendDataHuge(29, cry, 1000);
}

static int ov88_0223D150(Trade *unionTrade)
{
    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_CONFIRM);
        unionTrade->selectedMonId[0] = 12;
        ov88_0223BE28(unionTrade);
        Trade_AnimatePartyPokemon(unionTrade->selectedMonId[0], unionTrade->sprites[0], 0);
    } else {
        ov88_0223CE34(&unionTrade->unk_14C[0]);

        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            if (unionTrade->unk_14C[0] == 0) {
                if (unionTrade->selectedMonId[0] == 12) {
                    unionTrade->nextFunction = ov88_0223D2C4;
                } else if (unionTrade->selectedMonId[0] < 6) {
                    unionTrade->nextFunction = UnionTrade_SelectPlayerMon;
                } else if ((unionTrade->selectedMonId[0] >= 6) && (unionTrade->selectedMonId[0] < 12)) {
                    unionTrade->nextFunction = Trade_SelectFriendsPokemon;
                }
            }
        }
    }

    return 0;
}

static const u8 Unk_ov88_visiblePages[] = {
    0x0,
    0x1,
    0x2,
    0x4,
    0x3,
    0x5,
    0x6,
    0x7,
    0x8
};

static void Trade_InitPokemonSummary(Trade *trade, int isChatot)
{
    if (isChatot == 0) {
        trade->pokemonSummary.monData = trade->playerParty;
        trade->pokemonSummary.monMax = Party_GetCurrentCount(trade->playerData->currentParty);

        trade->pokemonSummary.chatotCry = NULL;
        PokemonSummaryScreen_SetPlayerProfile(&trade->pokemonSummary, CommInfo_TrainerInfo(CommSys_CurNetId()));
    } else {
        trade->pokemonSummary.monData = trade->friendParty;
        trade->pokemonSummary.monMax = Party_GetCurrentCount(trade->friendParty);
        trade->pokemonSummary.chatotCry = (ChatotCry *)trade->chatotCry[CommSys_CurNetId() ^ 1];
        PokemonSummaryScreen_SetPlayerProfile(&trade->pokemonSummary, CommInfo_TrainerInfo(CommSys_CurNetId() ^ 1));
    }

    trade->pokemonSummary.dataType = SUMMARY_DATA_PARTY_MON;
    trade->pokemonSummary.monIndex = trade->selectedMonId[0] % 6;
    trade->pokemonSummary.mode = SUMMARY_MODE_LOCK_MOVES;
    trade->pokemonSummary.move = 0;
    trade->pokemonSummary.showContest = PokemonSummaryScreen_ShowContestData(trade->playerData->saveData);
    trade->pokemonSummary.dexMode = trade->playerData->dexMode;
    trade->pokemonSummary.options = trade->playerData->options;
    trade->pokemonSummary.specialRibbons = GetRibbonData(trade->playerData->saveData);

    PokemonSummaryScreen_FlagVisiblePages(&trade->pokemonSummary, Unk_ov88_visiblePages);

    trade->appMan = ApplicationManager_New(&gPokemonSummaryScreenApp, &trade->pokemonSummary, HEAP_ID_26);
    trade->isChatot = isChatot;
}

// cancel trade
static int ov88_0223D2C4(Trade *trade)
{
    Bg_FillTilemapRect(trade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_MAIN_MESSAGES], MSG_CANCEL_TRADE, FONT_MESSAGE, trade->tradeMessages, trade->tradeStrTemplate);

    trade->nextFunction = ov88_0223D318;

    return 0;
}

static int ov88_0223D318(Trade *unionTrade)
{
    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        // message is "Waiting for your friend to finish..."
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_WAIT_FOR_FRIEND, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        Trade_SendData(unionTrade, 24, 1);
        unionTrade->nextFunction = ov88_0223DA00;
        unionTrade->unk_5C = 0;
        break;
    case MENU_CANCELED:
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223D150;
        break;
    default:
        break;
    }

    return 0;
}

// finish trade?
static int ov88_0223D3E0(Trade *trade)
{
    Bg_FillTilemapRect(trade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_MAIN_MESSAGES], trade->unk_68, FONT_MESSAGE, trade->tradeMessages, trade->tradeStrTemplate);
    trade->nextFunction = ov88_0223D434;

    return 0;
}

static int ov88_0223D434(Trade *unionTrade)
{
    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223D150;
        ov88_0223DFF4(unionTrade);
    }

    return 0;
}

static void UnionTrade_DisplayMessageFromPalPadBank(Trade *unionTrade, int entryId)
{
    Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], entryId, FONT_MESSAGE, unionTrade->palPadMessages, unionTrade->nameTemplate);
}

static int ov88_0223D4C4(Trade *unionTrade)
{
    int v0;

    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        unionTrade->nextFunction = ov88_0223D854;
        break;
    case MENU_CANCELED:
        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_FRIEND_ROSTER_FULL_ASK_DELETE);
        unionTrade->nextFunction = Trade_AskToDeleteFriendFromFullRoster;
        break;
    default:
        break;
    }

    return 0;
}

static int ov88_0223D514(Trade *unionTrade)
{
    TrainerInfo *friendInfo;
    int unused;

    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        sub_02030788(SaveData_GetBattleFrontier(unionTrade->saveData), unionTrade->friendRosterSlot);
        sub_0202AFD4(unionTrade->wifiList, unionTrade->friendRosterSlot);
        AddFriendToPalPad(unionTrade->saveData, unionTrade->friendNetId, 32 - 1, HEAP_ID_26, 0);
        unionTrade->nextFunction = ov88_0223D854;
        break;
    case MENU_CANCELED:
        friendInfo = CommInfo_TrainerInfo(unionTrade->friendNetId);
        StringTemplate_SetPlayerName(unionTrade->nameTemplate, 0, friendInfo);
        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_FRIEND_GIVE_UP_REGISTERING);
        unionTrade->nextFunction = ov88_0223D4C4;
        break;
    default:
        break;
    }

    return 0;
}

static int UnionTrade_AskReplaceFriendInFullRoster(Trade *unionTrade)
{
    int friendSlotChosen;
    TrainerInfo *friendInfo;

    friendSlotChosen = ListMenu_ProcessInput(unionTrade->friendRosterMenu);

    switch (friendSlotChosen) {
    case LIST_NOTHING_CHOSEN:
        return 0;
    case LIST_CANCEL:
        Sound_PlayEffect(SEQ_SE_CONFIRM);
        friendInfo = CommInfo_TrainerInfo(unionTrade->friendNetId);
        StringTemplate_SetPlayerName(unionTrade->nameTemplate, 0, friendInfo);
        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_FRIEND_GIVE_UP_REGISTERING);
        unionTrade->nextFunction = ov88_0223D4C4;
        break;
    default:
        Sound_PlayEffect(SEQ_SE_CONFIRM);
        unionTrade->friendRosterSlot = friendSlotChosen;

        TrainerInfo *trainerInfo = TrainerInfo_New(HEAP_ID_26);

        TrainerInfo_SetName(trainerInfo, GetFriendTrainerName(unionTrade->wifiList, friendSlotChosen));
        StringTemplate_SetPlayerName(unionTrade->nameTemplate, 0, trainerInfo);
        Heap_Free(trainerInfo);

        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_DELETE_FRIEND_FROM_ROSTER);
        unionTrade->nextFunction = ov88_0223D514;
        break;
    }

    Window_EraseStandardFrame(&unionTrade->friendRosterWindow, 0);
    Window_Remove(&unionTrade->friendRosterWindow);
    ListMenu_Free(unionTrade->friendRosterMenu, NULL, NULL);
    StringList_Free(unionTrade->friendList);

    return 0;
}

static int Trade_ShowFriendRosterMenuForReplacement(Trade *unionTrade)
{
    ListMenuTemplate mTemplate;
    int validFriendCount = GetTotalValidFriendDataCount(unionTrade->wifiList);
    int notUsed = 5; // left over from max display for menu.

    unionTrade->friendList = StringList_New(validFriendCount + 1, HEAP_ID_26);

    {
        MessageLoader *unused;
        Strbuf *friendName = Strbuf_Init(100, HEAP_ID_26);
        int i = 0;

        for (i = 0; i < 32; i++) {
            if (wifiSlotHasValidFriendData(unionTrade->wifiList, i)) {
                Strbuf_CopyChars(friendName, GetFriendTrainerName(unionTrade->wifiList, i));
                StringList_AddFromStrbuf(unionTrade->friendList, friendName, i);
            }
        }

        StringList_AddFromMessageBank(unionTrade->friendList, unionTrade->palPadMessages, MSG_PAL_CANCEL, MENU_CANCELED);
        Strbuf_Free(friendName);
    }

    unionTrade->friendRosterMenu = Trade_SetupFriendRosterMenu(unionTrade->friendList, validFriendCount, &unionTrade->friendRosterWindow, unionTrade->bgConfig);
    unionTrade->nextFunction = UnionTrade_AskReplaceFriendInFullRoster;

    return 0;
}

static int Trade_AskToDeleteFriendFromFullRoster(Trade *unionTrade)
{
    TrainerInfo *friendInfo;
    int unused;

    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        unionTrade->nextFunction = Trade_ShowFriendRosterMenuForReplacement;
        break;
    case MENU_CANCELED:
        friendInfo = CommInfo_TrainerInfo(unionTrade->friendNetId);
        StringTemplate_SetPlayerName(unionTrade->nameTemplate, 0, friendInfo);
        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_FRIEND_GIVE_UP_REGISTERING);
        unionTrade->nextFunction = ov88_0223D4C4;
        break;
    default:
        break;
    }

    return 0;
}

static int ov88_AskToRegisterFriendInPalPad(Trade *unionTrade)
{
    int slot;

    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        unionTrade->nextFunction = ov88_0223D854;

        for (slot = 0; slot < 32; slot++) {
            if (!wifiSlotHasValidFriendData(unionTrade->wifiList, slot)) {
                AddFriendToPalPad(unionTrade->saveData, unionTrade->friendNetId, slot, HEAP_ID_26, 0);
                break;
            }
        }

        if (slot == 32) {
            UnionTrade_DisplayMessageFromPalPadBank(unionTrade, MSG_PAL_FRIEND_ROSTER_FULL_ASK_DELETE);
            unionTrade->nextFunction = Trade_AskToDeleteFriendFromFullRoster;
            return 0;
        }

        break;
    case MENU_CANCELED:
        unionTrade->nextFunction = ov88_0223D854;
        break;
    default:
        break;
    }

    return 0;
}

static int ov88_0223D840(Trade *unionTrade)
{
    if (CommTiming_IsSyncState(19)) {
        return 2;
    }

    return 0;
}

static int ov88_0223D854(Trade *unionTrade)
{
    int i;
    TrainerInfo *friendInfo;

    unionTrade->friendNetId = -1;

    for (i = 0; i < CommSys_ConnectedCount(); i++) {
        if (unionTrade->unk_3644[i] == 2) {
            unionTrade->friendNetId = i;
            unionTrade->unk_3644[i] = 0;
            break;
        }
    }

    if (unionTrade->friendNetId == -1) {
        MessageLoader_Free(unionTrade->palPadMessages);
        StringTemplate_Free(unionTrade->nameTemplate);
        CommTiming_StartSync(19);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_WAIT_FOR_FRIEND, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223D840;
        return 0;
    }

    if (Bag_CanRemoveItem(SaveData_GetBag(unionTrade->saveData), ITEM_PAL_PAD, 1, HEAP_ID_26) == TRUE) {
        friendInfo = CommInfo_TrainerInfo(unionTrade->friendNetId);
        StringTemplate_SetPlayerName(unionTrade->nameTemplate, 0, friendInfo);
        UnionTrade_DisplayMessageFromPalPadBank(unionTrade, 57);
        unionTrade->nextFunction = ov88_AskToRegisterFriendInPalPad;
        return 0;
    }

    {
        WiFiList *wifiList = SaveData_GetWiFiList(unionTrade->saveData);

        for (i = 0; i < 32; i++) {
            if (!wifiSlotHasValidFriendData(wifiList, i)) {
                AddFriendToPalPad(unionTrade->saveData, unionTrade->friendNetId, i, HEAP_ID_26, 0);
                break;
            }
        }
    }

    unionTrade->nextFunction = ov88_0223D854;
    return 0;
}

static int ov88_0223D96C(Trade *unionTrade)
{
    if (0 == sub_020391DC(unionTrade->saveData, unionTrade->unk_3644, HEAP_ID_26)) {
        CommTiming_StartSync(19);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_WAIT_FOR_FRIEND, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223D840;
        return 0;
    }

    unionTrade->nameTemplate = StringTemplate_Default(HEAP_ID_26);
    unionTrade->palPadMessages = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0675, HEAP_ID_26);
    unionTrade->wifiList = SaveData_GetWiFiList(unionTrade->saveData);
    unionTrade->nextFunction = ov88_0223D854;

    return 0;
}

static int ov88_0223DA00(Trade *unionTrade)
{
    if ((unionTrade->unk_60[0] != 0) && (unionTrade->unk_60[1] != 0)) {
        if ((unionTrade->unk_60[0] == 1) && (unionTrade->unk_60[1] == 1)) {
            unionTrade->nextFunction = ov88_0223D96C;
        } else {
            unionTrade->nextFunction = ov88_0223D3E0;
        }

        unionTrade->unk_60[0] = 0;
        unionTrade->unk_60[1] = 0;
        unionTrade->unk_68 = 29;
    }

    return 0;
}

static int UnionTrade_SelectPlayerMon(Trade *unionTrade)
{
    MenuTemplate menuTemplate;

    menuTemplate.fontID = FONT_SYSTEM;
    menuTemplate.xSize = 1;
    menuTemplate.ySize = 3;
    menuTemplate.lineSpacing = 0;
    menuTemplate.suppressCursor = FALSE;
    menuTemplate.loopAround = FALSE;

    StringTemplate_SetNickname(unionTrade->nicknameTemplate, 0, Pokemon_GetBoxPokemon(Party_GetPokemonBySlotIndex(unionTrade->playerParty, unionTrade->selectedMonId[0])));
    Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&unionTrade->windows[22], MSG_MON_SELECTED, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->nicknameTemplate);

    unionTrade->options = StringList_New(3, HEAP_ID_26);

    StringList_AddFromMessageBank(unionTrade->options, unionTrade->tradeMessages, MSG_MON_SELECT_SUMMARY, 0);
    StringList_AddFromMessageBank(unionTrade->options, unionTrade->tradeMessages, MSG_MON_SELECT_TRADE, 1);
    StringList_AddFromMessageBank(unionTrade->options, unionTrade->tradeMessages, MSG_MON_SELECT_CANCEL, 2);

    menuTemplate.choices = unionTrade->options;
    menuTemplate.window = &unionTrade->windows[24];

    Trade_DrawWindowFrame(&unionTrade->windows[24]);

    unionTrade->pokemonActionMenu = Menu_NewAndCopyToVRAM(&menuTemplate, 8, 0, 0, 26, PAD_BUTTON_B);
    unionTrade->nextFunction = ov88_0223DB48;

    return 0;
}

static int ov88_0223DB48(Trade *unionTrade)
{
    switch (Menu_ProcessInput(unionTrade->pokemonActionMenu)) {
    case 0: // Summary
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        Menu_Free(unionTrade->pokemonActionMenu, NULL);
        StringList_Free(unionTrade->options);
        unionTrade->nextFunction = ov88_0223D150;
        return 3;
        break;
    case 1: // Trade
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_COMMUNICATING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        Menu_Free(unionTrade->pokemonActionMenu, NULL);
        StringList_Free(unionTrade->options);
        unionTrade->nextFunction = Trade_SelectMonForTrade;
        break;
    case 2: // Cancel
    case MENU_CANCELED:
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        Menu_Free(unionTrade->pokemonActionMenu, NULL);
        StringList_Free(unionTrade->options);
        unionTrade->nextFunction = ov88_0223D150;
        break;
    }

    return 0;
}

static int Trade_SelectMonForTrade(Trade *unionTrade)
{
    Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_COMMUNICATING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
    Trade_SendData(unionTrade, 24, 2);

    unionTrade->nextFunction = ov88_0223DCE0;

    return 0;
}

static int ov88_0223DCE0(Trade *unionTrade)
{
    if ((unionTrade->unk_60[0] != 0) && (unionTrade->unk_60[1] != 0)) {
        if ((unionTrade->unk_60[0] == 2) && (unionTrade->unk_60[1] == 2)) {
            unionTrade->nextFunction = ov88_0223DD1C;
        } else {
            unionTrade->nextFunction = ov88_0223D3E0;
        }

        unionTrade->unk_68 = 24;
        unionTrade->unk_60[0] = 0;
        unionTrade->unk_60[1] = 0;
    }

    return 0;
}

static int ov88_0223DD1C(Trade *unionTrade)
{
    int i;

    for (i = 0; i < 6; i++) {
        if (i != unionTrade->selectedMonId[0]) {
            Sprite_SetDrawFlag(unionTrade->partySprites[i], FALSE);

            if (unionTrade->tradePokemonData[i].holdsMail) {
                Sprite_SetDrawFlag(unionTrade->heldMailSprites[i], FALSE);
            }

            if (unionTrade->tradePokemonData[i].hasBallCapsule) {
                Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[i], FALSE);
            }
        }

        Window_ClearAndScheduleCopyToVRAM(&unionTrade->windows[7 + i]);

        if (i != (unionTrade->selectedMonId[1] - 6)) {
            Sprite_SetDrawFlag(unionTrade->partySprites[i + 6], FALSE);

            if (unionTrade->tradePokemonData[i + 6].holdsMail) {
                Sprite_SetDrawFlag(unionTrade->heldMailSprites[i + 6], FALSE);
            }

            if (unionTrade->tradePokemonData[i + 6].hasBallCapsule) {
                Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[i + 6], FALSE);
            }
        }

        Window_ClearAndScheduleCopyToVRAM(&unionTrade->windows[13 + i]);
    }

    Sprite_SetDrawFlag(unionTrade->sprites[0], FALSE);
    Sprite_SetDrawFlag(unionTrade->sprites[1], FALSE);

    ov88_0223DE68(unionTrade->unk_231C, UnionTrade_SpritePositions[unionTrade->selectedMonId[0]][0] + 16, UnionTrade_SpritePositions[unionTrade->selectedMonId[0]][1] + -6, 6 * 8, 6 * 8);
    ov88_0223DE68(unionTrade->unk_2334, UnionTrade_SpritePositions[unionTrade->selectedMonId[1]][0] + 16, UnionTrade_SpritePositions[unionTrade->selectedMonId[1]][1] + -6, 22 * 8, 6 * 8);

    unionTrade->unk_2314 = 0;
    unionTrade->nextFunction = ov88_0223DF00;

    return 0;
}

static void ov88_0223DE68(VecFx32 param0[], int x0Offset, int y0Offset, int x1Offset, int y1Offset)
{
    param0[0].x = FX32_ONE * x0Offset;
    param0[0].y = FX32_ONE * y0Offset;
    param0[1].x = FX32_ONE * x1Offset;
    param0[1].y = FX32_ONE * y1Offset;
}

static void ov88_0223DE7C(Sprite *pokemonSprite, Sprite *mailSprite, Sprite *capsuleSprite, int param3, VecFx32 offsets[], Trade_PokemonData *tradePokemonData)
{
    VecFx32 pos, mailPos, capsulePos;

    pos.x = offsets[0].x + ((offsets[1].x - offsets[0].x) / 20) * param3;
    pos.y = offsets[0].y + ((offsets[1].y - offsets[0].y) / 20) * param3;

    Sprite_SetPosition(pokemonSprite, &pos);

    if (tradePokemonData->holdsMail) {
        mailPos.x = pos.x + 20 * FX32_ONE;
        mailPos.y = pos.y + (16 + 6) * FX32_ONE;
        Sprite_SetPosition(mailSprite, &mailPos);
    }

    if (tradePokemonData->hasBallCapsule) {
        capsulePos.x = pos.x + (20 + 8) * FX32_ONE;
        capsulePos.y = pos.y + (16 + 6) * FX32_ONE;
        Sprite_SetPosition(capsuleSprite, &capsulePos);
    }
}

static int ov88_0223DF00(Trade *unionTrade)
{
    unionTrade->unk_2314++;

    ov88_0223DE7C(unionTrade->partySprites[unionTrade->selectedMonId[0]], unionTrade->heldMailSprites[unionTrade->selectedMonId[0]], unionTrade->ballCapsuleSprites[unionTrade->selectedMonId[0]], unionTrade->unk_2314, unionTrade->unk_231C, &unionTrade->tradePokemonData[unionTrade->selectedMonId[0]]);
    ov88_0223DE7C(unionTrade->partySprites[unionTrade->selectedMonId[1]], unionTrade->heldMailSprites[unionTrade->selectedMonId[1]], unionTrade->ballCapsuleSprites[unionTrade->selectedMonId[1]], unionTrade->unk_2314, unionTrade->unk_2334, &unionTrade->tradePokemonData[unionTrade->selectedMonId[1]]);

    if (unionTrade->unk_2314 == 20 + 1) {
        ov88_0223C860(&unionTrade->windows[19], unionTrade->playerParty, unionTrade->selectedMonId[0], 8, 1);
        ov88_0223C860(&unionTrade->windows[20], unionTrade->friendParty, unionTrade->selectedMonId[1] - 6, 8, 1);
        ov88_0223BDA4(unionTrade, unionTrade->selectedMonId[1]);
        unionTrade->nextFunction = ov88_ConfirmTradeMessage;
        Sprite_SetDrawFlag(unionTrade->unk_47C, TRUE);
    }

    return 0;
}

static void ov88_0223DFF4(Trade *unionTrade)
{
    int i;
    VecFx32 v1;

    Window_ClearAndScheduleCopyToVRAM(&unionTrade->windows[19]);
    Window_ClearAndScheduleCopyToVRAM(&unionTrade->windows[20]);

    for (i = 0; i < 12; i++) {
        if (unionTrade->tradePokemonData[i].species != 0) {
            Trade_SetSpritePosition(unionTrade->partySprites[i], UnionTrade_SpritePositions[i][0] + 16, UnionTrade_SpritePositions[i][1] + -6);
            Sprite_SetDrawFlag(unionTrade->partySprites[i], TRUE);

            if (unionTrade->tradePokemonData[i].holdsMail) {
                Trade_SetSpritePosition(unionTrade->heldMailSprites[i], UnionTrade_SpritePositions[i][0] + (16 + 20), UnionTrade_SpritePositions[i][1] + 16);
                Sprite_SetDrawFlag(unionTrade->heldMailSprites[i], TRUE);
            }

            if (unionTrade->tradePokemonData[i].hasBallCapsule) {
                Trade_SetSpritePosition(unionTrade->ballCapsuleSprites[i], UnionTrade_SpritePositions[i][0] + (16 + 20 + 8), UnionTrade_SpritePositions[i][1] + 16);
                Sprite_SetDrawFlag(unionTrade->ballCapsuleSprites[i], TRUE);
            }

            Window_ScheduleCopyToVRAM(&unionTrade->windows[7 + i]);
        }
    }

    Sprite_SetDrawFlag(unionTrade->sprites[0], TRUE);
    Sprite_SetDrawFlag(unionTrade->sprites[1], TRUE);
    ov88_0223CB34(unionTrade->windows, 1, unionTrade);
    Sprite_SetDrawFlag(unionTrade->pokemonBattleSprites[3], FALSE);
    Sprite_SetDrawFlag(unionTrade->unk_47C, FALSE);
}

static int ov88_ConfirmTradeMessage(Trade *unionTrade)
{
    Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    StringTemplate_SetNickname(unionTrade->nicknameTemplate, 0, Pokemon_GetBoxPokemon(Party_GetPokemonBySlotIndex(unionTrade->playerParty, unionTrade->selectedMonId[0])));
    StringTemplate_SetNickname(unionTrade->nicknameTemplate, 1, Pokemon_GetBoxPokemon(Party_GetPokemonBySlotIndex(unionTrade->friendParty, unionTrade->selectedMonId[1] - 6)));

    //"Trade [PokemonA] in return for [PokemonB]?"
    Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_CONFIRM_TRADE, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->nicknameTemplate);
    unionTrade->nextFunction = ov88_0223E20C;

    return 0;
}

static void ov88_0223E1AC(Trade *unionTrade)
{
    Trade_SendData(unionTrade, 24, 3);
    unionTrade->unk_5C = 1;
}

static void Trade_DisplayTradeMessage(Trade *unionTrade, int windowId, int messageId)
{
    Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&unionTrade->windows[windowId], messageId, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
}

static int ov88_0223E20C(Trade *unionTrade)
{
    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        if (Trade_PlayerHasNonEggMonsRemaining(unionTrade)) {
            switch (Trade_CheckForInvalidMons(unionTrade)) {
            case 0:
                if (unionTrade->tradePokemonData[unionTrade->selectedMonId[0]].hasBallCapsule == 0) {
                    ov88_0223E1AC(unionTrade);
                    Trade_DisplayTradeMessage(unionTrade, 23, MSG_COMMUNICATING);
                    unionTrade->nextFunction = ov88_0223E41C;
                } else {
                    unionTrade->nextFunction = ov88_WarnAboutBallCapsuleRemoval;
                }

                break;
            case 1:
                Trade_DisplayTradeMessage(unionTrade, 23, MSG_PLAYER_NONTRADABLE);
                unionTrade->nextFunction = ov88_0223E41C;
                Trade_SendData(unionTrade, 24, 4);
                break;
            case 2:
                Trade_DisplayTradeMessage(unionTrade, 23, MSG_FRIEND_NONTRADABLE);
                unionTrade->nextFunction = ov88_0223E41C;
                Trade_SendData(unionTrade, 24, 4);
                break;
            }
        } else {
            unionTrade->nextFunction = ov88_0223E41C;
            Trade_SendData(unionTrade, 24, 4);
        }

        break;
    case MENU_CANCELED:
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_COMMUNICATING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223E41C;
        Trade_SendData(unionTrade, 24, 4);
        break;
    default:
        break;
    }

    return 0;
}

static int ov88_WarnAboutBallCapsuleRemoval(Trade *unionTrade)
{
    Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_BALLCAPSULE_WARNING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->nicknameTemplate);
    unionTrade->nextFunction = ov88_HandleBallCapsuleRemovalMenu;
    return 0;
}

static int ov88_HandleBallCapsuleRemovalMenu(Trade *unionTrade)
{
    switch (Trade_HandleMenu(unionTrade->bgConfig, &unionTrade->unk_6BC, &unionTrade->unk_6C8)) {
    case 0:
        ov88_0223E1AC(unionTrade);
        Trade_DisplayTradeMessage(unionTrade, 23, MSG_COMMUNICATING);
        unionTrade->nextFunction = ov88_0223E41C;
        break;
    case 0xfffffffe:
        Bg_FillTilemapRect(unionTrade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&unionTrade->windows[WINDOW_MAIN_MESSAGES], MSG_COMMUNICATING, FONT_MESSAGE, unionTrade->tradeMessages, unionTrade->tradeStrTemplate);
        unionTrade->nextFunction = ov88_0223E41C;
        Trade_SendData(unionTrade, 24, 4);
        break;
    default:
        break;
    }

    return 0;
}

static int ov88_0223E41C(Trade *unionTrade)
{
    if ((unionTrade->unk_60[0] != 0) && (unionTrade->unk_60[1] != 0)) {
        if ((unionTrade->unk_60[0] == 3) && (unionTrade->unk_60[1] == 3)) {
            unionTrade->unk_36F0++;
            unionTrade->nextFunction = ov88_0223E478;
        } else {
            unionTrade->nextFunction = ov88_0223D3E0;
        }

        unionTrade->unk_60[0] = 0;
        unionTrade->unk_60[1] = 0;

        if (Trade_PlayerHasNonEggMonsRemaining(unionTrade)) {
            unionTrade->unk_68 = 24;
        } else {
            unionTrade->unk_68 = 34;
        }
    }

    return 0;
}

static int ov88_0223E478(Trade *unionTrade)
{ // finish trade?
    CommInfo_SetTradeResult(unionTrade->saveData, 1);
    Trade_TradePokemon(unionTrade->playerParty, unionTrade->friendParty, unionTrade->selectedMonId[0], unionTrade->selectedMonId[1] - 6, unionTrade->playerData);
    unionTrade->nextFunction = ov88_0223D3E0;
    return 2;
}

static int Trade_SelectFriendsPokemon(Trade *trade)
{
    MenuTemplate menuTemplate;

    menuTemplate.fontID = FONT_SYSTEM;
    menuTemplate.xSize = 1;
    menuTemplate.ySize = 2;
    menuTemplate.lineSpacing = 0;
    menuTemplate.suppressCursor = FALSE;
    menuTemplate.loopAround = FALSE;

    StringTemplate_SetNickname(trade->nicknameTemplate, 0, Pokemon_GetBoxPokemon(Party_GetPokemonBySlotIndex(trade->friendParty, trade->selectedMonId[0] - 6)));
    Bg_FillTilemapRect(trade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
    Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_SELECTED_MON], MSG_MON_SELECTED, FONT_MESSAGE, trade->tradeMessages, trade->nicknameTemplate);

    trade->options = StringList_New(2, HEAP_ID_26);

    StringList_AddFromMessageBank(trade->options, trade->tradeMessages, MSG_MON_SELECT_SUMMARY, 0);
    StringList_AddFromMessageBank(trade->options, trade->tradeMessages, MSG_MON_SELECT_CANCEL, 1);

    menuTemplate.choices = trade->options;
    menuTemplate.window = &trade->windows[WINDOW_SELECT_MON_CHOICES];

    Trade_DrawWindowFrame(&trade->windows[WINDOW_SELECT_MON_CHOICES]);

    trade->pokemonActionMenu = Menu_NewAndCopyToVRAM(&menuTemplate, 8, 0, 0, 26, PAD_BUTTON_B);
    trade->nextFunction = Trade_HandleSelectingFriendsMon;

    return 0;
}

static int Trade_HandleSelectingFriendsMon(Trade *trade) // lord, i need to find a better name for this.
{
    switch (Menu_ProcessInput(trade->pokemonActionMenu)) {
    case 0:
        Bg_FillTilemapRect(trade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, trade->tradeMessages, trade->tradeStrTemplate);
        trade->nextFunction = ov88_0223D150;
        Menu_Free(trade->pokemonActionMenu, NULL);
        StringList_Free(trade->options);
        return 3;
        break;

    case 1:
    case MENU_CANCELED:
        Bg_FillTilemapRect(trade->bgConfig, 0, 0, 0, 0, 32, 24, 0);
        Trade_DisplayMessageFromEntry(&trade->windows[WINDOW_CHOOSE_MON], MSG_CHOOSE_MON, FONT_MESSAGE, trade->tradeMessages, trade->tradeStrTemplate);
        Menu_Free(trade->pokemonActionMenu, NULL);
        StringList_Free(trade->options);
        trade->nextFunction = ov88_0223D150;
        break;
    }

    return 0;
}

static void Trade_TradePokemon(Party *playerParty, Party *friendParty, int playerSelectedSlot, int friendSelectedSlot, UnkStruct_ov88_playerData *pData)
{
    Pokemon *sentMon, *receivedMon;

    sentMon = Pokemon_New(HEAP_ID_26);
    receivedMon = Pokemon_New(HEAP_ID_26);

    Pokemon_Copy(Party_GetPokemonBySlotIndex(playerParty, playerSelectedSlot), sentMon);
    Pokemon_Copy(Party_GetPokemonBySlotIndex(friendParty, friendSelectedSlot), receivedMon);

    if (Pokemon_GetValue(receivedMon, MON_DATA_SPECIES, NULL) == SPECIES_ARCEUS) {
        if (Pokemon_GetValue(receivedMon, MON_DATA_FATEFUL_ENCOUNTER, NULL) || ((Pokemon_GetValue(receivedMon, MON_DATA_MET_LOCATION, NULL) == 86) && (Pokemon_GetValue(receivedMon, MON_DATA_FATEFUL_ENCOUNTER, NULL) == 0))) {
            VarsFlags *saveFlags = SaveData_GetVarsFlags(pData->saveData);

            if (SystemVars_GetArceusEventState(saveFlags) == 0) {
                SystemVars_SetArceusEventState(saveFlags, 1);
            }
        }
    }

    Pokemon_SetValue(receivedMon, MON_DATA_GENDER, NULL);

    if (Pokemon_GetValue(receivedMon, MON_DATA_IS_EGG, NULL) == 0) {
        u8 friendship = 70;
        Pokemon_SetValue(receivedMon, MON_DATA_FRIENDSHIP, &friendship);
    }

    UpdateMonStatusAndTrainerInfo(receivedMon, CommInfo_TrainerInfo(CommSys_CurNetId()), 5, 0, HEAP_ID_FIELD2);
    Pokemon_ClearBallCapsuleData(receivedMon);
    Pokemon_Copy(sentMon, pData->sentPokemon);
    Pokemon_Copy(receivedMon, pData->receivedPokemon);
    TrainerInfo_Copy(CommInfo_TrainerInfo(CommSys_CurNetId() ^ 1), pData->friendTrainerInfo);

    pData->playerSelectedSlot = playerSelectedSlot;

    if (Party_HasSpecies(playerParty, SPECIES_CHATOT) == 0) {
        ChatotCry *cry = SaveData_GetChatotCry(pData->saveData);
        ResetChatotCryDataStatus(cry);
    }

    SaveData_UpdateCatchRecords(pData->saveData, receivedMon);
    Pokemon_Copy(receivedMon, Party_GetPokemonBySlotIndex(playerParty, playerSelectedSlot));
    Pokemon_Copy(sentMon, Party_GetPokemonBySlotIndex(friendParty, friendSelectedSlot));
    Trade_WriteTradeJournalEntry(pData->journalEntry, receivedMon);
    GameRecords_IncrementRecordValue(pData->records, RECORD_LOCAL_LINK_TRADES);
    Heap_Free(sentMon);
    Heap_Free(receivedMon);
}

static void Trade_WriteTradeJournalEntry(JournalEntry *journalEntry, Pokemon *mon)
{
    void *journalEntryOnlineEvent;
    TrainerInfo *friendInfo = CommInfo_TrainerInfo(CommSys_CurNetId() ^ 1);
    u16 nickname[MON_NAME_LEN + 1];

    Pokemon_GetValue(mon, MON_DATA_NICKNAME, nickname);
    journalEntryOnlineEvent = JournalEntry_CreateEventGotPokemonFromTrade((u16 *)TrainerInfo_Name(friendInfo), TrainerInfo_Gender(friendInfo), nickname, Pokemon_GetGender(mon), 26);
    JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
}

static void ov88_0223E848(Trade *unionTrade)
{
    unionTrade->unk_2310 += 2;
    Bg_SetOffset(unionTrade->bgConfig, BG_LAYER_SUB_2, 0, unionTrade->unk_2310);
    Bg_SetOffset(unionTrade->bgConfig, BG_LAYER_MAIN_3, 0, unionTrade->unk_2310);
}

static void Trade_SetSpritePosition(Sprite *sprite, int unk_xMult, int unk_yMult)
{
    VecFx32 pos;

    pos.x = FX32_ONE * unk_xMult;
    pos.y = FX32_ONE * unk_yMult;

    Sprite_SetPosition(sprite, &pos);
}

static void Trade_AddWaitDial(Trade *trade)
{
    trade->waitingWindow = Window_AddWaitDial(&trade->windows[WINDOW_MAIN_MESSAGES], 512 - (9 + (18 + 12)));
}

static void Trade_RemoveWaitDial(Trade *trade)
{
    if (trade->waitingWindow != NULL) {
        DestroyWaitDial(trade->waitingWindow);
        trade->waitingWindow = NULL;
    }
}

static int Trade_PlayerHasNonEggMonsRemaining(Trade *trade)
{
    int i;
    int eggCount = 0;
    int playerPartyCount = Party_GetCurrentCount(trade->playerParty);

    for (i = 0; i < playerPartyCount; i++) {
        if (i != trade->selectedMonId[0]) {
            eggCount += trade->tradePokemonData[i].isEgg;
        }
    }

    if (eggCount == (playerPartyCount - 1)) {
        return 0;
    }

    return 1;
}

static int Trade_CheckForInvalidMons(Trade *trade)
{
    int i, partyCount;
    Pokemon *mon;

    partyCount = Party_GetCurrentCount(trade->playerParty);

    for (i = 0; i < partyCount; i++) {
        mon = Party_GetPokemonBySlotIndex(trade->playerParty, i);

        if (Pokemon_GetValue(mon, MON_DATA_CHECKSUM_FAILED, NULL)) {
            return 1;
        }
    }

    partyCount = Party_GetCurrentCount(trade->friendParty);

    for (i = 0; i < partyCount; i++) {
        mon = Party_GetPokemonBySlotIndex(trade->friendParty, i);

        if (Pokemon_GetValue(mon, MON_DATA_CHECKSUM_FAILED, NULL)) {
            return 2;
        }
    }

    return 0;
}

static void ov88_0223E984(Trade *unionTrade)
{
    unionTrade->unk_3704 = 1;
    unionTrade->unk_3708 = 0;
}

static void ov88_0223E998(Trade *unionTrade)
{
    if (unionTrade->unk_3704) {
        unionTrade->unk_3708++;

        if (unionTrade->unk_3708 > (30 * 60)) {
            Link_SetErrorState(4);
        }
    }
}
