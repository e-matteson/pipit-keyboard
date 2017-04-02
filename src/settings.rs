use options::settings_struct::*;
use std::collections::HashMap;

// thread_local!( pub static SETTINGS: Settings = Settings{
//     // let settings: Settings = Settings{
//     a: 1,
//     h: hashmap![3 => 2 ],
//     u: vec![vec![0,1], vec![2,3]],
//     // v: vec![vec![0,1], vec![2,3]],
//     v: vec2![[4,5], [6,7]],
//     s: vec![10, 11],
// };
// );

thread_local!(
    // TODO are lifetimes handled correctly?
    pub static SETTINGS: Settings<'static> = Settings {
        output_directory           : "pipit-firmware/",
        normal_mode                : "keymaps/dvorak24.kmap",
        onehand_mode               : "keymaps/dvorak24_onehand.kmap",
        chord_delay                : 30,
        held_delay                 : 200,
        debounce_delay             : 15,
        stickymod_key              : "KEY_INSERT",
        enable_audio_feedback      : false,
        debug_messages             : 2,
        enable_unknown_deletion    : true,
        collapse_unknown_deletions : true,

    // hardware-specific options:

    board_name                 : "FEATHER_M0_BLE",
    has_battery                : true,
    battery_level_pin          : 9,
    enable_rgb_led             : true,
    enable_color_feedback      : true,
    rgb_led_pins               : vec![10, 11, 12],
    row_pins                   : vec![1, 0, 19],
    column_pins                : vec![15,16,17,18, 20,21,5,6],

    kmap_format                : vec2![
        [(19,18),(19,17),(19,16),(19,15),    (19,20),(19,21),(19,5),(19,6)],
        [(0,18), (0,17), (0,16), (0,15),     (0,20), (0,21), (0,5), (0,6) ],
        [                (1,18),                     (1,6)                ],
        [         (1,17),(1,16),(1,15),       (1,20),(1,21),(1,5)         ]],


        plains : hashmap![
            "modifierkey_shift" => ("0","MODIFIERKEY_SHIFT"),
            "key_a"             => ("KEY_A","0")
        ],


        macros : hashmap![
            "macro_save" => vec![("KEY_SEMICOLON","MODIFIERKEY_SHIFT"),
                                 ("KEY_W", "0"),
                                 ("KEY_ENTER", "0")],

            "macro_ls" => vec![("KEY_L","0"),
                               ("KEY_S", "0"),
                               ("KEY_ENTER", "0")]
        ],

        special_functions : vec![
            "special_pause",
            "special_delete_word",
        ],

        words : vec2![
            ["abandon"],
            ["difference", "diff"],
            ["<ing", "~ing"],
            ["the"]
        ]
    }
);
