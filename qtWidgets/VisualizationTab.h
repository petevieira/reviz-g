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
 * \file VisualizationTab.h
 * \brief Widget containing all the visualization settings widgets all
 * contained in a DockableWidget
 */

#ifndef VISUALIZATION_TAB_H
#define VISUALIZATION_TAB_H

// Local includes
#include "ui_VisualizationTab.h"
#include "TreeView.h"
#include "MainWindow.h"

/**
 * \class VisualizationTab VisualizationTab.h
 * \brief Widget containing all the visualization settings widgets all
 * contained in a DockableWidget
 */
class VisualizationTab : public QDockWidget {

    /// Q_Object macro for using signals and slots
    Q_OBJECT

public:
    /**
     * \brief Constructs a Visualization_Tab object
     */
    VisualizationTab(TreeView* treeView, MainWindow *parent);

    /**
     * \brief Destructs a Visualization_Tab object
     */
    ~VisualizationTab();

    /**
     * \brief Updates the world based on the current visualization settings.
     * This is useful for having newly loaded objects render with the current
     * visualization settings
     * \return void
     */
    void update();

signals:
    /**
     * \brief Sets the status bar of its parent
     * \param msg QString to display in the status bar
     * \return void
     */
    void signalSendMessage(QString msg);

protected slots:

    /**
     * \brief Shows/hides the joint axes of the skeletons
     * \param checked Whether or not to show the axes
     * \return void
     */
    void slotToggleJointAxesVisibility(bool checked);

    /**
     * \brief Shows/hides the link frames of the skeletons
     * \param checked Whether or not to show the frames
     * \return void
     */
    void slotToggleBodyNodeAxesVisibility(bool checked);

    /**
     * \brief Shows/hides the center of mass of the skeletons
     * \param checked Whether or not to show the center of masses
     * \return void
     */
    void slotToggleSkeletonCoMVisibility(bool checked);

    /**
     * \brief Shows/hides the projected center of mass of the skeletons
     * \param checked Whether or not to show the projected center of masses
     * \return void
     */
    void slotToggleSkeletonProjCoMVisibility(bool checked);

    /**
     * \brief Turns on/off wireframe mode for all the skeletons
     * \param checked Whether or not to render using wireframe mode
     * \return void
     */
    void slotToggleSkeletonWireFrameMode(bool checked);

    /**
     * \brief Turns on/off collision mesh render mode for all the skeletons
     * \param checked Whether or not to render using the collision mesh instead
     * of the visualization mesh
     * \return void
     */
    void slotToggleSkeletonCollisionMeshMode(bool checked);

    /**
     * \brief Sets the transparency level of a skeleton or BodyNode
     * \param transparencyValue Current transparency value of the slider
     * \return void
     */
     void slotSetTransparencyValue(int transparencyValue);

     /**
      * \brief Turns on/off visualization of contact forces
      * \param checked Whether or not to show contact forces
      * return void
      */
     void slotToggleContactForcesVisibility(bool checked);

     /**
      * \brief Updates the transparency slider position based
      * on the currently selected node
      * \return void
      */
     void slotSetTransparencySliderFromSelectedItem();

     /**
      * \brief Slot to update the local treeview return item. This
      * gets called by the signal that gets triggered when the treeview
      * selection changes.
      * \return void
      */
     void slotSetSelectedTreeViewItem();

protected:
    /// Ui object that contains all the widgets of the tab
    Ui::VisualizationTab *_ui;

    /// Parent
    MainWindow *_parent;

    /// Tree_View pointer for getting the current object
    TreeView *_treeView;

    /// A local copy of the currently selected item in the treeview
    TreeViewReturn *_selectedTreeViewItem;

}; // end class Visualization_Tab

#endif // VISUALIZATION_TAB_H
