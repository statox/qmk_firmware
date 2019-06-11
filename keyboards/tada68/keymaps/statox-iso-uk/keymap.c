#include QMK_KEYBOARD_H

/*
 * The base of this layout is the tada68/iso-uk
 *
 * Modifications and features:
 *
 * QMK Features
 * AUTO_SHIFT_ENABLE with NO_AUTO_SHIFT_ALPHA
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
 * - Tap danse on the A key to switch between à, â and a
 *
 * Base layout
 * - Use KC_LSPO and KC_RSPC (i.e shift when held, parenthesis when taped)
 * - Use CAPS to switch to the function layer like FN
 */

#define _BL 0 // Base Layer
#define _NL 1 // Navigation Layer
#define _SL 2 // Symbols Layer

/*
 * Tap Dance Declarations
 */
enum {
    E_AC,
    A_AC
};

/*
 * Tap Dance Definitions
 */
// Switch between é, è, ê and e
void accent_e (qk_tap_dance_state_t *state, void *user_data) {
    int nbOfCases = 3;
    switch (state->count % nbOfCases) {
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
        case 0:
            unicode_input_start();
            register_hex(0x00ea); // ê
            unicode_input_finish();
            break;
        default:
            // Should not happen
            register_code(KC_E);
            unregister_code(KC_E);
    }
}

// Switch between à, â and a
void accent_a (qk_tap_dance_state_t *state, void *user_data) {
    int nbOfCases = 2;
    switch (state->count % nbOfCases) {
        case 1:
            unicode_input_start();
            register_hex(0x00e0);   // à
            unicode_input_finish();
            break;
        case 0:
            unicode_input_start();
            register_hex(0x00e2); // â
            unicode_input_finish();
            break;
        default:
            // Should not happen
            register_code(KC_A);
            unregister_code(KC_A);
    }
}

/*
 * Tap Dance Registrations
 */
qk_tap_dance_action_t tap_dance_actions[] = {
  [E_AC] = ACTION_TAP_DANCE_FN (accent_e),
  [A_AC] = ACTION_TAP_DANCE_FN (accent_a)
};


enum custom_keycodes {
  E_AIGUE = SAFE_RANGE,
  C_CEDIL,
  A_GRAVE,
  U_GRAVE,
  O_GRAVE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_GRAVE:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex(0x00e0);   // à
                unicode_input_finish();
            }
            break;
        case E_AIGUE:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex(0x00e9);   // é
                unicode_input_finish();
            }
            break;
        case O_GRAVE:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex(0x00f2);   // ò
                unicode_input_finish();
            }
            break;
        case U_GRAVE:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex(0x00f9);   // ù
                unicode_input_finish();
            }
            break;
        case C_CEDIL:
            if (record->event.pressed) {
                unicode_input_start();
                register_hex(0x00e7);   // ç
                unicode_input_finish();
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     |Del |
   * |-------------------------------------------------------    -----|
   * |FN1    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;| '|  #|Entr|PgUp|
   * |----------------------------------------------------------------|
   * |Shi/(|  \ |  Z|  X|  C|  V|  B|  N|  M|  ,|  .| /|Rshi/)|Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |  Layer _NL or Space   |Alt|FN2|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   *
   * FN1 => Momentarily activate Navigation layer
   * FN2 => One shot symbol layer (TODO find something better to do with that)
   */
  [_BL] = LAYOUT_iso(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC,          KC_DEL,  \
    MO(_NL), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP, \
    KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                  LT(_SL, KC_SPC),                     KC_RALT, OSL(_SL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

  /* Keymap _NL: Navigation Layer 1
   * ,----------------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete|  1*|
   * |----------------------------------------------------------------|
   * |     |   |   |Eac|   |   | ← | ↓ | ↑ | → |   |   |   |     |  2*|
   * |-------------------------------------------------------    -----|
   * |       |Aac|   |   |Ms1|Ms2|MsL|MsD|MsU|MsL|   |  |   |    |  3*|
   * |----------------------------------------------------------------|
   * |     |   |   |   | L-|LED| L+|MwL|MwD|MwU |MwR|  | Mute |V+|  4*|
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    | B-| V-| B+ |
   * `----------------------------------------------------------------'
   *
   * 1* to 4* => Autoshift configuration (To remove after experiment)
   *  - 1*  Raise the Autoshift timeout
   *  - 2*  Lower the Autoshift timeout
   *  - 3*  Toggle the Autoshift feature
   *  - 4*  Report the current Autoshift timeout
   * MsL|MsD|MsU|MsL   => Move the mouse
   * ← | ↓ | ↑ | →     => Move the arrow keys
   * MwL|MwD|MwU |MwR  => Scroll the mouse wheel
   * L+, L- => Change Led brightness
   * V+, V- => Change volume
   * B+, B- => Change screen brightness
   * Eac, Aac => Tap dances to get accentuated characters
   */
  [_NL] = LAYOUT_iso(
    _______, KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_ASUP, \
    _______, _______,  _______, TD(E_AC), _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,          KC_ASDN, \
    _______, TD(A_AC), _______, _______,  KC_BTN1, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______, _______, _______, KC_ASTG, \
    _______, _______,  _______, _______,  BL_DEC,  BL_TOGG, BL_INC,  KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, KC_MUTE, KC_VOLU, KC_ASRP, \
    _______, _______,  _______,                    _______,                            _______, _______, _______, KC_BRID, KC_VOLD, KC_BRIU
    ),

  /* Keymap _SL: Symbols Layer 2
   * ,----------------------------------------------------------------.
   * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|       |Home|
   * |----------------------------------------------------------------|
   * |     |   |   | é |   |   |CIn| ù |   | ò |Sin|   |   |     |End |
   * |-------------------------------------------------------    -----|
   * |       | à |   |   |   |   |   |   |   |   |   |  |   |    |PgUp|
   * |----------------------------------------------------------------|
   * |     |   |   |   | ç |   |   |   |   |    |   |  |      |  |PgDn|
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   *
   * Cin => Ctrl+Ins equivalent of Ctrl+C to copy selected text
   * Sin => Shift+Ins equivalent of Ctrl+V to paste copied text
   */

  [_SL] = LAYOUT_iso(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,        KC_F7,   KC_F8,   KC_F9,   KC_F10,       KC_F11,  KC_F12,  _______, KC_HOME, \
    _______, _______, _______, E_AIGUE, _______, _______, RCTL(KC_INS), U_GRAVE, _______, O_GRAVE, RSFT(KC_INS), _______, _______,          KC_END , \
    _______, A_GRAVE, _______, _______, _______, _______, _______,      _______, _______, _______, _______,      _______, _______, _______, KC_PGUP, \
    _______, _______, _______, _______, C_CEDIL, _______, _______,      _______, _______, _______, _______,      _______, _______, _______, KC_PGDN, \
    _______, _______, _______,                    _______,                                _______, _______,      _______, _______, _______, _______
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

  /*
   * Layout template
   * [_XX] = LAYOUT_iso(
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
   *   _______, _______, _______,                    _______,                           _______, _______, _______, _______, _______, _______
   *   ),
   */
