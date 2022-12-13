#pragma once

#include <chrono>
#include <poll.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <sys/stat.h>
#include <string.h>
#include <thread>

#include "core/libcamera_encoder.hpp"
#include "output/output.hpp"

using namespace std::placeholders;

class videoStream
{
private:
	bool m_running;
	std::thread m_thread;
	unsigned int m_argc;
	char** m_argv;
	int get_key_or_signal(VideoOptions const *options, pollfd p[1]);
	int get_colourspace_flags(std::string const &codec);
	void event_loop(LibcameraEncoder &app);
	void videoStreamInit(int argc, char *argv[]);
public:
	videoStream(int argc = 0, char *argv[] = nullptr);
	void start(int argc = 0, char *argv[] = nullptr);
	void stop();
	bool isRunning() const;
	~videoStream();
};