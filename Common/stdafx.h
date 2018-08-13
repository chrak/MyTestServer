// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#define __TBB_malloc_proxy
#ifdef __TBB_malloc_proxy
#ifdef _DEBUG
#pragma comment (lib, "tbbmalloc_proxy_debug.lib") 
#else
#pragma comment (lib, "tbbmalloc_proxy.lib") 
#endif
#pragma comment (linker, "/include:__TBB_malloc_proxy") 
#include "tbb/tbbmalloc_proxy.h"

#else
#ifdef _DEBUG
#pragma comment (lib, "libtcmalloc_minimal-debug.lib") 
#else
#pragma comment (lib, "libtcmalloc_minimal.lib") 
#endif
#pragma comment (linker, "/include:__tcmalloc") 
#endif


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
