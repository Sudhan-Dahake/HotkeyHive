{
    "targets": [
        {
            "target_name": "backend",
            "sources": [
              "backend.cpp",
              "../Backend/Interface/interface.cpp",
              "../Backend/key_remapper/key_remapper.cpp",
              "../Backend/key_utils/key_utils.cpp",
              "../Backend/keyboard_hook/keyboard_hook.cpp",
              "../Backend/utils/utils.cpp",
              ],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include\")",
                "../Frontend/node_modules/node-addon-api"
            ],

            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],

            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
        }
    ]
}