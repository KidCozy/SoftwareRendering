#pragma once
#include "stdafx.h"

using namespace std;

namespace linecolor {
	enum BGCOLOR {
		BG_RED,
		BG_GREEN,
		BG_BLUE,
	};
	enum FGCOLOR {
		FG_RED,
		FG_GREEN,
		FG_BLUE,
		FG_BLACK,
	};
}

using namespace linecolor;

void ChangeLineColor(BGCOLOR BG, FGCOLOR FG);
