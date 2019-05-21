#include QMK_KEYBOARD_H

/*
 * The base of this layout is the tada68/iso-uk
 *
 * Modifications and features:
 *
 * Function layout
 * - Change brightness with Left and Right
 * - Change volume with Up and Down
 * - Mute with RShift
 * - Move mouse with hjkl
 * - Clic mouse with u and i
 * - Toggle LED with V
 * - Change LED brightness with c and b
 * - Tap danse on the E key to switch between é, è, ê and e
 *
 * Base layout
 * - Use KC_LSPO and KC_RSPC (i.e shift when held, parenthesis when taped)
 * - Use CAPS to switch to the function layer like FN
 */

#define _BL 0
#define _FL 1

/*
 * Tap Dance Declarations
 */
enum {
  E_AC
};

/*
 * Tap Dance Definitions
 */
// Switch between é, è, ê and e
void accent_e (qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            unicode_input_start();
            register_hex(0x00e9);   // é
            unicode_input_finish();
            break;
        case 2:
            unicode_input_start();
            register_hex(0x00e8); // è
            unicode_input_finish();
            break;
        case 3:
            unicode_input_start();
            register_hex(0x00ea); // ê
            unicode_input_finish();
            break;
        default:
            register_code(KC_E);
            unregister_code(KC_E);
    }
}

/*
 * Tap Dance Registrations
 */
qk_tap_dance_action_t tap_dance_actions[] = {
  [E_AC] = ACTION_TAP_DANCE_FN (accent_e)
};

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
   * |     |   | ↑ |Eac|   |   |   |Ms1|Ms2|   |   |   |   |     |Home|
   * |-------------------------------------------------------    -----|
   * |       | ← | ↓ | → |   |   |MsL|MsD|MsU|MsL|   |  |   |    | End|
   * |----------------------------------------------------------------|
   * |     |   |   |   | L-|LED| L+|   |   |    |   |  | Mute |V+|    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    | B-| V-| B+ |
   * `----------------------------------------------------------------'
   */
  [_FL] = LAYOUT_iso(
    _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,  \
    _______, _______, KC_UP,   TD(E_AC), _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______,          KC_HOME, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT,  _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, _______, _______, KC_END,  \
    _______, _______, _______, _______,  BL_DEC,  BL_TOGG, BL_INC,  _______, _______, _______, _______, _______, KC_MUTE, KC_VOLU, _______, \
    _______, _______, _______,                    _______,                            _______, _______, _______, KC_BRID, KC_VOLD, KC_BRIU
	),
};

/*
 * Set up the proper unicode mode for linux
 */
void matrix_init_user(void) {
	set_unicode_input_mode(UC_LNX); // or UC_WINC
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
