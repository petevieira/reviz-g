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
 * \file Picker.h
 * \brief Class that subclasses osgGA::GUIEventHandler to implement picking of objects
 * in the scenegraph
 */

#ifndef PICKER_H
#define PICKER_H

// OpenSceneGraph includes
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
/**
 * \namespace osgReviz
 * \brief Namespace for all the classes that are only dependent upon OpenSceneGraph
 */
namespace osgReviz {

/**
 * \class Picker Picker.h
 * \brief Class that subclasses osgGA::GUIEventHandler to implement picking of objects
 * in the 3D scenegraph
 */
class Picker : public osgGA::GUIEventHandler
{
public:

  /**
   * \brief Constructor for Picker.
   */
  Picker(osgViewer::View* view);

  ~Picker();

  bool handle(const osgGA::GUIEventAdapter& eventAdapter, osgGA::GUIActionAdapter& actionAdapter);

  virtual void pick(const osgGA::GUIEventAdapter& eventAdapter);


protected:

  osgViewer::View* _view;

}; // end class Picker

} // end namespace osgReviz

#endif // PICKER_H
