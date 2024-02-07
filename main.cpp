#include<iostream>
#include<cmath>
#include<SDL2/SDL.h>

using namespace std;

const int width = 200;
const int height = 200;
float ALPHA = 0.01;
float BETA = 0.01;
float THETA = 0.02;

const float PI = 3.14159265;

class square
{
		private:
			//VARIABLES
			struct vector3i
			{
				float x, y, z;
			} point[8], temp[8], center;
			
			SDL_Point fFace[10];	//SDL_RenderDrawPoints needs an SDL_Point pointer to render the points
			SDL_Point sFace[5];
			SDL_Point rFace[8];

			//ROTATIONS
			void rotateZ()
			{
				for(int i = 0; i < 4; i++)
				{
					point[i].x = (temp[i].x - center.x) * cos((ALPHA*PI)/180) - (temp[i].y - center.y) * sin((ALPHA*PI)/180);
					point[i].y = (temp[i].x - center.x) * sin((ALPHA*PI)/180) + (temp[i].y - center.y) * cos((ALPHA*PI)/180);
					point[i].x += center.x;
					point[i].y += center.y;
					temp[i].x = point[i].x;
					temp[i].y = point[i].y;
					fFace[i].x = (int)point[i].x;
					fFace[i].y = (int)point[i].y;
				}	
				fFace[4] = fFace[0];
				for(int i = 5; i < 9; i++)
				{
					point[i - 1].x = (temp[i - 1].x - center.x) * cos((ALPHA*PI)/180) - (temp[i - 1].y - center.y) * sin((ALPHA*PI)/180);
					point[i - 1].y = (temp[i - 1].x - center.x) * sin((ALPHA*PI)/180) + (temp[i - 1].y - center.y) * cos((ALPHA*PI)/180);
					point[i - 1].x += center.x;
					point[i - 1].y += center.y;
					temp[i - 1].x = point[i - 1].x;
					temp[i - 1].y = point[i - 1].y;
					fFace[i].x = (int)point[i - 1].x;
					fFace[i].y = (int)point[i - 1].y;
				}
				fFace[9] = fFace[5];
			}

			void rotateY()
			{
				for(int i = 0; i < 4; i++)
				{
					point[i].x = (temp[i].x - center.x) * cos((BETA*PI)/180) + (temp[i].z - center.z) * sin((BETA*PI)/180);
					point[i].z = (temp[i].z - center.z) * cos((BETA*PI)/180) - (temp[i].x - center.x) * sin((BETA*PI)/180);
					point[i].x += center.x;
					point[i].z += center.z;
					temp[i].x = point[i].x;
					temp[i].z = point[i].z;
					fFace[i].x = (int)point[i].x;
				}
				fFace[4] = fFace[0];
				for(int i = 5; i < 9; i++)
				{
					point[i - 1].x = (temp[i - 1].x - center.x) * cos((BETA*PI)/180) + (temp[i - 1].z - center.z) * sin((BETA*PI)/180);
					point[i - 1].z = (temp[i - 1].z - center.z) * cos((BETA*PI)/180) - (temp[i - 1].x - center.x) * sin((BETA*PI)/180);
					point[i - 1].x += center.x;
					point[i - 1].z += center.z;
					temp[i - 1].x = point[i - 1].x;
					temp[i - 1].z = point[i - 1].z;
					fFace[i].x = (int)point[i - 1].x;
				}
				fFace[9] = fFace[5];
			}

			void rotateX()
			{
				for(int i = 0; i < 4; i++)
				{
					point[i].y = (temp[i].y - center.y) * cos((THETA*PI)/180) - (temp[i].z - center.z) * sin((THETA*PI)/180);
					point[i].z = (temp[i].y - center.y) * sin((THETA*PI)/180) + (temp[i].z - center.z) * cos((THETA*PI)/180);
					point[i].y += center.y;
					point[i].z += center.z;
					temp[i].y = point[i].y;
					temp[i].z = point[i].z;
					fFace[i].y = (int)point[i].y;
				}				
				fFace[4] = fFace[0];
				for(int i = 5; i < 9; i++)
				{
					point[i - 1].y = (temp[i - 1].y - center.y) * cos((THETA*PI)/180) - (temp[i - 1].z - center.z) * sin((THETA*PI)/180);
					point[i - 1].z = (temp[i - 1].y - center.y) * sin((THETA*PI)/180) + (temp[i - 1].z - center.z) * cos((THETA*PI)/180);
					point[i - 1].y += center.y;
					point[i - 1].z += center.z;
					temp[i - 1].y = point[i - 1].y;
					temp[i - 1].z = point[i - 1].z;
					fFace[i].y = (int)point[i - 1].y;
				}
				fFace[9] = fFace[5];

			}
		public:
		//CONSTRUCTOR
		square(int sideSize)
		{
			center.x = width/2;
			center.y = height/2;
			center.z = sideSize/2;

//To use the center point as, well, the center, we can calculate the position of the cube's verteces using the side size 

			fFace[0] = {center.x + sideSize/2, center.y + sideSize/2};
			fFace[1] = {center.x + sideSize/2, center.y - sideSize/2};
			fFace[2] = {center.x - sideSize/2, center.y - sideSize/2};
			fFace[3] = {center.x - sideSize/2, center.y + sideSize/2};
			fFace[4] = fFace[0];
			fFace[5] = fFace[0];
			fFace[6] = fFace[1];
			fFace[7] = fFace[2];
			fFace[8] = fFace[3];
			fFace[9] = fFace[4];

			for(int i = 0; i < 4; i++)
			{
				cout << fFace[i].x << " " << fFace[i].y << " " <<"\n";
				temp[i].x = fFace[i].x;
				temp[i].y = fFace[i].y;
				temp[i].z = 0;
			}
			for(int i = 4; i < 8; i++)
			{
				temp[i].x = fFace[i%4].x;
				temp[i].y = fFace[i%4].y;
				temp[i].z = sideSize;
			}
		}

		//RENDERING SQUARE
		void renderSquare(SDL_Renderer *renderer)
		{
			for(int i = 0; i < 5; i++)
			{
				sFace[i] = fFace[i + 5];
			}

			rFace[0] = fFace[0];
			rFace[1] = fFace[5];
			rFace[3] = fFace[1];
			rFace[2] = fFace[6];
			rFace[4] = fFace[2];
			rFace[5] = fFace[7];
			rFace[7] = fFace[3];
			rFace[6] = fFace[8];

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
			SDL_RenderDrawLines(renderer, fFace, 5);
			SDL_RenderDrawLines(renderer, sFace, 5);
			SDL_RenderDrawLines(renderer, rFace, 8);
			SDL_RenderPresent(renderer);
		}

		//MOVEMENT
		void rotate()
		{
			rotateX();
			rotateY();
			rotateZ();
		}
};

int main()
{
	bool running = 1;
	square mySquare(50);
	SDL_Window *window = SDL_CreateWindow("Cube", 0, 0, width, height, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SOMTEHING'S WRONG, MAN";
		return -1;
	}
	cout << "We gamin'/n";
	while(running)
	{
		//CHECK FOR EVENTS
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.scancode == SDL_SCANCODE_Q)
					running = 0;
			}
		}
		//UPDATE BACKBUFFER
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		mySquare.rotate();
		mySquare.renderSquare(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}
