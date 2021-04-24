#pragma once

//#ifdef _VECTOR
	#ifdef _PC
		#include "../pc/vectorgraphics/PCWidgetRenderer.h"
		typedef PCWidgetRenderer WidgetRenderer;
	#elif _SPSP
		#include "../psp/vectorgraphics/PSPWidgetRenderer.h"
		typedef PSPWidgetRenderer WidgetRenderer;
	#elif _GC
		#include "../gc/vectorgraphics/GCWidgetRenderer.h"
		typedef GCWidgetRenderer WidgetRenderer;
	#endif
//#endif
/*#elif _3D
	#ifdef _PC
		#include "../pc/3dgraphics/PCWidgetRenderer.h"
		typedef PCWidgetRenderer WidgetRenderer;
	#elif _SPSP
		#include "../psp/vectorgraphics/PSPWidgetRenderer.h"
		typedef PSPWidgetRenderer WidgetRenderer;
	#elif _GC
		#include "../gc/vectorgraphics/GCWidgetRenderer.h"
		typedef GCWidgetRenderer WidgetRenderer;
	#endif
#endif
	*/