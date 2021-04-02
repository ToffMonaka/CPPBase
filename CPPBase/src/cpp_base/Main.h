/**
 * @file
 * @brief Mainヘッダーファイル
 */
#pragma once


#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msacm32.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11d.lib")
#else
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#endif
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "libogg.lib")
#pragma comment(lib, "libvorbis.lib")
#pragma comment(lib, "libvorbisfile.lib")


#include "constant/ConstantUtil.h"


namespace cpp_base {
INT InitMain(void);
INT CreateMain(const HINSTANCE, const HINSTANCE, const WCHAR *, const INT);
}
