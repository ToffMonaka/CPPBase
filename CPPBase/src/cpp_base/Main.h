/**
 * @file
 * @brief Mainヘッダーファイル
 */
#pragma once


#if _DEBUG
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11d.lib")
#else
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#endif


#include "constant/ConstantUtil.h"


namespace cpp_base {
INT InitMain(void);
INT CreateMain(const HINSTANCE, const HINSTANCE, const WCHAR *, const INT);
}
