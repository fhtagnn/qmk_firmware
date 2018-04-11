/* © 2017 Wolf Belschner - dassuan@bitmessage.ch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kissboard.h"
#include "keymap.h"
#include "keymap_german.h"
#include "action_layer.h"

#define KC_SS KC_MINS      // necessary in macros
#define KC_AE KC_QUOT
#define KC_UE KC_LBRC
#define KC_OE KC_SCLN

#define _______ KC_TRNS    // enhance readability
#define XXXXXXX KC_NO

//Macro Definitions
#define SFMAC   M(01)      // shift-BASE switch

#define UMAC    M(10)      // call u
#define UE      M(11)      // send ü
#define SFUMAC  M(12)      // call U
#define SFUE    M(13)      // send Ü
#define AMAC    M(20)      // call a
#define AE      M(21)      // send ä
#define SFAMAC  M(22)      // call A
#define SFAE    M(23)      // send Ä
#define OMAC    M(30)      // call o
#define OE      M(31)      // send ö
#define SFOMAC  M(32)      // call O
#define SFOE    M(33)      // send Ö
#define SMAC    M(40)      // call s
#define SS      M(41)      // send ß

#define CUTP    M(50)      // cut on hold - paste on tap
#define COPP    M(51)      // copy on hold - paste on tap
#define RDUD    M(52)      // redo on hold - undo on tap
#define SCUTP   M(53)      // cut on hold - shift-paste on tap
#define SCOPP   M(54)      // copy on hold - shift-paste on tap

enum layers {
  _BASE,                   // Base
  _SBASE,                  // Shift-umlaut macro dummy layer
  _L11,                    // ü - umlaut macro dummy layers
  _L13,                    // Ü
  _L21,                    // ä
  _L23,                    // Ä
  _L31,                    // ö
  _L33,                    // Ö
  _L41,                    // ß
  _NMB,                    // navigation - numerals
  _FNB,                    // nav-mark - F-keys
  _SC1,                    // special characters 1
  _SC2,                    // special characters 2
  _OS                      // Unicode inputmethod switches
};

enum puq_keycodes {
// layer switches
  BASE = SAFE_RANGE,
  SBASE,
  NMB,
  FNB,
  SC1,
  SC2,
  OS,

// os switches
  LINUX,
  WIN,
  OSX
};

// Tap Dance Declarations
enum {
  ESC_CAP = 0,
  LCT_RCT = 1,
  LAL_RAL = 2,
  LSF_GUI = 3
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [ESC_CAP]  =  ACTION_TAP_DANCE_DOUBLE(KC_ESC , KC_CAPS),
  [LCT_RCT]  =  ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_RCTL),
  [LAL_RAL]  =  ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_RALT),
  [LSF_GUI]  =  ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_RGUI)
};

// unicode map
enum unicode_name {
  WINK,   // wink 😉
  CYCL,   // cycle 🚴
  RUNN,   // runner 🏃
  APOS,   // apostrophe ’
  QULO,   // quote low „
  QUUP,   // quote up “
  QUEN,   // quote end ”
  FDOT,   // fat dot •
  GMLE,   // guillemet left «
  GMRI,   // guillemet right »
  CARE,   // care of ℅
  TDOT,   // triple dot …
  SQUL,   // single quote low ‚
  SQUU,   // single quote up ‘
  SQUE,   // single quote end ’
  SICL,   // hammer & sicle ☭
  MUUU,   // muu μ
  DIAM,   // diameter ∅
  REQM,   // reverse question mark ⸮
  LSTR,   // long stroke —
  CENT,   // cent ¢
  SGML,   // single guillemet left ‹
  SGMR,   // single guillemet right ›
  SKLL,   // skull ☠
  DIAR    // diaresis ̈
};

const uint32_t PROGMEM unicode_map[] = {
  [WINK] = 0x1F609,
  [CYCL] = 0x1F6B4,
  [RUNN] = 0x1F3C3,
  [APOS] = 0x2019,
  [QULO] = 0x201E,
  [QUUP] = 0x201C,
  [QUEN] = 0x201D,
  [FDOT] = 0x2022,
  [GMRI] = 0x00BB,
  [GMLE] = 0x00AB,
  [CARE] = 0x2105,
  [TDOT] = 0x2026,
  [SQUL] = 0x201A,
  [SQUU] = 0x2018,
  [SQUE] = 0x2019,
  [SICL] = 0x262D,
  [MUUU] = 0x03BC,
  [DIAM] = 0x2205,
  [REQM] = 0x2E2E,
  [LSTR] = 0x2014,
  [CENT] = 0x00A2,
  [SGMR] = 0x203A,
  [SGML] = 0x2039,
  [SKLL] = 0x2620,
  [DIAR] = 0x0308
};

/*
 * .----------------------------------.    .----------------------------------.
 * |  P   | UMAC |      | COMM |  Q   |    |   V  |   C  |   L  |  M   |  B   |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |  H   |  I   |  E   | AMAC | OMAC |    |   D  |   T  |   R  |  N   | SMAC |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |  K   |  Y   |  ’   | DOT  |  X   |    !   J  |   G  |   Z  |  W   |  F   |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | NMB  | SC1  |SFMAC | LCTL | LALT |    | BSPC |  DEL | LSFT | SPC  | ENT  |
 * |      |      |=LSFT | RCTL | RALT |    | FNB  |  NMB | RGUI |      | SC2  |
 * '----------------------------------'    '----------------------------------'
 *
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = KEYMAP( /* BASE */
  DE_P    , UMAC    , XXXXXXX, DE_COMM    , DE_Q       , DE_V            , DE_C           , DE_L       , DE_M  , DE_B          , \
  DE_H    , DE_I    , DE_E   , AMAC       , OMAC       , DE_D            , DE_T           , DE_R       , DE_N  , SMAC          , \
  DE_K    , DE_Y    , X(APOS), DE_DOT     , DE_X       , DE_J            , DE_G           , DE_Z       , DE_W  , DE_F          , \
  TT(_NMB), MO(_SC1), SFMAC  , TD(LCT_RCT), TD(LAL_RAL), LT(_FNB,KC_BSPC), LT(_NMB,KC_DEL), TD(LSF_GUI), KC_SPC, LT(_SC2,KC_ENT) \
),

//SHIFT MACRO DUMMY LAYER
[_SBASE] = KEYMAP( /* SFMAC */
  _______, SFUMAC , _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, SFAMAC , SFOMAC , _______, _______, _______, _______, DE_S   , \
  _______, _______, DE_QUOT, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

//UMLAUT MACRO DUMMY LAYERS
[_L11] = KEYMAP( /* UMAC */
  _______, _______, UE     , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L13] = KEYMAP( /* SFUMAC */
  _______, _______, SFUE   , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L21] = KEYMAP( /* AMAC */
  _______, _______, AE     , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L23] = KEYMAP( /* SFAMAC */
  _______, _______, SFAE   , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L31] = KEYMAP( /* OMAC */
  _______, _______, OE     , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L33] = KEYMAP( /* SFOMAC */
  _______, _______, SFOE   , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

[_L41] = KEYMAP( /* SMAC */
  _______, _______, SS     , _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/*
 * .----------------------------------.    .----------------------------------.
 * | ESC  | PGUP |  UP  | PGDN | NLCK |    | PMNS |  P7  |  P8  |  P9  | PAST |
 * |/CAPS |      |      |      |      |    |      |      |      |      |      |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | HOME | LEFT | DOWN | RGHT | END  |    |  P0  |  P4  |  P5  |  P6  | PDOT |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | INS  | TAB  | CUTP | COPP | RDUD |    ! PPLS |  P1  |  P2  |  P3  | PSLS |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * '----------------------------------'    '----------------------------------'
 *
 */
[_NMB] = KEYMAP( /* NAVIGATION - NUMERALS */
  TD(ESC_CAP), KC_PGUP, KC_UP  , KC_PGDN, KC_NLCK, KC_PMNS, KC_P7  , KC_P8  , KC_P9  , KC_PAST, \
  KC_HOME    , KC_LEFT, KC_DOWN, KC_RGHT, KC_END , KC_P0  , KC_P4  , KC_P5  , KC_P6  , KC_COMM, \
  KC_INS     , KC_TAB , CUTP   , COPP   , RDUD   , KC_PPLS, KC_P1  , KC_P2  , KC_P3  , KC_PSLS, \
  _______    , _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/*
 * .----------------------------------.    .----------------------------------.
 * | ESC  |SPGUP | SUP  |SPGDN | PAUS |    | F12  |  F7  |  F8  |  F9  | LGUI |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |SHOME |SLEFT |SDOWN |SRGHT | SEND |    | F10  |  F4  |  F5  |  F6  | PDOT |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | INS  | TAB  | CUTP | COPP | RDUD |    ! F11  |  F1  |  F2  |  F3  | OS   |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * '----------------------------------'    '----------------------------------'
 *
 */
[_FNB] = KEYMAP( /*  NAV-MARK - FUNCTION-KEYS*/
  KC_ESC    , S(KC_PGUP), S(KC_UP)  , S(KC_PGDN), KC_PAUS  , KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_LGUI , \
  S(KC_HOME), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT), S(KC_END), KC_F10 , KC_F4  , KC_F5  , KC_F6  , KC_DOT  , \
  KC_INS    , KC_TAB    , SCUTP     , SCOPP     , RDUD     , KC_F11 , KC_F1  , KC_F2  , KC_F3  , OSL(_OS), \
  _______   , _______   , _______   , _______   , _______  , _______, _______, _______, _______, _______   \
),

/*
 * .----------------------------------.    .----------------------------------.
 * | PARA | UNDS |  „   |  “   |  “   |    | EXLM | LESS | MORE | EQL  | AMPR |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | BSLS | SLSH | PIPE | AT   | ASTR |    | QST  | LPRN | RPRN | MINS | •    |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | HASH | DLR  |  »   |  «   | TILD |    ! PLUS | PERC | QUOT | DQOT | RING |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * '----------------------------------'    '----------------------------------'
 *
 */
[_SC1] = KEYMAP( /* SPECIAL CHARACTERS 1 */
  DE_PARA, DE_UNDS, X(QULO), X(QUUP), X(QUEN), DE_EXLM, DE_LESS, DE_MORE, DE_EQL , DE_AMPR, \
  DE_BSLS, DE_SLSH, DE_PIPE, DE_AT  , DE_ASTR, DE_QST , DE_LPRN, DE_RPRN, DE_MINS, X(FDOT), \
  DE_HASH, DE_DLR , X(GMRI), X(GMLE), DE_TILD, DE_PLUS, DE_PERC, DE_QUOT, DE_DQOT, DE_RING, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/*
 * .----------------------------------.    .----------------------------------.
 * |  ℅   |  …   |  ‚   |  ‘   |  ’   |    |  ☭   | LBRC | RBRC |  µ   |  Ø   |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | GRV  | ACUT | EURO |  😉   | DIAR |    |  ⸮   | LCBR | RCBR |  —   | DOT  |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * | CIRC |  ¢   |  ›   |  ‹   | TILD |    |  ☠   |  🚴  | SQ2  | SQ3  |  🏃  |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * '----------------------------------'    '----------------------------------'
 *
 */
[_SC2] = KEYMAP( /* SPECIAL CHARACTERS 2 */
  X(CARE), X(TDOT), X(SQUL), X(SQUU), X(SQUE), X(SICL), DE_LBRC, DE_RBRC, X(MUUU), X(DIAM), \
  DE_GRV , DE_ACUT, DE_EURO, X(WINK), X(DIAR), X(REQM), DE_LCBR, DE_RCBR, X(LSTR), KC_DOT , \
  DE_CIRC, X(CENT), X(SGMR), X(SGML), DE_TILD, X(SKLL), X(CYCL), DE_SQ2 , DE_SQ3 , X(RUNN), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/*
 * .----------------------------------.    .----------------------------------.
 * |      |      |      |      |      |    |      |      |LINUX |      |      |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      | OSX  |    !      |      |      | WIN  |      |
 * !------+------+------+------+------!    !------+------+------+------+------!
 * |      |      |      |      |      |    |      |      |      |      |      |
 * '----------------------------------'    '----------------------------------'
 *
 */
[_OS] = KEYMAP( /* OS-UC-INPUTMETHOD oneshot x-l-w */
  _______, _______, _______, _______, _______, _______, _______, LINUX  , _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, OSX    , _______, _______, _______, WIN    , _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

};

static uint16_t key_timer;

const uint16_t PROGMEM fn_actions[] = { };

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {

    case 01: /* SFMAC */
      if (record->event.pressed) {
        layer_on(_SBASE);
        return MACRO( D(LSFT), END );
      } else {
        layer_off(_SBASE);
        return MACRO( U(LSFT), END );
      }
      break;

    case 10: /* UMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L31);
        layer_off(_L33);
        layer_off(_L21);
        layer_off(_L23);
        layer_off(_L13);
        layer_on(_L11);
        return MACRO( D(U), END );
      } else {
        return MACRO( U(U), END );
      }
      break;

    case 11: /* UE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(UE), END );
      } else {
        layer_off(_L11);
        return MACRO( U(UE), END );
      }
      break;

    case 12: /* SFUMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L31);
        layer_off(_L33);
        layer_off(_L21);
        layer_off(_L23);
        layer_off(_L11);
        layer_on(_L13);
        return MACRO( D(LSFT), D(U), END );
      } else {
        return MACRO( U(U), END );
      }
      break;

    case 13: /* SFUE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(LSFT), D(UE), END );
      } else {
        layer_off(_L13);
        return MACRO( U(UE), END );
      }
      break;

    case 20: /* AMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L31);
        layer_off(_L33);
        layer_off(_L23);
        layer_off(_L11);
        layer_off(_L13);
        layer_on(_L21);
        return MACRO( D(A), END );
      } else {
        return MACRO( U(A), END );
      }
      break;

    case 21: /* AE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(AE), END );
      } else {
        layer_off(_L21);
        return MACRO( U(AE), END );
      }
      break;

    case 22: /* SFAMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L31);
        layer_off(_L33);
        layer_off(_L21);
        layer_off(_L11);
        layer_off(_L13);
        layer_on(_L23);
        return MACRO( D(LSFT), D(A), END );
      } else {
        return MACRO( U(A), END );
      }
      break;

    case 23: /* SFAE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(LSFT), D(AE), END );
      } else {
        layer_off(_L23);
        return MACRO( U(AE), END );
      }
      break;

    case 30: /* OMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L33);
        layer_off(_L21);
        layer_off(_L23);
        layer_off(_L11);
        layer_off(_L13);
        layer_on(_L31);
        return MACRO( D(O), END );
      } else {
        return MACRO( U(O), END );
      }
      break;

    case 31: /* OE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(OE), END );
      } else {
        layer_off(_L31);
        return MACRO( U(OE), END );
      }
      break;

    case 32: /* SFOMAC */
      if (record->event.pressed) {
        layer_off(_L41);
        layer_off(_L31);
        layer_off(_L21);
        layer_off(_L23);
        layer_off(_L11);
        layer_off(_L13);
        layer_on(_L33);
        return MACRO( D(LSFT), D(O), END );
      } else {
        return MACRO( U(O), END );
      }
      break;

    case 33: /* SFOE */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(LSFT), D(OE), END );
      } else {
        layer_off(_L33);
        return MACRO( U(OE), END );
      }
      break;

    case 40: /* SMAC */
      if (record->event.pressed) {
        layer_off(_L31);
        layer_off(_L33);
        layer_off(_L21);
        layer_off(_L23);
        layer_off(_L11);
        layer_off(_L13);
        layer_on(_L41);
        return MACRO( D(S), END );
      } else {
        return MACRO( U(S), END );
      }
      break;

    case 41: /* SS */
      if (record->event.pressed) {
        return MACRO( D(BSPC), D(SS), END );
       } else {
        layer_off(_L41);
        return MACRO( U(SS), END );
      }
      break;

    case 50: {             /* CUTP = CUT-PASTE */
      if (record->event.pressed) {
         key_timer = timer_read();
       }
       else {
           if (timer_elapsed(key_timer) > 250) {
           return MACRO( D(LCTL), T(X), U(LCTL), END );
           }
           else {
           return MACRO( D(LCTL), T(V), U(LCTL), END );
           }
       }
       break;
    }

    case 51: {             /* COPP = COPY-PASTE */
      if (record->event.pressed) {
         key_timer = timer_read();
       }
       else {
           if (timer_elapsed(key_timer) > 250) {
           return MACRO( D(LCTL), T(C), U(LCTL), END );
           }
           else {
           return MACRO(  D(LCTL), T(V), U(LCTL), END );
           }
       }
       break;
    }

    case 52: {         /* RDUD = REDO-UNDO */
      if (record->event.pressed) {
         key_timer = timer_read();
       }
       else {
           if (timer_elapsed(key_timer) > 250) {
           return MACRO( D(LCTL), T(Z), U(LCTL), END );
           }
           else {
           return MACRO( D(LCTL), T(Y), U(LCTL), END );
           }
       }
       break;
    }

    case 53: {             /* SCUTP = CUT-SHIFT-PASTE */
      if (record->event.pressed) {
         key_timer = timer_read();
       }
       else {
           if (timer_elapsed(key_timer) > 250) {
           return MACRO(  D(LCTL), T(X), U(LCTL), END );
           }
           else {
           return MACRO( D(LSFT), D(LCTL), T(V), U(LCTL), U(LSFT), END );
           }
       }
       break;
    }

    case 54: {             /* SCOPP = COPY-SHIFT-PASTE */
      if (record->event.pressed) {
         key_timer = timer_read();
       }
       else {
           if (timer_elapsed(key_timer) > 250) {
           return MACRO( D(LCTL), T(C), U(LCTL), END );
           }
           else {
           return MACRO(  D(LSFT), D(LCTL), T(V), U(LCTL), U(LSFT), END );
           }
       }
       break;
    }


  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
    default_layer_set(_BASE);
};

// Runs all every scan - heavy duty
void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LINUX:
      set_unicode_input_mode(UC_LNX);
      layer_off(_OS);
      return false;
      break;
    case WIN:
      set_unicode_input_mode(UC_WINC);
      layer_off(_OS);
       return false;
      break;
    case OSX:
      set_unicode_input_mode(UC_OSX);
      layer_off(_OS);
      return false;
      break;
  }
  return true;
};

void led_set_user(uint8_t usb_led) {
}
