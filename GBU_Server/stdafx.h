// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <opencv2\opencv.hpp>
#ifdef _DEBUG
#pragma comment (lib, "opencv_world300d.lib")
#else
#pragma comment (lib, "opencv_world300.lib")
#endif

#include "sqlite\sqlite3.h"

using namespace cv;
using namespace std;
