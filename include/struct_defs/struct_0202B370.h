#ifndef POKEPLATINUM_STRUCT_0202B370_H
#define POKEPLATINUM_STRUCT_0202B370_H

#include <dwc.h>

#include "struct_defs/struct_0202B370_sub1.h"

typedef struct WiFiList_t {
    DWCUserData userData;
    DWCFriendData friendData[32];
    UnkStruct_0202B370_sub1 unk_1C0[32];
} WiFiList;

#endif // POKEPLATINUM_STRUCT_0202B370_H
