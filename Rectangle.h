/**********************************************
 * Rectangle.h
 * This class does basic rectangle collisions and such.
 *
 * Dylan Wilson
 * March 29
 ****************************************************/


#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <cstdlib>
#include <math.h>
using namespace std;

class Rectangle
{
	private:
		float X; //These are used to hold the normal values of the rectangle.
		float Y;
		float Height;
		float Width;

	public:
		Rectangle();
		Rectangle(float x, float y, float height, float width);

		float GetX(); //Used since my previous variables are private
		float GetY();
		float GetHeight();
		float GetWidth();

		void SetX(float x);
		void SetY(float y);
		void SetHeight(float height);
		void SetWidth(float width);

		bool Collision(Rectangle Rec); //Various ways to get collision done.
		bool Collision(Rectangle Rec1,Rectangle Rec2);
		bool Collision(float x, float y);

		bool CircleCollision (Rectangle Circle); //This is a 'step two' from the basic collision, meant only to be used if you know there is a collision. This will tell if there is a circle collision.

		int* SideCollision(Rectangle Rec); //This is used to figure out what side something is hitting the rectangle on. Should only be used AFTER you know there is a collision.

		void UpdateRec(float x, float y); //This is basicly a shortcut to set a new x and y fast.
};
#endif