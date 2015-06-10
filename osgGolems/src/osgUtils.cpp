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
#include "osgUtils.h"
#include "Axes.h"

// OpenSceneGraph includes
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>

osgViewer::View* osgGolems::createView(int x, int y, int w, int h, osg::Node* scene)
{
    osgViewer::View* view = new osgViewer::View;
    osgGA::OrbitManipulator* cameraManipulator = new osgGA::OrbitManipulator();
    cameraManipulator->setAllowThrow(false);
    view->setCameraManipulator(cameraManipulator);
    view->getCamera()->setClearColor(osg::Vec4(0.5, 0.5, 0.5, 0.5));
    view->setUpViewInWindow(x, y, w, h);
    view->addEventHandler(new osgViewer::StatsHandler);
    if (scene == scene) {
        view->setSceneData(scene);
    }
    return view;
}
