#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "defs.h"
#define assert(expr) do { \
			if (!(expr)) { \
				printf("Assertion failed: %s, file %s, line %d\n", #expr, __FILE__, __LINE__); \
				while (1) \
					; \
			} \
		    } while (0)
#endif
