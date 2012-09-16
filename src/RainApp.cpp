#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "DoubleLinkedList.h"
#include "Circle.h"
#include "Square.h"
#include "Rain.h"

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
	  DNode* destroyedSentinel;
	  Player player;
	  Surface background;
};

void RainApp::setup()
{
	background = loadImage(loadResource(RES_BACKGROUND));

	player = new Player();

	rainSentinel = new DNode;
	shapeSentinel = new DNode;
	destroyedSentinel = new DNode;
}

void RainApp::mouseDown( MouseEvent event )
{
}

void RainApp::update()
{
	rainSentinel->updateAll();
	shapeSentinel->updateAll();

	player.update();

	// TODO : collision detects
}

void RainApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	gl::draw(background);

	rainSentinel->drawAll();
	shapeSentinel->drawAll();
	destroyedSentinel->drawAll();
	
	player.draw();
}

CINDER_APP_BASIC( RainApp, RendererGl )
