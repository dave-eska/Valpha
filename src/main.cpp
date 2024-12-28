#include "global_variable.hpp"

#include "gameplay.hpp"

int main(){
	SetTraceLogLevel(LOG_NONE);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(1920, 1080, "Melieska");

	Gameplay* gameplay = new Gameplay();

	isDebugging = false;
	isTyping = false;

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		if(IsKeyPressed(KEY_X))
			isDebugging = !isDebugging;

		gameplay->Update(GetFrameTime());

		BeginDrawing();

		ClearBackground(GRAY);

		gameplay->Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
