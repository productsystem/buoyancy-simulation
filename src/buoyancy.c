#include "buoyancy.h"

float GetSubmergedHeight(Box *b, float waterLevel){
    if(b->pos.y + b->size.y < waterLevel){
        return 0;
    }

    float submerged = b->pos.y + b->size.y - waterLevel;
    if(b->pos.y + b->size.y - waterLevel > b->size.y){
        submerged = b->size.y;
    }
    return submerged;
}

float BuoyancyForce(Box *b, float waterlevel){
    float vol = b->size.x * GetSubmergedHeight(b,waterlevel) * PIXEL_SCALE_FACTOR * PIXEL_SCALE_FACTOR;
    return DENSITY * vol * GRAVITY;
}

bool IsSubmerged(Box *b, float waterLevel) {
    return b->pos.y + b->size.y > waterLevel;
}

void UpdateBuoyancy(Box *b, float *waterLevel, float dt){
    float weight = b->mass * GRAVITY;
    float buoyancy = BuoyancyForce(b,*waterLevel);
    float viscous = 0.0f;
    if (IsSubmerged(b, *waterLevel)) {
        viscous = (b->vel) * -DAMPING_COEFF;
    } 
    else {
        viscous = 0;
    }
    float totalForce = buoyancy - weight + viscous;
    float acc = totalForce/b->mass;

    b->vel += acc * dt;
    b->pos.y -= b->vel * dt;

    if (b->pos.y < 0) {
        b->pos.y = 0;
        b->vel = 0;
    }

    if (b->pos.y + b->size.y > GetScreenHeight()) {
        b->pos.y = GetScreenHeight() - b->size.y;
        b->vel = 0;
    }

    float fluidVol = b->size.x * GetSubmergedHeight(b,*waterLevel) * PIXEL_SCALE_FACTOR *PIXEL_SCALE_FACTOR;
    *waterLevel = BASE_WATER_LEVEL - fluidVol/(GetScreenWidth() * WATER_Z * PIXEL_SCALE_FACTOR * PIXEL_SCALE_FACTOR);
}

void DebugText(Box *b, float *waterLevel){
    float submergedHeight = GetSubmergedHeight(b, *waterLevel) * PIXEL_SCALE_FACTOR;
    float submergedVolume = b->size.x * submergedHeight * PIXEL_SCALE_FACTOR;
    float buoyancy = BuoyancyForce(b, *waterLevel);
    float weight = b->mass * GRAVITY;
    float viscous = (b->vel) * -DAMPING_COEFF;
    float netForce = buoyancy - weight + viscous;

    int y = 10;
    int spacing = 20;

    DrawText(TextFormat("Box Density: %.2f kg/m^2", b->density), 10, y, 20, DARKGRAY);
    y += spacing;
    DrawText(TextFormat("Box Volume: %.2f m^2", b->size.x * b->size.y), 10, y, 20, DARKGRAY);
    y += spacing;
    DrawText(TextFormat("Box Mass: %.2f kg", b->mass), 10, y, 20, DARKGRAY);
    y += spacing;

    DrawText(TextFormat("Water Level in Y: %.2f", *waterLevel), 10, y, 20, BLUE);
    y += spacing;
    DrawText(TextFormat("Submerged Height: %.2f", submergedHeight), 10, y, 20, BLUE);
    y += spacing;
    DrawText(TextFormat("Submerged Volume: %.2f", submergedVolume), 10, y, 20, BLUE);
    y += spacing;

    DrawText(TextFormat("Buoyant Force: %.2f N", buoyancy), 10, y, 20, DARKGREEN);
    y += spacing;
    DrawText(TextFormat("Weight: %.2f N", weight), 10, y, 20, MAROON);
    y += spacing;
    DrawText(TextFormat("Viscous Force: %.2f N", viscous ), 10, y, 20, BLACK);
    y += spacing;
    DrawText(TextFormat("Net Force: %.2f N", netForce), 10, y, 20, BLACK);
    y += spacing;
}