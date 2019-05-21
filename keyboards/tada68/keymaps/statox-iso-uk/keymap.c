#include QMK_KEYBOARD_H

/*
 * The base of this layout is the tada68/iso-uk
 *
 * Modifications and features:
 *
 * Function layout
 * - Add brightness modifications on k and l
 * - Invert V- and V+ on m and ,
 *
 * Base layout
 * - Use KC_LSPO and KC_RSPC (i.e shift when held, parenthesis when taped)
 * - Use CAPS to switch to the function layer like FN
 */

#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |Del |
   * |-------------------------------------------------------    -----|
   * |FN     |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;| '|  #|Entr|PgUp|
   * |----------------------------------------------------------------|
   * |Shi/(|  \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .| /|Rshi/)|Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
  [_BL] = LAYOUT_iso(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,  \
    MO(_FL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),

  /* Keymap _FL1: Function Layer 1
   * ,----------------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete| Ins|
   * |----------------------------------------------------------------|
   * |     |   | ↑ |   |   |   |   |   |   |   |   |   |   |     |Home|
   * |-------------------------------------------------------    -----|
   * |       | ← | ↓ | → |   |   |   |   |B- |B+ |   |  |   |    | End|
   * |----------------------------------------------------------------|
   * |     |   |   |   | L-|LED| L+|   | V-|  V+|Mut|  | MsBtn|Up|MsBn|
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    | Lt| Dn| Rt |
   * `----------------------------------------------------------------'
   */
  [_FL] = LAYOUT_iso(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,  \
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_BRID, KC_BRIU, _______, _______, _______, _______, KC_END,  \
    _______, _______, _______, _______, BL_DEC,  BL_TOGG, BL_INC,  _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_BTN1, KC_MS_U, KC_BTN2, \
    _______, _______, _______,                   _______,                            _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R
	),
};

  /* Keymap Template
   * ,----------------------------------------------------------------.
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |    |
   * |-------------------------------------------------------    -----|
   * |       |   |   |   |   |   |   |   |   |   |   |  |   |    |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   |   |   |    |   |  |      |  |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
