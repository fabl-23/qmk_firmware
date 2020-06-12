/* Copyright 2019 Ryota Goto
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

#define _BL 0
#define _FL 1
#define _RL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT_ortho_6x4( /* Base Layer */
		KC_ESC,  KC_BSPC, KC_BSPC, MO(_FL), \
		KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
		KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
		KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
		KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
		KC_P0,   KC_P0,   KC_PDOT, KC_PENT  \
  ),

	[_FL] = LAYOUT_ortho_6x4( /* Function Layer */
		_______, LSFT(KC_8), LSFT(KC_9), _______, \
		_______, _______, BL_TOGG, BL_DEC,  \
		_______, _______, _______, _______, \
		_______, _______, _______, BL_INC,  \
		_______, _______, _______, _______, \
		KC_SPC,  _______, _______, MO(_RL)  \
  ),

  	[_RL] = LAYOUT_ortho_6x4( /* Reset Layer */
		_______, _______, _______, _______, \
		_______, _______, _______, _______, \
		_______, _______, _______, _______, \
		_______, _______, _______, _______, \
		_______, _______, _______, _______, \
		RESET,   _______, _______, _______  \
  ),
};

layer_state_t layer_state_set_user(layer_state_t state, bool process_record_user) {
	
	uint8_t ledLevelDiff = 4;
	uint8_t lastLedLevel = get_backlight_level();
	
    switch (get_highest_layer(state)) {
	case _BL:
        breathing_disable();
		
		if (doSwitch == true) {
			backlight_level(lastLedLevel + ledLevelDiff);
		}

        break;
	case _FL:
		if (lastLedLevel != 0) {
			backlight_level(lastLedLevel - ledLevelDiff);
		}
		
		if (record->event.pressed) {
			doSwitch = true;
		}
		else {
			doSwitch = false;
		}

		break;
	case _RL:
        breathing_toggle();
        break;
    }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
