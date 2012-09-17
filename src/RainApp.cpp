#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "DoubleLinkedList.h"
#include "Circle.h"
#include "Square.h"
#include "Rain.h"
#include "Player.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RainApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings*);
  private:
	  void updateAll(DNode*);

	  DNode* rainSentinel;
	  DNode* shapeSentinel, *shape1;
	  DNode* rain1, *rain2;

	  Surface* background_;
	  Surface* sun_;
	  bool drawSun_;

	  int phase;
	  int remainingShapes;

	  uint8_t* surfaceData_, *imgData_, *surfaceData2_, *imgData2_;
	  static const int surfaceSize_ = 1028;
	  static const int appHeight_ = 600;
	  static const int appWidth_ = 800;
};

void RainApp::prepareSettings(Settings* settings){
	settings->setWindowSize(appWidth_,appHeight_);
	settings->setResizable(false);
}

void RainApp::updateAll(DNode* sentinel){
	DNode* current = sentinel->next;

	while(current != sentinel){
		current->shape->update();
		current = current->next;
	}

	// DO NOT PUT DELETE STATEMENT HERE!  BAD THINGS HAPPEN!
}

void RainApp::setup()
{
	drawSun_ = true;

	Surface sun(loadImage( loadResource(RES_SUN) ));
	Surface rain(loadImage( loadResource(RES_RAIN) ));

	background_ = new Surface(surfaceSize_, surfaceSize_, true);

	imgData_ = rain.getData();

	surfaceData_ = (*background_).getData();
	

	for(int y = 0; y < appHeight_; y++){
		for(int x = 0; x < appWidth_; x++){
			int offset1 = 4*(x + y*surfaceSize_);
			int offset2 = 3*(x + y*appWidth_);
			surfaceData_[offset1] = imgData_[offset2];
			surfaceData_[offset1 + 1] = imgData_[offset2 + 1];
			surfaceData_[offset1 + 2] = imgData_[offset2 + 2];
			surfaceData_[offset1 + 3] = 100;
		}
	}

	sun_ = new Surface(surfaceSize_, surfaceSize_, true);
	imgData2_ = sun.getData();
	surfaceData2_ = sun_->getData();

	for(int y = 0; y < appHeight_; y++){
		for(int x = 0; x < appWidth_; x++){
			int offset1 = 4*(x + y*surfaceSize_);
			int offset2 = 3*(x + y*appWidth_);
			surfaceData2_[offset1] = imgData2_[offset2];
			surfaceData2_[offset1 + 1] = imgData2_[offset2 + 1];
			surfaceData2_[offset1 + 2] = imgData2_[offset2 + 2];
			surfaceData2_[offset1 + 3] = 255;
		}
	}

	Shape* dummy = new Shape();
	dummy->square();

	rainSentinel = new DNode();
	shapeSentinel = new DNode();

	rainSentinel->shape = dummy;
	shapeSentinel->shape = dummy;

	phase = 1;
	remainingShapes = 2;

	rain1 = new DNode();
	rain1->shape->rain();
	rain2 = new DNode();
	rain2->shape->rain();

	rainSentinel->next = rain1;
	rain1->next = rain2;
	rain2->next = rainSentinel;
	rainSentinel->prev = rain2;
	rain2->prev = rain1;
	rain1->prev = rainSentinel;

	shape1 = new DNode();
	shape1->shape->square();
	shape1->next = shapeSentinel;
	shapeSentinel->next = shape1;
	shape1->prev = shapeSentinel;
	shapeSentinel->prev = shape1;
	
}

void RainApp::keyDown( KeyEvent event){
	drawSun_ = !drawSun_;

	DNode* temp = shapeSentinel->next;
	if(temp != shapeSentinel){
		shapeSentinel->next = temp->next;
		temp->next->prev = shapeSentinel;
	
		temp->prev = rainSentinel;
		temp->next = rainSentinel->next;
		rainSentinel->next = temp;
		temp->next->prev = temp;
		temp->shape->rain();
	}
}

void RainApp::mouseDown( MouseEvent event )
{
	remainingShapes--;
	Shape* shape_ = new Shape();

	if(event.isLeftDown()){
		shape_->square();
	}
	else{
		shape_->circle();
	}

	shape_->setX(event.getX());
	shape_->setY(event.getY());

	DNode* shapeNode = new DNode();
	shapeNode->shape = shape_;

	shapeNode->prev = shapeSentinel;
	shapeNode->next = shapeSentinel->next;
	shapeSentinel->next = shapeNode;
	
	shapeSentinel->reverseAll();
}

void RainApp::update()
{
	updateAll(rainSentinel);
	updateAll(shapeSentinel);

		DNode* rainDetection = rainSentinel->next;
		DNode* shapeDetection = shapeSentinel->next;

		while(rainDetection != rainSentinel){
			shapeDetection = shapeSentinel->next;

			while(shapeDetection != shapeSentinel){
				shapeDetection->shape->collision(rainDetection->shape);
				shapeDetection = shapeDetection->next;

				if(shapeDetection->prev->shape-> getHP() <= 0 && shapeDetection->prev != shapeSentinel){
					shapeDetection->prev->remove();
				}
			}
			rainDetection = rainDetection->next;

			if(rainDetection->prev->shape-> getHP() <= 0){
				rainDetection->prev->remove();
			}
		}

}

void RainApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	gl::enableAlphaBlending();
	if(drawSun_){
		glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
	}
	else{
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	gl::draw(*background_);
	if(drawSun_){
		gl::draw(*sun_);
	}

	shapeSentinel->drawAll();
	rainSentinel->drawAll();
	
	gl::disableAlphaBlending();
}

CINDER_APP_BASIC( RainApp, RendererGl )
