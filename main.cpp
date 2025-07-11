#include<iostream>
#include<raylib.h>
#include<cmath>
#include<vector>
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
		rotation += 0.08f;
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

		DrawTexturePro(planet, source, dest, origin, rotation, WHITE);
		rotation += 0.5f;
	}


};


int main()
{
	const int ScreenWidth = 1366;
	const int ScreenHeight = 690;

	InitWindow(ScreenWidth, ScreenHeight, "SolarSystem");

	Camera2D camera = {0};
	camera.target = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f }; 
	camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f }; 
	camera.rotation = 0.0f;
	camera.zoom = 1.0f; 

	Sun sun;
	Texture2D earth = LoadTexture("graphics/earth.png");
	Texture2D mercury = LoadTexture("graphics/mercury.png");
	Texture2D venus = LoadTexture("graphics/venus.png");
	Texture2D mars = LoadTexture("graphics/mars.png");
	float scaleFactor = 0.4f;
	vector<Planets> planets;

	planets.push_back(Planets(130, 130, 0.15f, 0.005, 0.5f, mercury, &sun)); 
	planets.push_back(Planets(210, 210, 0.08f, 0.0035, 0.5f, venus, &sun));  
	planets.push_back(Planets(310, 310, 0.038f, 0.003, 0.5f, earth, &sun));   
	planets.push_back(Planets(430,430, 0.15f, 0.003, 0.5f, mars, &sun)); 

	SetTargetFPS(60);

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);

		for(int i = 0; i < planets.size(); i++)
		{
			planets[i].Motion();
			planets[i].draw();
		}

		if (IsKeyDown(KEY_UP))
		{
			camera.zoom += 0.01f; 
		}    

		if (IsKeyDown(KEY_DOWN))
		{
			camera.zoom -= 0.01f;
		}   

		if (camera.zoom < 0.1f) 
		{
			camera.zoom = 0.1f;
		}

		if (camera.zoom > 5.0f)
		{
			camera.zoom = 5.0f;
		} 


		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}