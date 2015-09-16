
#include "stdafx.h"

struct GBUVideoFrame {
	Mat frame;
	int camindex;
};

void test();

void push_media(GBUVideoFrame frame);
bool pop_media(GBUVideoFrame* frame);