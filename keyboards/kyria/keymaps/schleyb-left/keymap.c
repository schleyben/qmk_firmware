/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pimoroni_trackball.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
#include "pointing_device.h"
#endif

#define _QWERTY 0
#define _WORKMAN 1
#define _GAMING 2
#define _SYM 3
#define _NAV 4
#define _ADJUST 5
#define KC_CAD LALT(LCTL(KC_DEL))
//#define KC_SNIP LGUI(LSFT(KC_S))


enum layers {
    QWERTY = SAFE_RANGE,
    WORKMAN,
    GAMING,
    NAV,
    SYM,
    ADJUST,
    CREDSHORT,
    FULLCRED,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  -_    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |   XX | CAD  |   N  |   M  | ,  < | . >  | /  ? |  RShift|
 * `----------------------+------+------+------|      |      |  |------+------+------+------+------+----------------------'
 *                        | GUI  | ESC  |      | Space| BSP  |  |  XX  | BSP  | NAV  | SYM  | CAPS |
 *                        |      | Alt  | SYM  | NAV  |      |  |  XX  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT( 
      KC_TAB,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      MT(MOD_LCTL, KC_ESC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSPO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   XXXXXXX,   XXXXXXX, XXXXXXX, KC_CAD, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
          KC_MUTE, KC_LALT, SYM, LT(_NAV, KC_SPC), MT(MOD_LGUI, KC_ENT), XXXXXXX, KC_BSPC, LT(_NAV, KC_ENT), SYM, KC_CAPS
    ),
/*
 * Workman Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  Q   |  D   |  R   |  W   |  B   |                              |   J  |  F   |  U   |  P   |  ;   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  A   |  S   |  H   |  T   |  G   |                              |   Y  |  N   |  E   |  O   |  I   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  Z   |  X   |  M   |  C   |  V   |      |      |  |      |      |   K  |  L   |  ,   |  .   |  / ? |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_WORKMAN] = LAYOUT(
      _______, KC_Q, KC_D, KC_R, KC_W, KC_B,                                     KC_J, KC_F, KC_U, KC_P, KC_SCLN, _______,
      _______, KC_A, KC_S, KC_H, KC_T, KC_G,                                     KC_Y, KC_N, KC_E, KC_O, KC_I, _______,
      _______, KC_Z, KC_X, KC_M, KC_C, KC_V, _______, _______, _______, _______, KC_K, KC_L,  KC_COMM, KC_DOT,  KC_SLSH, _______,
                  _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),
/*
 * Gaming Layer: left hand with a number row and other things
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   1  |   2  |   3  |   4  |   5  |                              |   Y  |   U  |   I  |   O  |   P  |  -_    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | CTRL   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |  RShift|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | ESC  | Enter| Space| BS   |  |      |      |      |      |      |
 *                        |      | Alt  | Ctrl |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAMING] = LAYOUT(
      _______,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      KC_LCTL,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   _______,   _______, _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    _______, _______, _______, KC_SPC, KC_BSPC, _______, _______, _______,  _______, _______
    ),
/*
 * NAV Layer: media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | BSP  |      |  UP  |      |      |                              |      |      |MsWlUp|      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  DEL | LEFT | DOWN |RIGHT |      |                              |      |Mouse1|Mouse2|Mouse3|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | INS  | HOME | END  | PGUP | PGDN |      |      |  |      |SCRED |      |      |MsWlDn|      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+-----+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_BSPC, _______, KC_UP, _______, _______,                                        _______,    _______,    KC_WH_U,    _______,    _______,    _______,
      _______, KC_DEL, KC_LEFT,  KC_DOWN, KC_RGHT, _______,                                     _______, KC_BTN1, KC_BTN3,  KC_BTN2, KC_BTN4, KC_BTN5,
      _______, KC_INS,  KC_HOME,  KC_END,  KC_PGUP,  KC_PGDOWN, _______, _______, _______, CREDSHORT, _______, _______, KC_WH_D, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * SYM Layer: Symbols, Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |   +  |  7   |  8   |  9   |  -   |                              |  !   |  @   |  #   |  $   |  %   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   ENT  |  0   |  4   |  5   |  6   |  =   |                              |  ^   |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   .  |  1   |  2   |  3   |      |      |      |  |      |FCRED |  [   |   ]  |  {   |  }   |  \   |    |   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      KC_GRV, KC_PLUS, KC_7,   KC_8, KC_9, KC_MINS,                                 KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,_______,
      _______,KC_0, KC_4,  KC_5, KC_6, KC_EQL,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,  
      _______,KC_DOT, KC_1, KC_2, KC_3, _______,_______, _______, _______, FULLCRED,  KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR,  KC_BSLS, KC_PIPE,
                                 _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),
/*SECOND COPY FOR TESTING
 * SYM Layer: Symbols, Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  !   |  @   |  #   |  $   |  %    |                             |   +  |  7   |  8   |  9   |  -   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ^   |  &   |  *   |  (   |  )   |                              |  0   |  4   |  5   |  6   |  =   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  [   |   ]  |  {   |  }   |  |   |      |      |  |      |      |   .  |  1   |  2   |  3   | ENT  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'

    [_SYM] = LAYOUT(
      KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                             KC_PLUS, KC_7,   KC_8, KC_9, KC_MINS,  _______, 
      _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                           KC_0, KC_4,  KC_5, KC_6, KC_EQL, _______,  
      _______, KC_LBRC, KC_RBRC,  KC_LCBR, KC_RCBR,  KC_PIPE, _______, _______, _______, _______, KC_DOT, KC_1, KC_2, KC_3, KC_ENT, _______,
                                 _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______
    ),
*/
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   F1   |  F2  | F3   | F4   | F5   |  F6  |                              | F7   |  F8  | F9   | F10  | F11  |   F12  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |WORKMAN|QWERTY|GAMING|      |      |       |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,                                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     WORKMAN, QWERTY, GAMING, _______,  _______,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, KC_ASDN, KC_ASUP, KC_ASRP, KC_ASON, KC_ASOFF, KC_ASTG,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        //set_single_persistent_default_layer(_QWERTY);
		layer_on(_QWERTY);
		layer_off(_WORKMAN);
		layer_off(_GAMING);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        //set_single_persistent_default_layer(_WORKMAN);
		layer_on(_WORKMAN);
		layer_off(_GAMING);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        //set_single_persistent_default_layer(_GAMING);
		layer_on(_GAMING);
      }
      return false;
      break;
    case SYM:
      if (record->event.pressed) {
        layer_on(_SYM);
      } else {
        layer_off(_SYM);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
      } else {
        layer_off(_NAV);
      }
      return false;
      break;
    case FULLCRED:
        if (record->event.pressed) {
            SEND_STRING("xxxxxx");
        }
        break;
	case CREDSHORT:
        if (record->event.pressed) {
            SEND_STRING("xxxxxxx");
        }
        break;
    }
  return true;
}

#ifdef PIMORONI_TRACKBALL_ENABLE
void pointing_device_task() {
    report_mouse_t mouse_report = pointing_device_get_report();
    if (is_keyboard_master()) {
		bool fast_scroll = (get_highest_layer(layer_state) == _SYM);
		process_mouse(&mouse_report, fast_scroll);
    }
	
	if (host_keyboard_led_state().caps_lock) {
		trackball_set_rgbw(200,100,0,0);
	}
	else {
		switch (get_highest_layer(layer_state)) {
			case _QWERTY:
				 trackball_set_rgbw(150,0,0,0);
				break;
			case _WORKMAN:
				trackball_set_rgbw(130,0,170,0);
				break;
			case _GAMING:
				trackball_set_rgbw(0,0,150,0);
				break;
			case _NAV:
				 trackball_set_rgbw(0,170,130,0);
				break;
			case _SYM:
				 trackball_set_rgbw(0,150,0,0);
				break;
			case _ADJUST:
				 trackball_set_rgbw(0,0,0,150);
				break;
			default:
				trackball_set_rgbw(0,0,0,150);
		}
    }

    if (layer_state_is(_ADJUST)) {
        trackball_set_scrolling(true);
    } else {
        trackball_set_scrolling(false);
    }

    pointing_device_set_report(mouse_report);
    pointing_device_send();
}
#endif


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif
