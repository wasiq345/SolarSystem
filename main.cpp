#include<iostream>
#include<raylib.h>
#include<cmath>
using namespace std;


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
		sun = LoadTexture("graphics/sun.png");
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
		rotation += 0.4f;
	}

};

class Planet 
{
	Vector2 OrbitDistance;
	float scale;
	Texture2D earth;
	float angle;
	float AngularSpeed;
	float rotation;
	Vector2 position;
	Rectangle source;
	Rectangle dest;
	Vector2 origin;
	Sun sun;

   public:
   	Planet()
   	{
   		earth = LoadTexture("graphics/earth.png");
	   	OrbitDistance.x = 270.0f;
   		OrbitDistance.y = 220.0f;
   		scale = 0.04f;
   		angle = 0.0f;
   		AngularSpeed = 0.01f;
   		rotation = 0.1f;
   		source = { 0.0f, 0.0f, (float)earth.width, (float)earth.height };
        origin = { dest.width / 2, dest.height / 2 };
   	}

   	void Motion()
   	{
   		angle += AngularSpeed;

   		position.x = sun.position.x + OrbitDistance.x * cos(angle);
   		position.y = sun.position.y + OrbitDistance.y * sin(angle);
   		dest = { position.x, position.y,
                   earth.width * scale,
                   earth.height * scale };
   	}

   	void draw()
   	{
   		sun.draw();

		DrawTexturePro(earth, source, dest, origin, rotation, WHITE);
		rotation += 0.5f;
	}


};


int main()
{
	const int ScreenWidth = 1366;
	const int ScreenHeight = 690;

	InitWindow(ScreenWidth, ScreenHeight, "SolarSystem");
	Planet earth;

	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		earth.Motion();

		earth.draw();


		EndDrawing();
	}

	CloseWindow();
	return 0;
}