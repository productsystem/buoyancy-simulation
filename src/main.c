#include "raylib.h"
#include "buoyancy.h"

int main()
{
	InitWindow(800,800, "Buoyancy Simulation");
	SetTargetFPS(240);

	Box box = {350,200,100,50,0,500,0};
	box.mass = box.size.x * box.size.y * box.density * PIXEL_SCALE_FACTOR * PIXEL_SCALE_FACTOR;
	float waterLevel = BASE_WATER_LEVEL;

	while(!WindowShouldClose())
	{
		UpdateBuoyancy(&box,&waterLevel,DT);
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawFPS(0,0);
			DebugText(&box, &waterLevel);
			DrawLine(0, (int)waterLevel, 800, (int)waterLevel, BLUE);
			DrawRectangleV(box.pos,box.size,BLACK);
		EndDrawing();
	}
	CloseWindow();
}