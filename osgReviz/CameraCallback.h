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
 * \file CameraCallback.h
 * \brief Class for Camera callback
 */

#ifndef CAMERA_CALLBACK_H
#define CAMERA_CALLBACK_H

// OpenSceneGraph includes
#include <osg/Node>
#include <osg/NodeCallback>
#include <osg/MatrixTransform>
#include <osgViewer/View>
#include <osg/io_utils>

// C++ Standard includes
#include <iostream>

/**
 * \class CameraData CameraCallback.h
 * \brief Data for the camera callback
 */
class CameraData : public osg::Referenced
{
public:
    /// TF of the camera
    osg::MatrixTransform* tf;
    /// View that the camera belongs to
    osgViewer::View* view;
};

/**
 * \class CameraCallback CameraCallback.h
 * \brief Class for the camera callback
 */
class CameraCallback : public osg::NodeCallback
{
public:
    /**
     * \brief Constructs a CameraCallback object
     */
    CameraCallback()
    {

    }

    /**
     * \brief Callback operator
     */
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::ref_ptr<CameraData> data =
                dynamic_cast<CameraData*> (node->getUserData());
        if(data) {
            osg::Matrix m = data->view->getCamera()->getInverseViewMatrix();
            data->tf->setMatrix(m);
        }

        traverse(node, nv);
    }

}; // end class CameraCallback

#endif // CAMERA_CALLBACK_H
