#include<iostream>
#include<raylib.h>
#include<cmath>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

static float cameraOffsetX = 0.0f;
static float cameraOffsetY = 0.0f;

// All the possible States the Simulation can be in
	enum gameStates
	{
		MAIN_MENU,
		CONTROLS,
		GAMEPLAY,
		EARTH_DATA,
		EXIT
	};


class Sun
{
	Texture2D sun;
	float scale;
	float rotation;
	Rectangle source;
	Rectangle dest;
	Vector2 origin;

public:
	Vector2 position;
public:

	Sun()
	{
		sun = LoadTexture("graphics/sun-1.png");
		position.x = GetScreenWidth() / 2;
		position.y = GetScreenHeight() / 2;
		scale = 0.3f;
		rotation = 0.1f;
		source = { 0.0f, 0.0f, (float)sun.width, (float)sun.height };
		dest = {position.x, position.y, sun.width * scale, sun.height * scale};
		origin = {dest.width / 2, dest.height / 2};
	}

	void draw()
	{
		DrawTexturePro(sun, source, dest, origin, rotation, WHITE);
		rotation += 0.03f;
	}

};

class Planets
{
	Vector2 OrbitDistance;
	float scale;
	Texture2D planet;
	float angle;
	float AngularSpeed;
	float rotation;
	Vector2 position;
	Rectangle source;
	Rectangle dest;
	Vector2 origin;
	Sun *sun;

   public:

   	Planets(float OrbitX, float OrbitY, float scale, float AngularSpeed, float rotation, Texture2D planetTex, Sun *s)
   	{
   		this -> OrbitDistance.x = OrbitX;
   		this -> OrbitDistance.y = OrbitY;
   		this -> AngularSpeed = AngularSpeed;
   		this -> scale = scale;
   		this -> rotation = rotation;
   		planet = planetTex;
   		sun = s;
   		angle = 0.0f;
   		source = { 0.0f, 0.0f, (float)planet.width, (float)planet.height };
   	}

   	void Motion()
   	{
   		angle += AngularSpeed;

		// Using cosine for x and sine for y to create a circular orbit
   		position.x = sun -> position.x + OrbitDistance.x * cos(angle);
   		position.y = sun -> position.y + OrbitDistance.y * sin(angle);
   		dest = { position.x, position.y,
                   planet.width * scale,
                   planet.height * scale };
        origin = { dest.width / 2, dest.height / 2 };
   	}

   	void draw()
   	{
   		sun-> draw();

		// Draw the orbit ellipse
		DrawEllipseLines(sun->position.x, sun->position.y, OrbitDistance.x, OrbitDistance.y, GRAY);

		DrawTexturePro(planet, source, dest, origin, rotation, WHITE);
		rotation += 0.5f;
	}


};

// Function to Read the nasa Data file
void ReadData(float &ra, float &dec, float &delta)
{
    ifstream file("earth_data_minimal.txt");
    if(!file)
    {
        cout << "Error occurred while opening file" << endl;
        ra = dec = delta = 0.0f; 
        return;
    }

    if (!(file >> ra >> dec >> delta))
    {
        cout << "Error reading data from file" << endl;
        ra = dec = delta = 0.0f;
    }

    file.close();
}

// Function to add buttons
bool DrawButton(const char* text, int x, int y, int fontSize, Sound buttonSound, Vector2 mousePos, gameStates &currentState, gameStates targetState)
{
    int width = MeasureText(text, fontSize);
    Rectangle buttonRect = { x - 10, y - 10, width + 20, fontSize + 20 };

    // Hover effect
    Color buttonColor;
	if(CheckCollisionPointRec(mousePos, buttonRect))
	{
		buttonColor = SKYBLUE;
	}
	else
	{
		buttonColor = GRAY;
	}

    DrawRectangle(x - 10, y - 10, width + 20, fontSize + 20, buttonColor);
    DrawText(text, x, y, fontSize, BLACK);

    // check collison
    if (CheckCollisionPointRec(mousePos, buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        PlaySound(buttonSound);
        currentState = targetState;
        return true;
    }

    return false;
}




int main()
{
	const int ScreenWidth = 1366;
	const int ScreenHeight = 690;

	InitWindow(ScreenWidth, ScreenHeight, "SolarSystem");
	InitAudioDevice();

	//calling Read File function
	system("python generate_minimal_data.py"); // Running python script to generate data file
	float ra, dec, delta;
	ReadData(ra, dec, delta);

	gameStates currentState = MAIN_MENU;

	// Set the Key Camera Values
	Camera2D camera = {0};
	camera.target = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f }; 
	camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f }; 
	camera.rotation = 0.0f;
	camera.zoom = 0.16f;


	Sun sun;
	// Load Background Music
	Music bgm = LoadMusicStream("Audio/BackgroundMusic.ogg");
	PlayMusicStream(bgm);
	SetMusicVolume(bgm, 0.5f);
	bool IsMusicPaused = false;

	// Button Sound
	Sound buttonSound = LoadSound("Audio/beep.wav");

	// Load All Planets Texture
	Texture2D earth = LoadTexture("graphics/earth.png");
	Texture2D mercury = LoadTexture("graphics/mercury.png");
	Texture2D venus = LoadTexture("graphics/venus.png");
	Texture2D mars = LoadTexture("graphics/mars.png");
	Texture2D jupiter = LoadTexture("graphics/jupiter.png");
	Texture2D saturn_rings = LoadTexture("graphics/saturn-rings.png");
	Texture2D saturn = LoadTexture("graphics/saturn.png");
	Texture2D uranus = LoadTexture("graphics/uranus.png");
	Texture2D neptune = LoadTexture("graphics/neptune.png");

	// Push The Planets objects to vector
	vector<Planets> planets;

	planets.push_back(Planets(528, 480, 0.4f, 0.005, 0.5f, mercury, &sun)); 
	planets.push_back(Planets(680, 680, 0.2f, 0.0035, 0.5f, venus, &sun));  
	planets.push_back(Planets(1050, 1050, 0.5f, 0.003, 0.5f, earth, &sun));   
	planets.push_back(Planets(1480,1350, 0.3f, 0.003, 0.5f, mars, &sun)); 
	planets.push_back(Planets(1750,1750, 0.8f, 0.0028, 0.5f, jupiter, &sun)); 
	planets.push_back(Planets(2150,2150, 0.6f, 0.0027, 0.5f, saturn_rings, &sun));
	planets.push_back(Planets(2150,2150, 0.7f, 0.0027, 0.5f, saturn, &sun));
	planets.push_back(Planets(2650,2650, 0.8f, 0.0026, 0.5f, uranus, &sun));
	planets.push_back(Planets(3000,3000, 0.6f, 0.0025, 0.5f, neptune, &sun));


	SetTargetFPS(60);

	// Main Simulation Loop
	while(!WindowShouldClose())
	{
		Vector2 menuView = {sun.position.x - 2800, sun.position.y};
		Vector2 gameplayView = sun.position;
		Vector2 mousePos = GetMousePosition();
		float transitionSpeed = 0.04f;

		if(currentState == EXIT)
		{
			CloseWindow();
			return 0;
		}

		// Repeat Music if it ends
		if(!IsMusicStreamPlaying(bgm) && !IsMusicPaused)
		{
			PlayMusicStream(bgm);
			IsMusicPaused = !IsMusicPaused;
		}
		UpdateMusicStream(bgm);
		
		// M to Mute Music
		if(IsKeyPressed(KEY_M))
		{
			PlaySound(buttonSound);
			PauseMusicStream(bgm);
			IsMusicPaused = !IsMusicPaused;
		}

		// Smooth Zoom transition from GamePlay State To Menu State
		if(currentState == MAIN_MENU)
		{
			float zoomTarget = 0.16f;
			float zoomSpeed = 0.04f * transitionSpeed;

			if (fabs(camera.zoom - zoomTarget) > 0.001f) 
			{
				if(camera.zoom > zoomTarget)
					camera.zoom -= zoomSpeed;
				else
					camera.zoom += zoomSpeed;
			}
			else
			{
				camera.zoom = zoomTarget;
			}
			camera.target.x += (menuView.x - camera.target.x) * transitionSpeed;
    		camera.target.y += (menuView.y - camera.target.y) * transitionSpeed;
		}

		// Smooth camera movement
		else if (currentState == GAMEPLAY)
		{
			camera.target.x += ((gameplayView.x + cameraOffsetX) - camera.target.x) * transitionSpeed;
			camera.target.y += ((gameplayView.y + cameraOffsetY) - camera.target.y) * transitionSpeed;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);

		// Draw Planets And Sun
		for(int i = 0; i < planets.size(); i++)
		{
			planets[i].Motion();
			planets[i].draw();
		}

		if(currentState == GAMEPLAY)
		{
			float MoveSpeed = 14.0f;
			// Zooming functionality
			if (IsKeyDown(KEY_UP)) camera.zoom += 0.01f; 
			if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.01f;
	
			if (camera.zoom < 0.1f) camera.zoom = 0.1f; 
			if (camera.zoom > 2.0f) camera.zoom = 2.0f; 

			// Camera Movement
			if (IsKeyDown(KEY_A)) cameraOffsetX -= MoveSpeed; 
			if (IsKeyDown(KEY_D)) cameraOffsetX += MoveSpeed;

			if (IsKeyDown(KEY_W)) cameraOffsetY -= MoveSpeed;
			if (IsKeyDown(KEY_S)) cameraOffsetY += MoveSpeed;
		
			if(cameraOffsetX < -5000) cameraOffsetX = -5000; 
			if(cameraOffsetX > 5000) cameraOffsetX = 5000;

			if (cameraOffsetY < -5000) cameraOffsetY = -5000;
			if (cameraOffsetY > 5000) cameraOffsetY = 5000;
		}
		EndMode2D();

		// Displaying the Return to Menu button 
		if(currentState == GAMEPLAY)
		{
			DrawButton("Return to Menu", 40, GetScreenHeight() - 70, 20, buttonSound, mousePos, currentState, MAIN_MENU);
		}
		
		if(currentState == MAIN_MENU)
		{
			const char* title = "Solar System \nSimulation";
			const char* startText = "Press to Start";
			const char* ExitText = "Press to Exit";
			const char* ControlText = "Controls and Tips";
			const char* earthDataText = "Live Earth Data";

			// Title Text
			int titleFontSize = 45;
			int titleWidth = MeasureText("Solar System Simulation", titleFontSize);
			int titleX = 200;
			int titleY = 200;
			DrawText(title, titleX, titleY, titleFontSize, SKYBLUE);
			DrawLine(titleX, titleY + 100, titleWidth, titleY + 100, WHITE);

			// Start Button
			DrawButton(startText, 200, 350, 20, buttonSound, mousePos, currentState, GAMEPLAY);

			// Exit Button
			DrawButton(ExitText, 200, 600, 20, buttonSound, mousePos, currentState, EXIT);

		   // Control Button 
		   DrawButton(ControlText, 200, 450, 20, buttonSound, mousePos, currentState, CONTROLS);
			
		   // Earth Data Button
		   DrawButton(earthDataText, 200, 400, 20, buttonSound, mousePos, currentState, EARTH_DATA);

		}

		if(currentState == CONTROLS)
		{
			const char* title = "Controls and Tips";
			const char* tipsTitle = "Tips";
			const char* ReturnText = "Return to Menu";

			// Title Text
			int titleFontSize = 35;
			int titleWidth = MeasureText("Controls and Tips", titleFontSize);
			int titleX = 100;
			int titleY = 50;
			DrawText(title, titleX, titleY, titleFontSize, GRAY);
			DrawLine(titleX, titleY + 50, titleWidth + 80, titleY + 50, WHITE);

			// Controls Guide
			int textFontSize = 19;
			int textX = 120;
			int textY = titleY + 80;
			int lineSpacing = 35;

			DrawText("- Zoom In / Out:        UP / Down Arrows", textX, textY, textFontSize, LIGHTGRAY);
			DrawText("- Movement:     WASD keys", textX, textY + lineSpacing, textFontSize, LIGHTGRAY);
			DrawText("- Start Simulation:  Click Start Button", textX, textY + 2 * lineSpacing, textFontSize, LIGHTGRAY);
			DrawText("- View Planet Info:  Click on a Planet", textX, textY + 3 * lineSpacing, textFontSize, LIGHTGRAY);
			DrawText("- Mute Music:       M Key", textX, textY + 4 * lineSpacing, textFontSize, LIGHTGRAY);
			DrawText("- Exit:                  ESC Key", textX, textY + 5 * lineSpacing, textFontSize, LIGHTGRAY);

			// Tips Section
			int tipsTitleY = textY + 6 * lineSpacing;
			DrawText(tipsTitle, textX - 20, tipsTitleY + 20, titleFontSize - 5, GRAY);
			DrawLine(textX - 20, tipsTitleY + 55, textX + 200, tipsTitleY + 55, WHITE);

			DrawText("- Zoom out fully to view all planets.", textX, tipsTitleY + 80, textFontSize, LIGHTGRAY);
			DrawText("- Rotate and observe orbits for realism.", textX, tipsTitleY + 110, textFontSize, LIGHTGRAY);
			DrawText("- Future updates will add planet facts!", textX, tipsTitleY + 140, textFontSize, LIGHTGRAY);

			// Return Menu Button
			DrawButton(ReturnText, 40, GetScreenHeight() - 70, 20, buttonSound, mousePos, currentState, MAIN_MENU);
		}

		if(currentState == EARTH_DATA)
		{
			const char* title = "Live Earth Data";
			const char* ReturnText = "Return to Menu";

			// Title Text
			int titleFontSize = 35;
			int titleWidth = MeasureText(title, titleFontSize);
			int titleX = 100;
			int titleY = 50;
			DrawText(title, titleX, titleY, titleFontSize, SKYBLUE);
			DrawLine(titleX, titleY + 50, titleWidth + 90, titleY + 50, WHITE);

			// Data Display Section
			int textFontSize = 19;
			int textX = 120;
			int textY = titleY + 80;
			int lineSpacing = 35;

			DrawText("- Right Ascension (RA):", textX, textY, textFontSize, LIGHTGRAY);
			DrawText(TextFormat("%.2f deg", ra), textX + 300, textY, textFontSize, RAYWHITE);

			DrawText("- Declination (DEC):", textX, textY + lineSpacing, textFontSize, LIGHTGRAY);
			DrawText(TextFormat("%.2f deg", dec), textX + 300, textY + lineSpacing, textFontSize, RAYWHITE);

			DrawText("- Distance:", textX, textY + 2 * lineSpacing, textFontSize, LIGHTGRAY);
			DrawText(TextFormat("%.2f AU", delta), textX + 300, textY + 2 * lineSpacing, textFontSize, RAYWHITE);

			// Explanatory Tips
			int tipsY = textY + 4 * lineSpacing;
			DrawText("RA/DEC:   Earth position in the sky.", textX, tipsY, textFontSize - 2, GRAY);
			DrawText("Distance:   Current distance from observer in AU.", textX, tipsY + lineSpacing, textFontSize - 2, GRAY);

			// Return Menu Button
			DrawButton(ReturnText, 40, GetScreenHeight() - 70, 20, buttonSound, mousePos, currentState, MAIN_MENU);
			
		}

		EndDrawing();
	}

	// Unload all the textures and music
	UnloadTexture(earth);
	UnloadTexture(mercury);
	UnloadTexture(venus);
	UnloadTexture(mars);
	UnloadTexture(jupiter);
	UnloadTexture(saturn_rings);
	UnloadTexture(saturn);
	UnloadTexture(uranus);
	UnloadTexture(neptune);
	UnloadMusicStream(bgm);
	UnloadSound(buttonSound);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}