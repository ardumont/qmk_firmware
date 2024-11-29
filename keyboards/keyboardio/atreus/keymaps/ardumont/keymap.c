// Copyright (C) 2019, 2020  Keyboard.io, Inc
//               2021  Antoine R. Dumont (@ardumont) <ardumont@duck.com>
//
// this is the style you want to emulate. This is the canonical layout file for the
// Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix
// below. The underscores don't mean anything - you can have a layer called STUFF or any
// other name. Layer names don't all need to be of the same length, obviously, and you
// can also skip them entirely and just use numbers.
enum layer_names {
    _LAYER0,  // default qwerty use
    _LAYER1,  // Access number and extra characters (!, ...)
    _LAYER2,  // Access Fn (F0, F1, ... and qmk keyboard functionalities)
};

// Layer movement
// https://docs.qmk.fm/feature_layers
#define FN0 MO(_LAYER1)  // move to layer 1 (L1)
#define FN1 TG(_LAYER2)  // move to layer 2 (L2)
#define FN2 TO(_LAYER0)  // move to layer 0 (L0)

// Meaning
// - MO: momentarily activates layer. As soon as you let go of the key, the layer is
//   deactivated.
// - TG: toggles layer, activating it if it's inactive and vice versaxs
// - T0: activates layer and de-activates all other layers (except your default layer).
//   This function is special, because instead of just adding/removing one layer to your
//   active layer stack, it will completely replace your current active layers, uniquely
//   allowing you to replace higher layers with a lower one. This is activated on keydown
//   (as soon as the key is pressed).

// tap: z    // hold: SHIFT
#define SFT_Z     SFT_T(KC_Z)
// tap: /    // hold: SHIFT
#define SFT_SLSH  SFT_T(KC_SLSH)

// tap: `    // hold: SHIFT
#define SFT_GRAVE SFT_T(KC_GRAVE)
// tap: [    // hold: SHIFT
#define SFT_RBRC  SFT_T(KC_RBRC)

  /*
   *  q     w     e     r   t      ||     y   u   i/tab o  p
   *  a     s     d     f   g      ||     h   j   k     l  ;
   *  z/sft x     c     v   b  `   || \   n   m   ,     .  //sft
   *  ctl   esc  super  alt L1 spc || spc L1  alt -     '  ctl
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,   KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN ,
    SFT_Z,   KC_X,   KC_C,     KC_V,    KC_B,   KC_GRAVE, KC_BSLS, KC_N,   KC_M,    KC_COMM, KC_DOT,  SFT_SLSH,
    KC_LCTL, KC_ESC, KC_LGUI,  KC_LALT, KC_SPC, FN0,      FN0,     KC_SPC, KC_LALT, KC_MINS, KC_QUOT, KC_LCTL
  ),

  /*
   *  1     2      3     4   5       ||    6   7   8    9      0
   *  !     @      #     $   %       ||    ^   &   *    (      )
   *  `/sft ~      ?     ?   ?   ~   || |  +   -   /    [      ]/sft
   *  ctl   esc    super alt spc L2  || L2 spc alt =    pageup pagedown
   */
  [_LAYER1] = LAYOUT( /* [> RAISE <] */
    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,       KC_0    ,
    KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,    KC_RPRN ,
    SFT_GRAVE, KC_TILD, KC_NO,   KC_NO,   KC_NO,   KC_TILD, KC_PIPE, KC_PLUS, KC_MINS, KC_SLSH, KC_LBRC,    SFT_RBRC,
    _______,   _______, _______, _______, _______, FN1,     FN1,     _______, _______, KC_EQL,  KC_PAGE_UP, KC_PAGE_DOWN
  ),

  /*
   * F1    F2  F3    F4      F5    ||    F6  F7  F8    F9  F10
   * __    __  __    __      F11   ||    F12 __  __    __  __
   * bootl dbg rst   eep-clr __ __ ||  __  __  __    __  __
   * ctl   esc super alt __  L0    || L0 __ alt  prtsc esc ctl
   */
  [_LAYER2] = LAYOUT( /* [> LOWER <] */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F11,                KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
    QK_BOOT, DB_TOGG, QK_RBT,  EE_CLR,  KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO ,  KC_NO,   KC_NO ,  KC_NO,
    _______, _______, _______, _______, _______, FN2,   FN2,   _______, _______, KC_PSCR, _______, _______
  )
};

//Note:
// QK_BOOT: Put the keyboard into bootloader mode for flashing
// DB_TOGG: Toggle debug mode
// QK_RBT: Resets the keyboard. Does not load the bootloader
// EE_CLR: Reinitializes the keyboard's EEPROM (persistent memory)

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

bool substitute_keycode(uint16_t keycode, keyrecord_t *record, uint8_t mod_state, uint16_t substitute_keycode) {
    /* Substitute keycode if condition matches */
    // Initialize a boolean variable that keeps track
    // of the delete key status: registered or not?
    static bool key_registered;
    // ctrl activated?
    if ((mod_state & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL)) {
        if (record->event.pressed) {
            // No need to register KC_LCTL because it's already active.
            unregister_code(KC_LCTL);
            // Send substitute code
            register_code(substitute_keycode);
            // Update the boolean variable to reflect the status of the register
            key_registered = true;
            // Reapplying modifier state so that the held shift key(s)
            // still work even after having tapped the Backspace/Delete key.
            set_mods(mod_state);
            // Do not let QMK process the keycode further
            return false;
        } else {
            // In case substitude_keycode is still being sent even after the release of
            // the key
            if (key_registered) {
                unregister_code(substitute_keycode);
                key_registered = false;
                // Do not let QMK process the keycode further
                return false;
            }
        }
    }
    // Else, let QMK process the keycode as usual
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
    case KC_I:
        return substitute_keycode(keycode, record, mod_state, KC_TAB);
    case KC_M:
        return substitute_keycode(keycode, record, mod_state, KC_ENTER);
    case KC_H:
        return substitute_keycode(keycode, record, mod_state, KC_BSPC);
    case KC_D:
        return substitute_keycode(keycode, record, mod_state, KC_DEL);
    case KC_N:
        return substitute_keycode(keycode, record, mod_state, KC_DOWN);
    case KC_P:
        return substitute_keycode(keycode, record, mod_state, KC_UP);
    }
    return true;
};
