#pragma once
#define pi 3.14159
#define fov (3.14159 / 3)
#define halfFov (3.14159 / 6)
#define screenSizeX 1200
#define screenSizeY 600
#define numRays (screenSizeX / 10)
#define spriteSize 32
const float dist = numRays / (2 * tanf(halfFov * pi / 180)) * 2;
const float FloorLines = 0.4 * screenSizeY;