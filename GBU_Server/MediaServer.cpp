
#include "stdafx.h"
#include "MediaServer.h"
#include <list>

deque<GBUVideoFrame> g_media_buffer;

void push_media(GBUVideoFrame frame)
{
	if (g_media_buffer.size() > 50) {
		//OutputDebugString(TEXT("Media Buffer Overflow!\n"));
		return;
	}
	g_media_buffer.push_back(frame);
}

bool pop_media(GBUVideoFrame* frame)
{
	if (g_media_buffer.size() > 0 && frame != NULL)
	{
		GBUVideoFrame front = g_media_buffer.front();
		frame->frame = front.frame;
		frame->camindex = front.camindex;
		
		g_media_buffer.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}

void test()
{
	//dbtest();
	//return;

	VideoCapture camera_frame = VideoCapture("rtsp://test:test1234@1.233.158.28:554/Streaming/Channels/101?transportmode=unicast");

	int keydown = 0;
	Mat frame;
	while (keydown != 'q' && keydown != 'Q') {

		if (camera_frame.read(frame)) {
			imshow("test", frame);
		}

		keydown = waitKey(10);
	}
	destroyWindow("test");

	waitKey();

	return;
}
