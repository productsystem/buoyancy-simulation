#pragma once
#include "raylib.h"

#define GRAVITY 9.8f
#define DENSITY 1000.0f
#define DT 1.0f/60.0f
#define BASE_WATER_LEVEL 400.0f
#define PIXEL_SCALE_FACTOR 0.01f
#define DAMPING_COEFF 50
#define WATER_Z 0.5f

typedef struct{
    Vector2 pos;
    Vector2 size;
    float vel;
    float density;
    float mass;
} Box;

float GetSubmergedHeight(Box *b, float waterLevel);
float BuoyancyForce(Box *b, float waterlevel);
void UpdateBuoyancy(Box *b, float *waterLevel, float dt);
void DebugText(Box *b, float *waterLevel);