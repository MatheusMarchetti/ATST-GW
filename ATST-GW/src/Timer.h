#pragma once

class Timer
{
public:
	Timer() {}
	void Start() { start = std::chrono::high_resolution_clock::now(); }
	void End() { end = std::chrono::high_resolution_clock::now(); }
	void Now() { now = std::chrono::system_clock::now(); }
	std::chrono::duration<double> Duration() { return end - start; }

public:
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::system_clock::time_point now;

} timer;