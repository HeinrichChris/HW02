#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "DoubleLinkedList.h"
#include "Circle.h"
#include "Square.h"
#include "Rain.h"
#include "Player.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RainApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
  private:
	  DNode* rainSentinel;
	  DNode* shapeSentinel;
	  //DNode* destroyedSentinel;
	  //Player player; // no player in this version
	  Surface background;

	  int phase;
	  int remainingShapes;

	  static const int appHeight_ = 600;
	  static const int appWidth_ = 800;
};

void RainApp::setup()
{
	background loadImage(loadResource(RES_BACKGROUND));

	//player = new Player();

	rainSentinel = new DNode;
	shapeSentinel = new DNode;
	//destroyedSentinel = new DNode;

	phase == 1;
	remainingShapes = 2;
}

void RainApp::mouseDown( MouseEvent event )
{
	if(remainingShapes > 0 && phase % 2 == 1){
		remainingShapes--;
		Shape* shape_;

		if(event.isLeftDown()){
			shape_ = (Shape*) new Square();
		}
		else{
			shape_ = (Shape*) new Circle();
		}

		shape_->setX(event.getX());
		shape_->setY(event.getY());

		DNode* shapeNode = new DNode;
		shapeNode->shape = shape_;

		shapeSentinel->addNext(*shapeNode);
	}
}

void RainApp::update()
{
	rainSentinel->updateAll();
	shapeSentinel->updateAll();

	// if sunny
	if(phase % 2 == 1){
		if(remainingShapes <= 0){
			phase++;
			remainingShapes = phase * 5;
		}
	}
	else{
		//player.update();

		if(remainingShapes > 0){
			DNode* rain = new DNode();
			rain->shape = (Shape*) new Rain();
			rain->shape->setX(rand() % appWidth_);
			rain->shape->setY(0);

			rainSentinel->addNext(*rain);
		}

		DNode* rainDetection = rainSentinel->next;
		DNode* shapeDetection = shapeSentinel->next;

		while(rainDetection != rainSentinel){
			shapeDetection = shapeSentinel->next;

			while(shapeDetection != shapeSentinel){
				shapeDetection->shape->collision(rainDetection->shape);
				shapeDetection = shapeDetection->next;

				if(shapeDetection->prev->shape-> getHP() <= 0 && shapeDetection->prev != shapeSentinel){
					//destroyedSentinel->addNext(*(shapeDetection->prev);
					shapeDetection->prev->remove();
				}
			}
			rainDetection = rainDetection->next;

			if((rainDetection->prev->shape-> getHP() <= 0 || rainDetection->prev->shape->getLoc()[1] < appHeight_) && rainDetection->prev != rainSentinel){
				rainDetection->prev->remove();
			}
		}

		if(rainSentinel->next == rainSentinel){
			phase++;
		}

	}

}

void RainApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	gl::draw(background);

	shapeSentinel->drawAll();
	rainSentinel->drawAll();
	//destroyedSentinel->drawAll();
	
	//player.draw();
}

CINDER_APP_BASIC( RainApp, RendererGl )
