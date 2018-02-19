//
// Created by Nikos R. Katsipoulakis on 2/7/18.
//

#ifndef _DEBUG_
#define _DEBUG_

#ifdef _DM_
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) {}
#endif

#endif //_DEBUG_
