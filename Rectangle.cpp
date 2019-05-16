#include "Rectangle.h"

Rectangle::Rectangle()
{
	X = 0.0f;
	Y = 0.0f;
	
	Height = 1.0f;
	Width = 1.0f;

}

Rectangle::Rectangle(float x, float y, float height, float width)
{
	X = x;
	Y = y;
	Height = height;
	Width = width;

}

float Rectangle::GetX()
{
	return X;
}

float Rectangle::GetY()
{
	return Y;
}

float Rectangle::GetHeight()
{
	return Height;
}

float Rectangle::GetWidth()
{
	return Width;
}

void Rectangle::SetX(float x)
{
	X = x;
}

void Rectangle::SetY(float y)
{
	Y = y;
}

void Rectangle::SetHeight(float height)
{
	if(height>0) //Height has to exist.
		Height = height;
}

void Rectangle::SetWidth(float width)
{
	if(width>0) //Width has to exist
		Width = width;
}

void Rectangle::UpdateRec(float x, float y)
{
	X = x;
	Y = y;
}

bool Rectangle::Collision(Rectangle Rec) //The most basic collision, this will test Rec to see if any of it's points are inside this rectangle
{
	if((Rec.GetX() <X+Width && Rec.GetX()>X) && (Rec.GetY()<Y+Height && Rec.GetY()>Y))
	{
		return true;
	}
	else if((Rec.GetX() + Rec.GetWidth()<X+Width && Rec.GetX() + Rec.GetWidth()>X) && (Rec.GetY()<Y+Height && Rec.GetY()>Y))
	{
		return true;
	}
	else if((Rec.GetX()<X+Width && Rec.GetX()>X) && (Rec.GetY() +Rec.GetHeight() <Y+Height && Rec.GetY() + Rec.GetHeight()>Y))
	{
		return true;
	}
	else if((Rec.GetX() + Rec.GetWidth()<X+Width && Rec.GetX() + Rec.GetWidth()>X) && (Rec.GetY() +Rec.GetHeight() <Y+Height && Rec.GetY() + Rec.GetHeight()>Y))
	{
		return true;
	}

	return false;
}

bool Rectangle::Collision(Rectangle Rec1, Rectangle Rec2) //This is under construction
{
	return false;
}

bool Rectangle::Collision(float x, float y) //This does a collision with a point
{
	if((x <X+Width && x>X) && (y<Y+Height && y>Y))
	{
		return true;
	}

	return false;
}

bool Rectangle::CircleCollision(Rectangle Circle) //This is used to test the second rectangle as a circle.
{
	int Radius = Circle.GetWidth()/2;

	int MidX = X + Width/2;

	int MidY = Y +Height/2;

	int CircleMidX = Circle.GetX() + Circle.GetWidth()/2;

	int CircleMidY = Circle.GetY() + Circle.GetHeight()/2;


	if(CircleMidX>X && CircleMidX < X + Width && CircleMidY < Y) //Top Area
	{
		return true;
	}
	else if(CircleMidX>X && CircleMidX < X + Width && CircleMidY > Y + Height) //Bottom Area
	{
		return true;
	}
	else if(CircleMidY > Y && CircleMidY < Y + Height && CircleMidX> X + Width) //Right Area
	{
		return true;
	}
	else if(CircleMidY > Y && CircleMidY < Y + Height && CircleMidX<X) //Left Area
	{
		return true;
	}
	else if(CircleMidX > X + Width && CircleMidY < Y)//Top Right
	{
		if(sqrt(pow(int(X + Width-CircleMidX),2.0f) + pow(int(Y - CircleMidY),2.0)) <= Radius /*+ Rectangle Radius*/)
		{
			return true;
		}
		return false;
	}
	else if(CircleMidX < X && CircleMidY < Y) // Top Left
	{
		if(sqrt(pow(int(X-CircleMidX),2.0f) + pow(int(Y - CircleMidY),2.0)) <= Radius /*+ Rectangle Radius*/)
		{
			return true;
		}
		return false;
	}
	else if(CircleMidX > X + Width && CircleMidY > Y + Height) //Bottom Right
	{
		if(sqrt(pow(int(X + Width-CircleMidX),2.0f) + pow(int(Y + Height - CircleMidY),2.0)) <= Radius /*+ Rectangle Radius*/)
		{
			return true;
		}
		return false;
	}
	else if(CircleMidX < X && CircleMidY > Y + Height) //Bottom Left
	{
		if(sqrt(pow(int(X-CircleMidX),2.0f) + pow(int(Y + Height - CircleMidY),2.0)) <= Radius /*+ Rectangle Radius*/)
		{
			return true;
		}
		return false;
	}

	return true;
}

int* Rectangle::SideCollision(Rectangle Rec) //This class takes the middle of rec and finds out which of the eight areas around a rectangle it's in. Returns a int array of 2, position 0 being what the x should bounce and 1 being what the y should bounce.
{
	float MidX = Rec.GetX() + Rec.GetWidth()/2;
	float MidY = Rec.GetY() + Rec.GetHeight()/2;

	int* pointer;


	if(MidX>=X && MidX <= X + Width && MidY <= Y) //Top Area
	{
		int dummy [2] = {0,-1};
		pointer = dummy;
		return pointer;
	}
	else if(MidX>=X && MidX <= X + Width && MidY >= Y + Height) //Bottom Area
	{
		int dummy [2] = {0,1};
		pointer = dummy;
		return pointer;
	}
	else if(MidY >= Y && MidY <= Y + Height && MidX>= X + Width) //Right Area
	{
		int dummy [2] = {1,0};
		pointer = dummy;
		return pointer;
	}
	else if(MidY >= Y && MidY <= Y + Height && MidX<=X) //Left Area
	{
		int dummy [2] = {-1,0};
		pointer = dummy;
		return pointer;
	}
	else if(MidX > X + Width && MidY < Y)//Top Right
	{
		int dummy [2] = {1,-1};
		pointer = dummy;
		return pointer;
	}
	else if(MidX < X && MidY < Y) // Top Left
	{
		int dummy [2] = {-1,-1};
		pointer = dummy;
		return pointer;
	}
	else if(MidX > X + Width && MidY > Y + Height) //Bottom Right
	{
		int dummy [2] = {1,1};
		pointer = dummy;
		return pointer;
	}
	else if(MidX < X && MidY > Y + Height) //Bottom Left
	{
		int dummy [2] = {-1,1};
		pointer = dummy;
		return pointer;
	}

	int dummy [2] = {0,0};
	pointer = dummy;
	return pointer;
}