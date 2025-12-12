#ifndef POKEPLATINUM_STRUCT_OV88_0223C370_H
#define POKEPLATINUM_STRUCT_OV88_0223C370_H

#include "struct_decls/pokedexdata_decl.h"
#include "struct_defs/wi_fi_history.h"

#include "field/field_system_decl.h"

#include "game_options.h"
#include "game_records.h"
#include "journal.h"
#include "pal_pad.h"
#include "party.h"
#include "pokemon.h"
#include "savedata.h"
#include "trainer_info.h"

typedef struct {
    FieldSystem *fieldSystem;
    TrainerInfo *trainerInfo;
    Party *currentParty;
    PalPad *palPad;
    SaveData *saveData;
    WiFiHistory *wiFiHistory;
    Options *options;
    JournalEntry *journalEntry;
    GameRecords *records;
    Pokedex *pokedex;
    int unk_28;
    int playerSelectedSlot;
    int dexMode;
    int unk_34;
    TrainerInfo *friendTrainerInfo;
    Pokemon *sentPokemon;
    Pokemon *receivedPokemon;
} UnkStruct_ov88_playerData;

#endif // POKEPLATINUM_STRUCT_OV88_0223C370_H
