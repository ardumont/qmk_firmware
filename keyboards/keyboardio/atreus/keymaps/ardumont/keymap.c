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
#define CTL_A     MT(MOD_LCTL, KC_A)      // LCTL_T(KC_A)
// tap: ;    // hold: Ctrl
#define CTL_SCLN  MT(MOD_RCTL, KC_SCLN)   // LCTL_T(KC_SCLN)

// tap: z    // hold: SHIFT
#define SFT_Z     MT(MOD_LSFT, KC_Z)      // SFT_T(KC_Z
// tap: /    // hold: SHIFT
#define SFT_SLSH MT(MOD_RSFT, KC_SLSH)

// tap: `    // hold: SHIFT
#define SFT_GRAVE MT(MOD_LSFT, KC_GRAVE)
// tap: [    // hold: SHIFT
#define SFT_RBRC MT(MOD_RSFT, KC_RBRC)

// Layer movment
#define FN0 MO(_RS)  // move to layer 1 (L1)
#define FN1 KC_TRNS  // move to layer 2 (L2)
#define FN2 TO(_QW)  // move to layer 0 (L0)

// %
#define KC_PCT S(KC_5)
// ~
#define KC_TLD S(KC_GRAVE)

  /*
   *  q     w     e     r   t      ||     y   u   i/tab o  p
   *  a/ctl s     d     f   g      ||     h   j   k     l  ;/ctl
   *  z/sft x     c     v   b  `   || \   n   m   ,     .  //sft
   *  esc   tab  super  alt L1 spc || spc L1  alt -     '  enter
   */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,   KC_W,   KC_E,     KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P    ,
    CTL_A,  KC_S,   KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    CTL_SCLN,
    SFT_Z,  KC_X,   KC_C,     KC_V,    KC_B,   KC_GRAVE, KC_BSLS, KC_N,   KC_M,    KC_COMM, KC_DOT,  SFT_SLSH,
    KC_ESC, KC_TAB, KC_LGUI,  KC_LALT, KC_SPC, FN0,      FN0,     KC_SPC, KC_LALT, KC_MINS, KC_QUOT, KC_ENT
  ),

  /*
   *  1     2      3     4   5       ||    6   7   8    9    0
   *  !     @      #     $   %       ||    ^   &   *    (    )
   *  `/sft ~      ?     ?   ?   ~   || |  +   -   /    [    ]/sft
   *  lower tab    super alt spc L2  || L2 spc alt =    {    }
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0    ,
    KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PCT,                  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN ,
    SFT_GRAVE, KC_TLD,  KC_NO,   KC_NO,   KC_NO,  KC_TLD, KC_PIPE, KC_PLUS, KC_MINS, KC_SLSH, KC_LBRC, SFT_RBRC ,
    TG(_LW),   KC_INS,  KC_LGUI, KC_LALT, KC_SPC, FN1,    FN1,     KC_SPC,  KC_LALT, KC_EQL,  KC_LCBR, KC_RCBR
  ),

  /*
   * insert home   up  end      pgup       ||     up  F7  F8    F9     F10
   * del    left  down right    pgdn       ||    down F4  F5    F6     F11
   * __     volup __   __       reset  __  || __ __   F1  F2    F3     F12
   * __     voldn super alt/spc alt    L0  || L0 __   alt prtsc scroll pause
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_NO,   KC_VOLU, KC_NO,   KC_NO,   RESET,   _______, _______, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,
    KC_NO,   KC_VOLD, KC_LGUI, KC_LALT, _______, FN2,     FN2,     _______, KC_LALT, KC_PSCR, KC_SLCK, KC_PAUS
  )
};
