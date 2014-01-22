#pragma once

#define VERSION_MAJOR 0
#define VERSION_MINOR 3
#define VERSION_PATCH 0

// TEMP SETTINGS
#define GAME_TEMP_CONTROLS_SETTING 0

#define _MTS(x) #x
/** Converts a macro to string literal. */
#define MTS(x) _MTS(x)

/** Used instead of _DEBUG because a pre-release test could be built with release target. */
#define _FULL_RELEASE
