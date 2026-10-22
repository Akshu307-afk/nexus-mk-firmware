#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif

enum nexus_layers {
    _CODING,
    _MUSIC_TOOLS
};

enum nexus_keycodes {
    NEXUS_MODE = SAFE_RANGE,
    NEXUS_VSCODE,
    NEXUS_ARDUINO,
    NEXUS_VERIFY,
    NEXUS_UPLOAD,
    NEXUS_SPOTIFY,
    NEXUS_CHATGPT,
    NEXUS_BROWSER,
    NEXUS_LOCK,
    NEXUS_DESKTOP,
    NEXUS_NEW_TAB,
    NEXUS_CLOSE_TAB
};

/*
 * Windows-oriented launcher helpers.
 * The normal editing and media keys are standard keyboard reports.
 * Change these app names if your Windows installation uses different
 * command-line aliases. These macros do not launch apps on Linux/macOS.
 */
static void windows_run_command(const char *command) {
    tap_code16(LGUI(KC_R));
    wait_ms(350);
    send_string(command);
    tap_code(KC_ENTER);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* CODING MODE
     * ┌────────┬──────────┬─────────────┐
     * │ MODE   │ VS CODE  │ ARDUINO IDE │
     * ├────────┼──────────┼─────────────┤
     * │ VERIFY │ UPLOAD   │ RUN         │
     * │ SAVE   │ UNDO     │ COPY        │
     * │ PASTE  │ REDO     │ CUT         │
     * └────────┴──────────┴─────────────┘
     */
    [_CODING] = LAYOUT_ortho_4x3(
        NEXUS_MODE,  NEXUS_VSCODE, NEXUS_ARDUINO,
        NEXUS_VERIFY,NEXUS_UPLOAD,  KC_F5,
        C(KC_S),     C(KC_Z),       C(KC_C),
        C(KC_V),     C(KC_Y),       C(KC_X)
    ),

    /* MUSIC + TOOLS MODE
     * ┌────────┬──────────┬────────────┐
     * │ MODE   │ SPOTIFY  │ PLAY/PAUSE │
     * ├────────┼──────────┼────────────┤
     * │ PREV   │ NEXT     │ SCREENSHOT │
     * │ LOCK   │ DESKTOP  │ CHATGPT    │
     * │ BROWSER│ NEW TAB  │ CLOSE TAB  │
     * └────────┴──────────┴────────────┘
     */
    [_MUSIC_TOOLS] = LAYOUT_ortho_4x3(
        NEXUS_MODE,     NEXUS_SPOTIFY, KC_MEDIA_PLAY_PAUSE,
        KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_PSCR,
        NEXUS_LOCK,     NEXUS_DESKTOP, NEXUS_CHATGPT,
        NEXUS_BROWSER,  NEXUS_NEW_TAB, NEXUS_CLOSE_TAB
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case NEXUS_MODE:
            layer_invert(_MUSIC_TOOLS);
            return false;

        case NEXUS_VSCODE:
            windows_run_command("code");
            return false;

        case NEXUS_ARDUINO:
            /* Arduino IDE 2 command alias; edit to "arduino" for IDE 1.x. */
            windows_run_command("arduino-ide");
            return false;

        case NEXUS_VERIFY:
            /* Arduino IDE Verify shortcut */
            tap_code16(C(KC_R));
            return false;

        case NEXUS_UPLOAD:
            /* Arduino IDE Upload shortcut */
            tap_code16(C(KC_U));
            return false;

        case NEXUS_SPOTIFY:
            windows_run_command("https://open.spotify.com");
            return false;

        case NEXUS_CHATGPT:
            windows_run_command("https://chatgpt.com");
            return false;

        case NEXUS_BROWSER:
            windows_run_command("https://www.google.com");
            return false;

        case NEXUS_LOCK:
            tap_code16(LGUI(KC_L));
            return false;

        case NEXUS_DESKTOP:
            tap_code16(LGUI(KC_D));
            return false;

        case NEXUS_NEW_TAB:
            tap_code16(C(KC_T));
            return false;

        case NEXUS_CLOSE_TAB:
            tap_code16(C(KC_W));
            return false;
    }

    return true;
}

/* Counter-clockwise/clockwise: scroll in Coding Mode, volume in Music Mode. */
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_CODING] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_MUSIC_TOOLS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("NEXUS // HUD\n"), false);
    oled_write_P(PSTR("--------------------\n"), false);

    if (get_highest_layer(layer_state) == _MUSIC_TOOLS) {
        oled_write_P(PSTR("MUSIC + TOOLS\n"), false);
        oled_write_P(PSTR("VOL  |  MEDIA  |  PC"), false);
    } else {
        oled_write_P(PSTR("CODING MODE\n"), false);
        oled_write_P(PSTR("VSCODE  /  ARDUINO"), false);
    }
    return false;
}
#endif
