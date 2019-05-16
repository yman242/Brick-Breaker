/**********************************************
 * Brick.h
 * This class is used to hold basic brick information.
 * Built to make mass using bricks easier.
 *
 * Dylan Wilson
 * March 29
 ****************************************************/

#include "DragonFireSDK.h"
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#include "Rectangle.h"

class Brick
{
	public:
		int BrickImage;
		int BrickView;
		Rectangle BrickRec;
		bool Dead;

		Brick()
		{

		}

		Brick(float x, float y, float height, float width)
		{
			BrickImage = ImageAdd("Images/Block.png");
			BrickView = ViewAdd(BrickImage,x,y);

			BrickRec.UpdateRec(x,y);
			BrickRec.SetHeight(height);
			BrickRec.SetWidth(width);

			Dead = false;
		}

		void BrickUpdate(float x, float y)
		{
			BrickRec.UpdateRec(ViewGetx(BrickView),ViewGety(BrickView));
		}

};