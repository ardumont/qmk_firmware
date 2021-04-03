// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QW,
    _RS,
    _LW,
};

// tap: a,   // hold: Ctrl
#define A_CTL     CTL_T(KC_A)            // MT(MOD_LCTL, KC_A);
// tap: ;    // hold: Ctrl
#define SCLN_CTL  CTL_T(KC_SCLN)         // MT(MOD_RCTL, KC_SCLN)

// tap: z    // hold: SHIFT
#define Z_SFT     SFT_T(KC_Z)
// tap: /    // hold: SHIFT
#define SLSH_SFT  SFT_T(KC_SLSH)

// tap: `    // hold: SHIFT
#define GRAVE_SFT SFT_T(KC_GRAVE)
// tap: [    // hold: SHIFT
#define RBRC_SFT  SFT_T(KC_RBRC)

// Layer movment
#define FN0 MO(_RS)  // move to layer 1 (L1)
#define FN1 TG(_LW)  // move to layer 2 (L2)
#define FN2 TO(_QW)  // move to layer 0 (L0)

  /*
   *  q     w     e     r   t      ||     y   u   i/tab o  p
   *  a/ctl s     d     f   g      ||     h   j   k     l  ;/ctl
   *  z/sft x     c     v   b  `   || \   n   m   ,     .  //sft
   *  esc   tab  super  alt L1 spc || spc L1  alt -     '  enter
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,   KC_W,   KC_E,     KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P    ,
    A_CTL,  KC_S,   KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    SCLN_CTL,
    Z_SFT,  KC_X,   KC_C,     KC_V,    KC_B,   KC_GRAVE, KC_BSLS, KC_N,   KC_M,    KC_COMM, KC_DOT,  SLSH_SFT,
    KC_ESC, KC_TAB, KC_LGUI,  KC_LALT, KC_SPC, FN0,      FN0,     KC_SPC, KC_LALT, KC_MINS, KC_QUOT, KC_ENT
  ),

  /*
   *  1     2      3     4   5       ||    6   7   8    9    0
   *  !     @      #     $   %       ||    ^   &   *    (    )
   *  `/sft ~      ?     ?   ?   ~   || |  +   -   /    [    ]/sft
   *  lower tab    super alt spc L2  || L2 spc alt =    {    }
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0    ,
    KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN ,
    GRAVE_SFT, KC_TILD,  KC_NO,   KC_NO,   KC_NO,   KC_TILD, KC_PIPE, KC_PLUS, KC_MINS, KC_SLSH, KC_LBRC, RBRC_SFT,
    FN1,       KC_TAB,  KC_LGUI, KC_LALT, KC_BSPC, FN1,    FN1,       KC_SPC,  KC_LALT, KC_EQL,  KC_LCBR, KC_RCBR
  ),

  /*
   * F1 F2 F3    F4  F5       ||    F6  F7  F8    F9  F10
   * __ __ __    __  __       ||    __  __  __    F11 F12
   * __ __ __    __  reset __ || __ __  __  __    __  __
   * L0 __ super alt __    L0 || L0 __ alt  prtsc __  L0
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_F1, KC_F2, KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,  KC_F9,  KC_F10,
    KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,   KC_NO,  KC_F11, KC_F12,
    KC_NO, KC_NO, KC_NO,   KC_NO,   RESET,   _______, _______, KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO ,
    FN2,   KC_NO, KC_LGUI, KC_LALT, _______, FN2,     FN2,     _______, KC_LALT, KC_NO,  KC_NO,  FN2
  )
};

// Increase slightly the A_CTL to reduce its typing annoyance (lingering ctl with side
// effect on the next keys)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_CTL:
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}
