/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUMERAL,
    LAYER_FUNCTION,
    LAYER_SYMBOLS,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define SPC_NUM LT(LAYER_NUMERAL, KC_SPC)
#define ESC_FUN LT(LAYER_FUNCTION, KC_ESC)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NAV LT(LAYER_NAVIGATION, KC_BSPC)
#define CAP_MED LT(LAYER_MEDIA, KC_CAPS)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)


#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
       LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), KC_G, KC_H, RGUI_T(KC_J), RALT_T(KC_K), RSFT_T(KC_L), RCTL_T(KC_SCLN),
       PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH,
                      KC_TAB, SPC_NUM, ESC_FUN, ENT_SYM, BSP_NAV, CAP_MED
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, KC_PAST, KC_7, KC_8, KC_9, KC_PSLS,
    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,  XXXXXXX, KC_PPLS, KC_4, KC_5, KC_6, KC_PMNS,
     XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, KC_PDOT, KC_1, KC_2, KC_3, KC_EQL,
                       XXXXXXX, _______, XXXXXXX, KC_ENT, KC_BSPC, KC_0
  ),

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    S(KC_6),  S(KC_7), S(KC_8), S(KC_9), S(KC_0), XXXXXXX, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,
    KC_GRV, KC_MINS,   KC_EQL, S(KC_LBRC), S(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX,  XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
  ),
};

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,   KC_RGHT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
                      XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, _______, XXXXXXX
  ),

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
    XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, _______
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX, XXXXXXX, KC_BTN3, SNIPING, DRGSCRL, _______,
                      KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2, KC_BTN3
  ),

enum combo_events {
    SD_COMBO,    // S + D -> Ctrl + Space
    KL_COMBO,    // K + L -> ?
    COMBO_LENGTH 
};

const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    [SD_COMBO] = COMBO_ACTION(sd_combo),  // S + D -> Ctrl + Space
    [KL_COMBO] = COMBO(kl_combo, KC_QUES) // K + L -> ?
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case SD_COMBO:
            if (pressed) {
                register_code(KC_LCTL);  
                register_code(KC_SPC);   
            } else {
                unregister_code(KC_SPC); 
                unregister_code(KC_LCTL);
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case SD_COMBO:
            return 50;
        case KL_COMBO:
            return 50;
        default:
            return COMBO_TERM;
    }
}

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_MEDIA] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),  ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),  ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE
