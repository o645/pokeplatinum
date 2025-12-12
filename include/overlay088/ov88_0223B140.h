#ifndef POKEPLATINUM_OV88_0223B140_H
#define POKEPLATINUM_OV88_0223B140_H

#include "struct_decls/struct_02095E80_decl.h"

#include "overlay_manager.h"
#include "party.h"

// trade steps
#define TRADE_START           0
#define TRADE_SEND_CHATOT_CRY 14

// windows
#define WINDOW_CHOOSE_MON         21
#define WINDOW_SELECTED_MON       22
#define WINDOW_MAIN_MESSAGES      23
#define WINDOW_SELECT_MON_CHOICES 25

// messages from unk_0354.json. trade related.
#define MSG_CANCEL              0
#define MSG_CHOOSE_MON          15
#define MSG_MON_SELECTED        16
#define MSG_MON_SELECT_SUMMARY  17
#define MSG_MON_SELECT_TRADE    18
#define MSG_MON_SELECT_CANCEL   19
#define MSG_COMMUNICATING       20
#define MSG_CONFIRM_TRADE       21
#define MSG_CONFIRM_TRADE_YES   22
#define MSG_CONFIRM_TRADE_NO    23
#define MSG_TRADE_CANCELLED     24
#define MSG_CANCEL_TRADE        25
#define MSG_CANCEL_TRADE_YES    26
#define MSG_CANCEL_TRADE_NO     27
#define MSG_WAIT_FOR_FRIEND     28
#define MSG_FRIEND_WANTS_TRADE  29
#define MSG_PLAYER_SENT_MON     30
#define MSG_CARE_SENT           31
#define MSG_FRIEND_SENT_MON     32
#define MSG_CARE_RECEIVED       33
#define MSG_ONLY_POKEMON        34
#define MSG_GARBAGE             35
#define MSG_BALLCAPSULE_WARNING 36
#define MSG_PLAYER_NONTRADABLE  37
#define MSG_FRIEND_NONTRADABLE  38
#define MSG_MALE                39
#define MSG_FEMALE              40
#define MSG_LV                  41
#define MSG_ITEM                42
#define MSG_NONE                49
#define MSG_QUIT                50

// messages from unk_0675, palpad related.
#define MSG_PAL_CANCEL                        11
#define MSG_PAL_FRIEND_ROSTER_FULL_ASK_DELETE 58
#define MSG_PAL_FRIEND_GIVE_UP_REGISTERING    59
#define MSG_PAL_DELETE_FRIEND_FROM_ROSTER     60

int ov88_0223B140(ApplicationManager *appMan, int *param1);
int ov88_0223B57C(ApplicationManager *appMan, int *step);
int ov88_0223C03C(ApplicationManager *appMan, int *unused);
void Trade_Sendu8Data(int netId, int cmd, int data);
void ov88_0223D058(Trade *unionTrade, int cmd, int data);
void ov88_0223D098(int netId, Party *party, int param2);

#endif // POKEPLATINUM_OV88_0223B140_H
