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
 * \file ViewerWidget.h
 * \brief Class that is an osgViewer::CompositeViewer as a QWidget
 */

#ifndef VIEWER_WIDGET_H
#define VIEWER_WIDGET_H

// QT includes
#include <QtCore/QTimer>
#include <QtGui/QGridLayout>

// OpenSceneGraph includes
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/OrbitManipulator>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>
#include <osg/io_utils>
#include "osgUtils.h"

// Standard Library includes
#include <iostream>

/**
 * \class ViewerWidget ViewerWidget.h
 * \brief Class which inherits from QWidget and osgViewer::CompositeViewer.
 * This class creates a osgQt::GraphicsWindowQt and puts it inside a composite viewer
 */
class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{

public:
    /**
     * \brief Constructor for ViewerWidget class
     */
    ViewerWidget(osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::AutomaticSelection);

    /**
     * \brief Add a osgQt::GraphicsWindowQt widget to the ViewerWidget
     * \param camera An osg::Camera pointer
     * \param scene An osg::Node pointer which is the scene to display
     * \return QWidget pointer
     */
    QWidget* addViewWidget(osg::Camera* camera, osg::Node* scene);

    /**
     * \brief Creates a camera for the viewer
     * \param x x-coordinate of the upper-left corner of the window
     * \param y y-coordinate of the upper-left corner of the window
     * \param w Width of the window
     * \param h Height of the window
     * \param name Name of the window
     * \param windowDecoration Whether or not to add window decoration
     * \return void
     */
    osg::Camera* createCamera(int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false);

    /**
     * \brief Gets the view matrix
     * \return osg::Matrixd
     */
    osg::Matrixd getViewMatrix();

    /**
     * \brief Sets the viewMatrix of the specified view
     * \param i View to change the view matrix of
     * \param m New view matrix
     * \return void
     */
    void setViewMatrix(uint i, osg::Matrixd m);

    /**
     * \brief Sets the matrix of the camera manipulator to front view
     * \return void
     */
    void setToFrontView();

    /**
     * \brief Sets the matrix of the camera manipulator to top view
     * \return void
     */
    void setToTopView();

    /**
     * \brief Sets the matrix of the camera manipulator to side view
     * \return void
     */
    void setToSideView();

    /**
     * \brief Sets the matrix of the specified view
     * \param newMatrix osg::Matrix reference to set the camera to
     * \param viewNum The view of which to set the camera matrix
     * \return void
     */
    void setCameraMatrix(osg::Matrix& newMatrix, uint viewNum=0);

    /**
     * \brief Gets the camera matrix of the specified view
     * \param viewNum View from which to get the camera matrix.
     * \return osg::Matrix object representing the camera matrix
     */
    osg::Matrix getCameraMatrix(uint viewNum=0);

    /**
     * \brief Adds an osg node to the scene in the view specified by the user
     * \param node osg::Node pointer to add to the scene
     * \param viewNum View to which to add the node
     * \return void
     */
    void addNodeToScene(osg::Node *node, uint viewNum=0);

    /**
     * \brief Removes an osg node from the scene in the view specified by the user
     * \param node osg::Node pointer to remove from the scene
     * \param viewNum View from which to remove the node
     * \return void
     */
    void removeNodeFromScene(osg::Node *node, uint viewNum=0);

    /**
     * \brief Sets background color of the view number "viewNum" with the
     * "color". If an invalid view number is provided an error message is printed
     * and no change occurs to any view.
     * \param color osg::Vec4 RGBA (red, green blue, alpha) color vector.
     * \param viewNum View number to change the background color of.
     * \return void
     */
    void setBackgroundColor(const osg::Vec4& color, uint viewNum=0);

    /**
     * \brief Gets the camera manipulator for a certain view, specified
     * by it's view number "viewNum".
     * \param viewNum Number of the view of which to get the camera manipulator.
     * \return osgGA::CameraManipulator pointer.
     */
    osgGA::CameraManipulator* getCameraManipulator(uint viewNum=0);

    /**
     * \brief Sets the the camera the in the specified view to its home position
     * \param viewNum View for which to set the camera to home position
     * \return void
     */
    void setCameraToHomePosition(uint viewNum=0);

    /**
     * \brief Adds a grid to the viewer
     * \param width Width of the entire grid in meters
     * \param depth Depth of the entire grid in meters
     * \param gridSize Length of side of each grid square in meters
     * \return void
     */
    void addGrid(uint width, uint depth, uint gridSize);

    /**
     * \brief Renders the scene
     * \param event QPaint event
     * \return void
     */
    virtual void paintEvent( QPaintEvent* event )
    { frame(); }

    /**
     * \brief takes a screenshot of the view widget
     * \return void
     */
    QImage takeScreenshot();

protected:

    // Timer for update the interface
    QTimer _timer;

    /**
     * \brief Determines if the input view number is valid,
     * i.e., Does that view exist in the ViewWidget, since the
     * ViewWidget is a CompositeViewer and therefore can hold more
     * than one view.
     * \param viewNum Number of the view to validate
     * \return bool Whether or not the view number exists
     */
    bool viewNumIsValid(uint viewNum);
}; // end class ViewerWidget

#endif // VIEWER_WIDGET_H
