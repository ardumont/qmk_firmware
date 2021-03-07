// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2

// tap: space // hold: alt
#define ALT_SPC   LALT_T(KC_SPC)          // MT(MOD_LALT, KC_SPC)

// tap: a,   // hold: Ctrl
#define CTL_A     MT(MOD_LCTL, KC_A)      // LCTL_T(KC_A)
// tap: ;    // hold: Ctrl
#define CTL_SCLN  MT(MOD_RCTL, KC_SCLN)   // LCTL_T(KC_SCLN)

// tap: z    // hold: SHIFT
#define SFT_Z     MT(MOD_LSFT, KC_Z)      // SFT_T(KC_Z
// tap: /    // hold: SHIFT
#define SFT_SLSH MT(MOD_RSFT, KC_SLSH)

// Layer movment
#define FN0 MO(_RS)  // move to layer 1 (L1)
#define FN1 KC_TRNS  // move to layer 2 (L2)
#define FN2 TO(_QW)  // move to layer 0 (L0)

  /*
   *  q     w     e     r     t               ||         y        u     i/tab o  p
   *  a/ctl s     d     f     g               ||         h        j     k     l  ;/ctl
   *  z/sft x     c     v     b               ||         n        m     ,     .  //sft
   *  esc   tab  super L1     alt/spc alt/spc || alt/spc alt/spc  L1    -     '  enter
   */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,   KC_W,   KC_E,     KC_R,    KC_T,                       KC_Y,     KC_U,    KC_I,    KC_O,    KC_P     ,
    CTL_A,  KC_S,   KC_D,     KC_F,    KC_G,                       KC_H,     KC_J,    KC_K,    KC_L,    CTL_SCLN ,
    SFT_Z,  KC_X,   KC_C,     KC_V,    KC_B,                       KC_N,     KC_M,    KC_COMM, KC_DOT,  SFT_SLSH ,
    KC_ESC, KC_TAB, KC_LGUI,  FN0,     ALT_SPC,  ALT_SPC, ALT_SPC, ALT_SPC,  FN0,     KC_MINS, KC_QUOT, KC_ENT
  ),

  /*
   *  !       @     up     {    }               ||         pgup      7     8     9    *
   *  #     left   down  right  $               ||         pgdn      4     5     6    +
   *  [       ]      (     )    &               ||           `       1     2     3    \
   * lower  insert super  L2    alt/spc alt/spc || alt/spc alt/spc   L2    .     0    =
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_EXLM, KC_AT,   KC_UP,   KC_LCBR, KC_RCBR,                   KC_PGUP, KC_7,    KC_8,   KC_9, KC_ASTR ,
    KC_HASH, KC_LEFT, KC_DOWN, KC_RGHT, KC_DLR,                    KC_PGDN, KC_4,    KC_5,   KC_6, KC_PLUS ,
    KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_AMPR,                   KC_GRV,  KC_1,    KC_2,   KC_3, KC_BSLS ,
    TG(_LW), KC_INS,  KC_LGUI, FN1,     ALT_SPC, ALT_SPC, ALT_SPC, ALT_SPC, FN1,     KC_DOT, KC_0, KC_EQL
  ),
  /*
   * insert home   up  end   pgup             ||          up       F7  F8    F9     F10
   *  del   left  down right pgdn             ||         down      F4  F5    F6     F11
   *       volup             reset            ||                   F1  F2    F3     F12
   *       voldn  super L0   alt/spc alt/spc  || alt/spc alt/spc   L0  prtsc scroll pause
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,    KC_F7,   KC_F8,   KC_F9,   KC_F10  ,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_DOWN,  KC_F4,   KC_F5,   KC_F6,   KC_F11  ,
    KC_NO,   KC_VOLU, KC_NO,   KC_NO,   RESET,                     KC_NO,    KC_F1,   KC_F2,   KC_F3,   KC_F12  ,
    KC_NO,   KC_VOLD, KC_LGUI, FN2,     ALT_SPC, ALT_SPC, ALT_SPC, ALT_SPC,  FN2,     KC_PSCR, KC_SLCK, KC_PAUS
  )
};
