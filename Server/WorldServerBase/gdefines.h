/** Contains global metadata defines in addition to CommonLib/metadata.h */

#pragma once

#include <CommonLib/metadata.h>

#if VERSION_PATCH == 0
#define RAW_APP_VERSION MTS(VERSION_MAJOR)"."MTS(VERSION_MINOR)
#else
#define RAW_APP_VERSION MTS(VERSION_MAJOR)"."MTS(VERSION_MINOR)"."MTS(VERSION_PATCH)
#endif

// Application Information
#ifdef _FULL_RELEASE
#define APP_NAME "SquareCubed World Server"
#define APP_VERSION RAW_APP_VERSION
#define APP_AUTHOR "EdgeWorks Games™"
#define STR_SUPPORT "Supported release version!"
#else
#define APP_NAME "SquareCubed World Server"
#define APP_VERSION RAW_APP_VERSION"-dev"
#define APP_AUTHOR "EdgeWorks Games™"
#define STR_SUPPORT "Unsupported development version!"
#endif