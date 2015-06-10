/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

// Local includes
#include "ViewerWidget.h"
#include "osgUtils.h"
#include "Axes.h"
#include "CameraCallback.h"
#include "GripCameraManipulator.h"
#include "Grid.h"

// OpenSceneGraph includes
#include <osg/io_utils>
#include <osg/ShapeDrawable>


void ViewerWidget::addGrid(uint width, uint depth, uint gridSize)
{
    osg::Geode* gridGeode = new osg::Geode();
    osgGolems::Grid* grid = new osgGolems::Grid(width, depth, gridSize, osg::Vec4(.3, .3, .3, .5));
    gridGeode->addDrawable(grid);
    gridGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF
                                                   | osg::StateAttribute::PROTECTED);
    addNodeToScene(gridGeode);
}

ViewerWidget::ViewerWidget(osgViewer::ViewerBase::ThreadingModel threadingModel) : QWidget()
{
//    switch(threadingModel) {
//        case 0: std::cerr << "SingleThreaded" << std::endl; break;
//        case 1: std::cerr << "CullDrawThreadPerContext" << std::endl; break;
//        case 2: std::cerr << "ThreadPerContext" << std::endl; break;
//        case 3: std::cerr << "DrawThreadPerContext" << std::endl; break;
//        case 4: std::cerr << "CullThreadPerCameraDrawThreadPerContext" << std::endl; break;
//    }
    /// regardless of the threadingModel passed, we are using SingleThreaded for now, which does not cause problems yet.
    /// In some platforms, auto-selected threading model causes some problems
    setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
    this->setRunFrameScheme(osgViewer::CompositeViewer::ON_DEMAND);

    // Create scene data
//    osg::Node* sceneData = getSceneData();
    osg::Group* sceneData = new osg::Group;

    // Create view widget with camera and scene data
    QWidget* widget1 = addViewWidget(createCamera(0,0,100,100), sceneData);

    // Create QLayout and add view widget to it. Then set it as the main layout
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(widget1);
    setLayout(layout);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(10);
}

QWidget* ViewerWidget::addViewWidget(osg::Camera* camera, osg::Node* scene)
{
    osgViewer::View* view = new osgViewer::View;
    view->setCamera(camera);

    // This needs to be added to set up the camera's stateset properly,
    // in order to override OpenGL default settings to enable things like
    // depth test, etc, otherwise it will use OpenGL defaults.
    view->getCamera()->getOrCreateStateSet()->setGlobalDefaults();
    
    this->addView(view);

    view->setSceneData(scene);

    view->addEventHandler(new osgViewer::StatsHandler);

    osgGolems::GripCameraManipulator* cameraManipulator = new osgGolems::GripCameraManipulator();
    view->setCameraManipulator(cameraManipulator);

//    osgGolems::myKeyboardEventHandler* keyboardHandler = new osgGolems::myKeyboardEventHandler();
//    view->getEventHandlers().push_front(keyboardHandler);

    osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
    return gw ? gw->getGLWidget() : NULL;
}

osg::Camera* ViewerWidget::createCamera(int x, int y, int w, int h, const std::string& name, bool windowDecoration)
{
    // Get display settings instance in order to set our traits
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();

    // Create GraphicsContext traits and set them.
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowName = name;
    traits->windowDecoration = windowDecoration;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
    camera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 0.0));
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f);
    return camera.release();
}

osg::Matrixd ViewerWidget::getViewMatrix()
{
    osg::Matrixd m = getView(0)->getCameraManipulator()->getMatrix();
    return m;
}

void ViewerWidget::setViewMatrix(uint i, osg::Matrixd m)
{
    if (viewNumIsValid(i)) {
        this->getView(i)->getCameraManipulator()->setByMatrix(m);
        osg::ref_ptr<osgGA::OrbitManipulator> c =
            dynamic_cast<osgGA::OrbitManipulator*>(this->getView(i)->getCameraManipulator());
        c->setCenter(osg::Vec3f(0, 0, 0));
    }
}

void ViewerWidget::setToTopView()
{
    osg::Matrixd m;
    m.makeRotate(M_PI/2, osg::Vec3(0, 0, 1));
    m.setTrans(0, 0, 1);
    this->setCameraMatrix(m);
    // 0  1  0  0
    //-1  0  0  0
    // 0  0  1  0
    // 0  0  1  1
}

void ViewerWidget::setToFrontView()
{
    osg::Matrixd m;
    m.makeRotate(M_PI/2, osg::Vec3(0, 0, 1));
    m.postMultRotate(osg::Quat(M_PI/2, osg::Vec3(0, 1, 0)));
    m.setTrans(1, 0, 0);
    this->setCameraMatrix(m);
    // 0  1  0  0
    // 0  0  1  0
    // 1  0  0  0
    // 1  0  0  1
}

void ViewerWidget::setToSideView()
{
    osg::Matrixd m;
    m.makeRotate(M_PI, osg::Vec3(0, 0, 1));
    m.postMultRotate(osg::Quat(-M_PI/2, osg::Vec3(1, 0, 0)));
    m.setTrans(0, 1, 0);
    this->setCameraMatrix(m);
    //-1  0  0  0
    // 0  0  1  0
    // 0  1  0  0
    // 0  1  0  1
}

void ViewerWidget::setCameraMatrix(osg::Matrix& newMatrix, uint viewNum)
{
    if (viewNumIsValid(viewNum)) {
        this->getCameraManipulator(viewNum)->setByMatrix(newMatrix);
        osg::ref_ptr<osgGA::OrbitManipulator> c =
            dynamic_cast<osgGA::OrbitManipulator*>(this->getCameraManipulator(viewNum));
        c->setCenter(osg::Vec3f(0, 0, 0));
    }
}

osg::Matrix ViewerWidget::getCameraMatrix(uint viewNum)
{
    if (viewNumIsValid(viewNum)) {
        return this->getCameraManipulator(viewNum)->getMatrix();
    } else {
        osg::Matrix m;
        m.identity();
        return m;
    }
}

void ViewerWidget::addNodeToScene(osg::Node* node, uint viewNum)
{
    if (node != node || !(viewNumIsValid(viewNum))) {
        std::cerr << "Error! Invalid node" << std::endl;
        return;
    }

    osg::Group* scene = this->getView(viewNum)->getSceneData()->asGroup();

    if (scene != scene) {
        std::cerr << "Error! Can not convert from osg::Node to osg::Group."
                  << std::endl;
    } else {
        scene->addChild(node);
    }
}

void ViewerWidget::removeNodeFromScene(osg::Node* node, uint viewNum)
{
    if (node != node || !(viewNumIsValid(viewNum))) {
        std::cerr << "Error! Invalid node" << std::endl;
        return;
    }

    osg::Group* scene = this->getView(viewNum)->getSceneData()->asGroup();
    if (scene != scene) {
        std::cerr << "Error! Can not convert from osg::Node to osg::Group."
                  << std::endl;
    } else {
        scene->removeChild(node);
    }
}

void ViewerWidget::setBackgroundColor(const osg::Vec4 &color, uint viewNum)
{
    // If the view number is valid, set the background color the view's camera
    if (viewNumIsValid(viewNum)) {
        this->getView(viewNum)->getCamera()->setClearColor(color);
    }
}

osgGA::CameraManipulator* ViewerWidget::getCameraManipulator(uint viewNum)
{
    // If the view number is valid, get its camera manipulator,
    // otherwise return a NULL pointer
    if (viewNumIsValid(viewNum)) {
        return this->getView(viewNum)->getCameraManipulator();
    } else {
        return NULL;
    }
}

void ViewerWidget::setCameraToHomePosition(uint viewNum)
{
    if (viewNumIsValid(viewNum)) {
        this->getCameraManipulator(viewNum)->home(1.0);
    }
}

bool ViewerWidget::viewNumIsValid(uint viewNum)
{
    // If viewNum exists, return true, otherwise report error and return false
    if (viewNum >= 0 && viewNum < this->getNumViews()) {
        return true;
    } else {
        fprintf(stderr, "Error! Requested view #%d, but only %d views exist\n", viewNum, this->getNumViews());
        fprintf(stderr, "Valid view #'s are 0 - %d\n", this->getNumViews() - 1);
        return false;
    }
}

QImage ViewerWidget::takeScreenshot()
{
    osgViewer::View* view = this->getView(0);
    osg::Camera* camera = view->getCamera();
    osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
    QGLWidget* glw = gw->getGLWidget();
    //QSize cur_size = glw->size();
    //glw->resize(1280, 712);
    //glw->update();
    //std::cerr<<glw->size().width()<<" "<<glw->size().height()<<std::endl;
    QImage screenshot = glw->grabFrameBuffer();
    //glw->resize(cur_size);
    return screenshot;
}
