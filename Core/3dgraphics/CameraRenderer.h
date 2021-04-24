#pragma once

#ifdef _3D

	#ifdef _PC
		#include "../pc/3dgraphics/PCCameraRenderer.h"
		typedef PCCameraRenderer CameraRenderer;
	#elif _SPSP
		#include "../psp/3dgraphics/PSPCameraRenderer.h"
		typedef PSPCameraRenderer CameraRenderer;
	#elif _GC
		//#include "../psp/3dgraphics/GCCameraRenderer.h"
		//typedef GCCameraRenderer CameraRenderer;
	#endif

#endif