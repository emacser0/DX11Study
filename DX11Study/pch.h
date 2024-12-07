#pragma once

#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <cassert>

#include <windows.h>
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DirectXTex.inl"

#include "SimpleMath.h"
#include "SimpleMath.inl"

#include "Types.h"
#include "Structs.h"
#include "Values.h"

using namespace DirectX;
using namespace Microsoft::WRL;
namespace Math = SimpleMath;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef __DEBUG
#pragma comment(lib, "DirectXTex.d.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

#define CHECK(p) assert(SUCCEEDED(p))
