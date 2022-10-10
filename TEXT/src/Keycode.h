#pragma once

// From glfw3.h
// TOE is the name of an engine I'm working on so I just copied/pasted the code from this project

/* The unknown key */
#define TOE_KEY_UNKNOWN            -1

/* Printable keys */
#define TOE_KEY_SPACE              32
#define TOE_KEY_APOSTROPHE         39  /* ' */
#define TOE_KEY_COMMA              44  /* , */
#define TOE_KEY_MINUS              45  /* - */
#define TOE_KEY_PERIOD             46  /* . */
#define TOE_KEY_SLASH              47  /* / */
#define TOE_KEY_0                  48
#define TOE_KEY_1                  49
#define TOE_KEY_2                  50
#define TOE_KEY_3                  51
#define TOE_KEY_4                  52
#define TOE_KEY_5                  53
#define TOE_KEY_6                  54
#define TOE_KEY_7                  55
#define TOE_KEY_8                  56
#define TOE_KEY_9                  57
#define TOE_KEY_SEMICOLON          59  /* ; */
#define TOE_KEY_EQUAL              61  /* = */
#define TOE_KEY_A                  65
#define TOE_KEY_B                  66
#define TOE_KEY_C                  67
#define TOE_KEY_D                  68
#define TOE_KEY_E                  69
#define TOE_KEY_F                  70
#define TOE_KEY_G                  71
#define TOE_KEY_H                  72
#define TOE_KEY_I                  73
#define TOE_KEY_J                  74
#define TOE_KEY_K                  75
#define TOE_KEY_L                  76
#define TOE_KEY_M                  77
#define TOE_KEY_N                  78
#define TOE_KEY_O                  79
#define TOE_KEY_P                  80
#define TOE_KEY_Q                  81
#define TOE_KEY_R                  82
#define TOE_KEY_S                  83
#define TOE_KEY_T                  84
#define TOE_KEY_U                  85
#define TOE_KEY_V                  86
#define TOE_KEY_W                  87
#define TOE_KEY_X                  88
#define TOE_KEY_Y                  89
#define TOE_KEY_Z                  90
#define TOE_KEY_LEFT_BRACKET       91  /* [ */
#define TOE_KEY_BACKSLASH          92  /* \ */
#define TOE_KEY_RIGHT_BRACKET      93  /* ] */
#define TOE_KEY_GRAVE_ACCENT       96  /* ` */
#define TOE_KEY_WORLD_1            161 /* non-US #1 */
#define TOE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define TOE_KEY_ESCAPE             256
#define TOE_KEY_ENTER              257
#define TOE_KEY_TAB                258
#define TOE_KEY_BACKSPACE          259
#define TOE_KEY_INSERT             260
#define TOE_KEY_DELETE             261
#define TOE_KEY_RIGHT              262
#define TOE_KEY_LEFT               263
#define TOE_KEY_DOWN               264
#define TOE_KEY_UP                 265
#define TOE_KEY_PAGE_UP            266
#define TOE_KEY_PAGE_DOWN          267
#define TOE_KEY_HOME               268
#define TOE_KEY_END                269
#define TOE_KEY_CAPS_LOCK          280
#define TOE_KEY_SCROLL_LOCK        281
#define TOE_KEY_NUM_LOCK           282
#define TOE_KEY_PRINT_SCREEN       283
#define TOE_KEY_PAUSE              284
#define TOE_KEY_F1                 290
#define TOE_KEY_F2                 291
#define TOE_KEY_F3                 292
#define TOE_KEY_F4                 293
#define TOE_KEY_F5                 294
#define TOE_KEY_F6                 295
#define TOE_KEY_F7                 296
#define TOE_KEY_F8                 297
#define TOE_KEY_F9                 298
#define TOE_KEY_F10                299
#define TOE_KEY_F11                300
#define TOE_KEY_F12                301
#define TOE_KEY_F13                302
#define TOE_KEY_F14                303
#define TOE_KEY_F15                304
#define TOE_KEY_F16                305
#define TOE_KEY_F17                306
#define TOE_KEY_F18                307
#define TOE_KEY_F19                308
#define TOE_KEY_F20                309
#define TOE_KEY_F21                310
#define TOE_KEY_F22                311
#define TOE_KEY_F23                312
#define TOE_KEY_F24                313
#define TOE_KEY_F25                314
#define TOE_KEY_KP_0               320
#define TOE_KEY_KP_1               321
#define TOE_KEY_KP_2               322
#define TOE_KEY_KP_3               323
#define TOE_KEY_KP_4               324
#define TOE_KEY_KP_5               325
#define TOE_KEY_KP_6               326
#define TOE_KEY_KP_7               327
#define TOE_KEY_KP_8               328
#define TOE_KEY_KP_9               329
#define TOE_KEY_KP_DECIMAL         330
#define TOE_KEY_KP_DIVIDE          331
#define TOE_KEY_KP_MULTIPLY        332
#define TOE_KEY_KP_SUBTRACT        333
#define TOE_KEY_KP_ADD             334
#define TOE_KEY_KP_ENTER           335
#define TOE_KEY_KP_EQUAL           336
#define TOE_KEY_LEFT_SHIFT         340
#define TOE_KEY_LEFT_CONTROL       341
#define TOE_KEY_LEFT_ALT           342
#define TOE_KEY_LEFT_SUPER         343
#define TOE_KEY_RIGHT_SHIFT        344
#define TOE_KEY_RIGHT_CONTROL      345
#define TOE_KEY_RIGHT_ALT          346
#define TOE_KEY_RIGHT_SUPER        347
#define TOE_KEY_MENU               348

/* Mouse buttons */
#define TOE_MOUSE_BUTTON_1         0
#define TOE_MOUSE_BUTTON_2         1
#define TOE_MOUSE_BUTTON_3         2
#define TOE_MOUSE_BUTTON_4         3
#define TOE_MOUSE_BUTTON_5         4
#define TOE_MOUSE_BUTTON_6         5
#define TOE_MOUSE_BUTTON_7         6
#define TOE_MOUSE_BUTTON_8         7
#define TOE_MOUSE_BUTTON_LAST      TOE_MOUSE_BUTTON_8
#define TOE_MOUSE_BUTTON_LEFT      TOE_MOUSE_BUTTON_1
#define TOE_MOUSE_BUTTON_RIGHT     TOE_MOUSE_BUTTON_2
#define TOE_MOUSE_BUTTON_MIDDLE    TOE_MOUSE_BUTTON_3

#define TOE_PRESS GLFW_PRESS
#define TOE_RELEASE GLFW_RELEASE