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
#include "keymap_japanese.h"

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
                SEND_STRING(SS_LGUI(SS_DELAY(1) SS_TAP(X_SPC)));
                return false;
            // alt space (command palette)
            case QK_M1:
                SEND_STRING(SS_LALT(SS_DELAY(1) SS_TAP(X_SPC)));
                return false;
            // alt f4
            case QK_M2:
                SEND_STRING(SS_LALT(SS_DELAY(1) SS_TAP(X_F4)));
                return false;
            // alt tab
            case QK_M3:
                SEND_STRING(SS_LALT(SS_DELAY(1) SS_TAP(X_TAB)));
                return false;
        }
    }

    return true;
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(5, KC_H):
            return true;
        case LT(5, KC_J):
            return true;
        case LT(5, KC_K):
            return true;
        case LT(5, KC_L):
            return true;
        case LT(2, KC_H):
            return true;
        default:
            return false;
    }
}

bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys.
    }
    switch (get_tap_keycode(keycode)) {
        case KC_SPC:
        case KC_A ... KC_G:
        case KC_I:
        case KC_M ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x6_3_ex2(
//,-----------------------------------------------------------------------.    ,----------------------------------------------------------------------.
GUI_T(KC_TAB),    KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,LT(4,KC_MUTE),      KC_VOLU,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,         KC_BSPC,
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+----------------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,      KC_G,        QK_M1,      KC_VOLD,    KC_H,    KC_J,    KC_K,    KC_L, JP_SCLN, SFT_T(JP_COLN),
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+----------------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,                                KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, CTL_T(JP_BSLS),
//|----------+--------+--------+--------+--------+----------+-------------|    |--------+--------+--------+--------+--------+--------+----------------|
                                       KC_LALT, LT(1,KC_ESC), LT(2,KC_TAB),      LT(3,KC_ENT), LT(5,KC_SPC), KC_DEL
                                   //`------------------------------------'    `------------------------------------'
),
[1] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
    KC_TRNS, KC_TRNS, JP_MHEN, JP_ZKHK,   QK_M0, KC_TRNS, KC_TRNS,      KC_TRNS,  JP_GRV, JP_QUOT, JP_LPRN, JP_RPRN, JP_TILD, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,   QK_M3,  KC_SPC,  KC_ENT, KC_BSPC,  KC_DEL, KC_TRNS,      KC_TRNS,  JP_EQL,  JP_DLR, JP_PERC, JP_AMPR, JP_PIPE, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        JP_UNDS, JP_EXLM, JP_DQUO, JP_HASH, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                      //`------------------------'     `--------------------------'
),
[2] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
    KC_TRNS,   JP_AT,    JP_7,    JP_8,    JP_9, JP_CIRC, KC_TRNS,      KC_TRNS,   JP_AT,    JP_7,    JP_8,    JP_9, JP_CIRC, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, JP_MINS,    JP_4,    JP_5,    JP_6, JP_COMM, KC_TRNS,      KC_TRNS, JP_MINS,    JP_4,    JP_5,    JP_6, JP_PLUS, JP_ASTR,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,    JP_0,    JP_1,    JP_2,    JP_3,  JP_DOT,                           JP_0,    JP_1,    JP_2,    JP_3,  JP_DOT, JP_COMM,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                      //`------------------------'     `--------------------------'
),
[3] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.    ,--------------------------------------------------------------.
     QK_RBT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_TRNS, KC_TRNS,      KC_TRNS,   JP_AT,    JP_7,    JP_8,    JP_9, KC_TRNS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------,    ,--------+--------+--------+--------+--------+--------+--------|
    QK_BOOT,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_TRNS, KC_TRNS,      KC_TRNS, JP_MINS,    JP_4,    JP_5,    JP_6, JP_PLUS, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'    '--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_TRNS,                           JP_0,    JP_1,    JP_2,    JP_3,  JP_DOT, JP_COMM,
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
const uint16_t PROGMEM l3[] = {KC_J, JP_SCLN, COMBO_END};
const uint16_t PROGMEM l4[] = {KC_H, JP_SCLN, COMBO_END};
const uint16_t PROGMEM l5[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM l6[] = {KC_L, JP_SCLN, COMBO_END};
const uint16_t PROGMEM l7[] = {KC_H, KC_J, COMBO_END};

combo_t key_combos[] = {
    COMBO(r1, JP_LCBR),
    COMBO(r2, JP_LBRC),
    COMBO(r3, JP_LPRN),
    COMBO(r4, JP_TILD),
    COMBO(r5, JP_LABK),
    COMBO(r6, JP_EQL),
    COMBO(l1, JP_RPRN),
    COMBO(l2, JP_DQUO),
    COMBO(l3, JP_UNDS),
    COMBO(l4, JP_RABK),
    COMBO(l5, JP_RBRC),
    COMBO(l6, JP_RCBR),
    COMBO(l7, JP_MINS),
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
