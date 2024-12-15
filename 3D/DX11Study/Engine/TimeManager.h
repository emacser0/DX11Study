#pragma once

class FTimeManager
{
	DECLARE_SINGLE(FTimeManager);

public:
	void Init();
	void Update();

	uint32 GetFPS() { return FPS; }
	float GetDeltaTime() { return DeltaTime; }

private:
	uint64	Frequency = 0;
	uint64	PrevCount = 0;
	float	DeltaTime = 0.f;

private:
	uint32	FrameCount = 0;
	float	FrameTime = 0.f;
	uint32	FPS = 0;
};

