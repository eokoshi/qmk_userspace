/*
Copyright 2019 @foostan
Copyright 2025 @eokoshi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum custom_keycodes {
    QK_M0,
    QK_M1,
    QK_M2,
    QK_M3,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // windows space (change keyboard layout)
            case QK_M0:
                SEND_STRING(SS_LGUI(" "));
                return false;
            // alt space (command palette)
            case QK_M1:
                SEND_STRING(SS_LGUI(SS_LALT(" ")));
                return false;
            // alt f4
            case QK_M2:
                SEND_STRING(SS_LALT(SS_TAP(X_F4)));
                return false;
            // alt tab
            case QK_M3:
                SEND_STRING(SS_LALT(SS_TAP(X_TAB)));
                return false;
        }
    }

    return true;
};

const key_override_t sft_scln_override = ko_make_basic(MOD_MASK_SHIFT, KC_SCLN, KC_PLUS);
const key_override_t sft_coln_override = ko_make_basic(MOD_MASK_SHIFT, KC_COLN, KC_ASTR);
const key_override_t sft_bsls_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSLS, KC_UNDS);

const key_override_t *key_overrides[] = {
	&sft_scln_override,
    &sft_coln_override,
    &sft_bsls_override
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    ENT_53, // Our custom tap dance key; add any other tap dance keys to this enum
};

td_state_t cur_dance(tap_dance_state_t *state);
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x6_3_ex2(
//, ----------------------------------------------------------------------.    ,---------------------------------------------------------------------.
GUI_T(KC_TAB),    KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,LT(4,KC_MUTE),      KC_VOLU,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,        KC_BSPC,
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+---------------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,      KC_G,        QK_M1,      KC_VOLD,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,        KC_COLN,
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+---------------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,                                KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, CTL_T(KC_BSLS),
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+---------------|
                                       KC_LALT, LT(1,KC_ESC), LT(2,KC_TAB),     TD(ENT_53), KC_SPC,  KC_DEL
                                   //`------------------------------------'    `------------------------------------'
),
[1] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
    KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS,   QK_M0, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_GRV, KC_QUOT, KC_LPRN, KC_RPRN, KC_TILD, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,   QK_M3,  KC_SPC,  KC_ENT, KC_BSPC,  KC_DEL, KC_TRNS,      KC_TRNS,  KC_EQL,  KC_DLR, KC_PERC, KC_AMPR, KC_PIPE, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_UNDS, KC_EXLM, KC_DQUO, KC_HASH, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                      //`------------------------'     `--------------------------'
),
[2] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
    KC_TRNS,   KC_AT,    KC_7,    KC_8,    KC_9, KC_CIRC, KC_TRNS,      KC_TRNS,   KC_AT,    KC_7,    KC_8,    KC_9, KC_CIRC, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_MINS,    KC_4,    KC_5,    KC_6, KC_COMM, KC_TRNS,      KC_TRNS, KC_MINS,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_ASTR,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,    KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT,                           KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_COMM,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                      //`------------------------'     `--------------------------'
),
[3] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
     QK_RBT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_TRNS, KC_TRNS,      KC_TRNS,   KC_AT,    KC_7,    KC_8,    KC_9, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    QK_BOOT,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_TRNS, KC_TRNS,      KC_TRNS, KC_MINS,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
QK_CLEAR_EEPROM,KC_F1,  KC_F2,   KC_F3,   KC_F4, KC_TRNS,                           KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_COMM,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                    //`--------------------------'    `--------------------------'
),
[4] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      RM_PREV, KC_TRNS, RM_VALD, RM_VALU, KC_TRNS, KC_TRNS, RM_TOGG,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      RM_NEXT, RM_SPDD, RM_HUED, RM_HUEU, RM_SPDU, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, RM_SATD, RM_SATU, KC_TRNS, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,  KC_TRNS
                                    //`--------------------------'    `---------------------------'
),
[5] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,---------------------------------------------------------------.
    KC_TRNS, KC_TRNS, MS_WHLU,   MS_UP, MS_WHLD, KC_TRNS, KC_TRNS,      KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, KC_TRNS,    QK_M2,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+---------|
    KC_TRNS, MS_WHLL, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLR, KC_TRNS,      KC_TRNS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_TRNS,  KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+---------|
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+---------|
                                        KC_TRNS, MS_BTN1, MS_BTN2,      KC_TRNS, KC_TRNS, KC_TRNS
                                    //`--------------------------'    `---------------------------'
)
};

const uint16_t PROGMEM r1[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM r2[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM r3[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM r4[] = {KC_A, KC_F, COMBO_END};
const uint16_t PROGMEM r5[] = {KC_A, KC_G, COMBO_END};
const uint16_t PROGMEM r6[] = {KC_S, KC_F, COMBO_END};

const uint16_t PROGMEM l1[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM l2[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM l3[] = {KC_J, KC_SCLN, COMBO_END};
const uint16_t PROGMEM l4[] = {KC_H, KC_SCLN, COMBO_END};
const uint16_t PROGMEM l5[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM l6[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM l7[] = {KC_H, KC_J, COMBO_END};

const uint16_t PROGMEM left[] = {TD(ENT_53), KC_H, COMBO_END};
const uint16_t PROGMEM down[] = {TD(ENT_53), KC_J, COMBO_END};
const uint16_t PROGMEM up[] = {TD(ENT_53), KC_K, COMBO_END};
const uint16_t PROGMEM right[] = {TD(ENT_53), KC_L, COMBO_END};
const uint16_t PROGMEM home[] = {TD(ENT_53), KC_Y, COMBO_END};
const uint16_t PROGMEM end[] = {TD(ENT_53), KC_O, COMBO_END};

combo_t key_combos[] = {
    COMBO(r1, KC_LCBR),
    COMBO(r2, KC_LBRC),
    COMBO(r3, KC_LPRN),
    COMBO(r4, KC_TILD),
    COMBO(r5, KC_LABK),
    COMBO(r6, KC_EQL),
    COMBO(l1, KC_RPRN),
    COMBO(l2, KC_DQUO),
    COMBO(l3, KC_UNDS),
    COMBO(l4, KC_RABK),
    COMBO(l5, KC_RBRC),
    COMBO(l6, KC_RCBR),
    COMBO(l7, KC_MINS),
    COMBO(left, KC_LEFT),
    COMBO(down, KC_DOWN),
    COMBO(up, KC_UP),
    COMBO(right, KC_RIGHT),
    COMBO(home, KC_HOME),
    COMBO(end, KC_END),
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif


// TAP DANCE
// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2 && state->pressed) return TD_DOUBLE_HOLD;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(5);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(3);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(5);
    }
    if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        layer_off(3);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [ENT_53] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};
