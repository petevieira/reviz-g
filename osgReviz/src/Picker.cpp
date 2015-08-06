/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

/**
 * \file Picker.cpp
 * \brief Class that subclasses osgGA::GUIEventHandler to implement picking of objects
 * in the scenegraph
 */

// Standard headers
#include <iostream>

// OpenSceneGraph includes

// Local headers
#include "../Picker.h"

using namespace osgReviz;


Picker::Picker(osgViewer::View* view)
{
  _view = view;
}

Picker::~Picker()
{}

bool Picker::handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter)
{
  switch (eventAdapter.getEventType()) {
    case osgGA::GUIEventAdapter::PUSH: {
      _view = dynamic_cast<osgViewer::View*>(&actionAdapter);
      if (_view) {
        pick(eventAdapter);
        return false;
      }
    }
    default:
      return false;
  }
}

void Picker::pick(const osgGA::GUIEventAdapter& eventAdapter)
{
  osgUtil::LineSegmentIntersector::Intersections intersections;

  if (_view->computeIntersections(eventAdapter, intersections)) {
    for (osgUtil::LineSegmentIntersector::Intersections::iterator intersection = intersections.begin(); intersection != intersections.end(); ++intersection) {
      osg::ref_ptr<osg::Drawable> drawable = intersection->drawable;
      if (drawable.valid()) {
      }
    }
  }
}
