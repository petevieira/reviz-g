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
 * \file GripTab.h
 * \brief GripTab declares virtual functions and contains some useful member pointers to
 * objects in the main window of grip. Users making plugins need to subclass this class
 */

#ifndef GRIPTAB_H
#define GRIPTAB_H

// Local includes
#include "TreeViewReturn.h"
#include "ViewerWidget.h"

// Qt includes
#include <QtGui/QDockWidget>
#include <QtCore/QtPlugin>


/**
 * \class GripTab GripTab.h
 * \brief This class is used as an interface for defining plugins
 * The aim is to ensure that all methods declared in this class are defined in the plugins
 */
class GripTab : public QDockWidget
{
protected:
    /// pointer to the object selected in the Tree View
    TreeViewReturn *_activeNode;

    /// pointer to the osg viewer
    ViewerWidget *_viewWidget;

public:
    /**
     * \brief called from the main window whenever a new scene is loaded
     */
    virtual void Refresh() = 0;

    /**
     * \brief called from the main window whenever the plugin is added to grip
     * This is initalize the members of the class
     * \param ret Pointer to object returned by the TreeView
     * \param viewer Pointer to composite viewer object where things are rendered
	 * \param world Pointer to the dart world simulation object
	 * \param timeline Array of GripTimeslice object for simulation and kinematic playback
     */
    virtual void Load(TreeViewReturn *ret,
                      ViewerWidget *viewer)
    {
        _activeNode = ret;
        _viewWidget = viewer;
    }

    /**
     * \brief called when a new scene file (urdf, sdf) is loaded into Grip.
     * This signifies that there are skeletons in the world, the viewer is displaying
     * the objects in the world and the TreeView is populated
     */
    virtual void GRIPEventSceneLoaded(){}

    /**
     * \brief called from the main window whenever the simulation is executing
     * This method is executed before every simulation time step
     */
    virtual void GRIPEventSimulationBeforeTimestep(){}

    /**
     * \brief called from the main window whenever the simulation is executing
     * This method is executed after every simulation time step
     */
    virtual void GRIPEventSimulationAfterTimestep(){}

    /**
     * \brief called from the main window whenever the simulation is executing
     * This method is executed at the start of the simulation
     */
    virtual void GRIPEventSimulationStart(){}

    /**
     * \brief called from the main window whenever the simulation is executing
     * This method is executed at the end of the simulation
     */
    virtual void GRIPEventSimulationStop(){}


    /**
     * \brief called from the main window whenever the simulation history slider is being played
     * This method is executed before every playback time step
     */
    virtual void GRIPEventPlaybackBeforeFrame(){}

    /**
     * \brief called from the main window whenever the simulation history slider is being played
     * This method is executed after every playback time step
     */
    virtual void GRIPEventPlaybackAfterFrame(){}

    /**
     * \brief called from the main window whenever the simulation history slider is being played
     * This method is executed at the start of the playback
     */
    virtual void GRIPEventPlaybackStart(){}

    /**
     * \brief called from the main window whenever the simulation history slider is being played
     * This method is executed at the end of the playback
     */
    virtual void GRIPEventPlaybackStop(){}

    /**
     * \brief called from the main window when a new object is selected in the treeview
     */
    virtual void GRIPEventTreeViewSelectionChanged(){}
};

Q_DECLARE_INTERFACE(GripTab,
                    "com.gatech.Grip2.GripTab/1.0")

#endif // GRIPTAB_H
