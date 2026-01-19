#ifndef MIRRORS_FIX_H
#define MIRRORS_FIX_H

namespace MirrorsFix {
	//void			sub_595230(int *_mirrors);
	void __fastcall ProcessMirrors(int *_this, int* EDX);
	void			injectHooks();
}

#endif
