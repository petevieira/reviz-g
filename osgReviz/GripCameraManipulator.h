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
 * \file GripCameraManipulator.h
 * \brief Camera manipulator class that subclasses osgGA::OrbitManipulator.
 * It sets up desired behavior for robot simulator.
 */

#ifndef GRIP_CAMERA_MANIPULATOR_H
#define GRIP_CAMERA_MANIPULATOR_H

// OpenSceneGraph includes
#include <osgGA/OrbitManipulator>

/**
 * \namespace osgReviz
 * \brief Namespace for all the classes that are only dependent upon OpenSceneGraph
 */
namespace osgReviz {

/**
 * \class GripCameraManipulator GripCameraManipulator.h
 * \brief Camera manipulator class that subclasses osgGA::OrbitManipulator.
 * It sets up desired behavior for robot simulator.
 */
class GripCameraManipulator : public osgGA::OrbitManipulator
{
public:

    /**
     * \brief Constructor for GRIPCameraManipulator class
     */
    GripCameraManipulator();

    /**
     * \brief Destructor for GRIPCameraManipulator class
     */
    virtual ~GripCameraManipulator();

    /**
     * \brief Set the camera manipulator's center of rotation
     * \param center osg::Vec3 specifying x,y,z coordinates of center of rotation
     * \return void
     */
    void setCenter(osg::Vec3 center);

protected:

    /**
     * \brief keyboard and mouse event handler
     */
    virtual bool handleKeyDown( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
    /**
     * \brief keyboard and mouse event handler
     */
    virtual bool handleKeyUp( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
    /**
     * \brief keyboard and mouse event handler
     */
    virtual bool handleMouseMove( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
    /**
     * \brief a boolean member variable to trace whether a keyboard is pressed
     */
    bool _keyPressed; //true = pressed, false = released
    /**
     * \brief a member variable to trace the pressed key
     */
    int _pressedKey;

    float _currentX;
    float _previousX;
    float _currentY;
    float _previousY;

    bool _keyboardMouseBinding; // true - when keyboard and mouse are used for camera control

}; // end class CameraManipulator

} // end namespace osgReviz

#endif // GRIP_CAMERA_MANIPULATOR_H
