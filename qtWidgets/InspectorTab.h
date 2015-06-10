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
 * \file InspectorTab.h
 * \brief Class that handles all primitive interaction affecting orientation
 * and position of objects in the simulation world
 */

#ifndef INSPECTOR_TAB_H
#define INSPECTOR_TAB_H

// Local includes
#include "ui_InspectorTab.h"
#include "TreeView.h"

/**
 * \class InspectorTab InspectorTab.h
 * \brief Widget containing all the widgets that allow the user to manually manipulate
 * a skeleton. Subclasses QDockWidget.
 */
class InspectorTab : public QDockWidget {

    /// meta object macro for signals and slots usage
    Q_OBJECT

public:
    /**
     * \brief Constructs an InspectorTab object
     * \param parent Object constructing this InspectorTab object
     * \param simWorld Pointer to the simulation world
     * \param treeViewer Pointer to the TreeView
     */
    InspectorTab(QWidget *parent, TreeView *treeViewer);

    /**
     * \brief Destructs an InspectorTab object
     */
    ~InspectorTab();

    /**
     * \brief Initializes the tab widget
     * \return void
     */
    void initializeTab();


private slots:
    void changeSelectedJoint(int sliderValue); //, simulation::World* mWorld, Tree_View* treeviewer);
    void receiveSeletedItem(TreeViewReturn *active_item);
    void changePositionAndOrientation(int sliderValue);


private:
    /// Pointer to all the widgets of the UI
    Ui::InspectorTab *_ui;
    /// Pointer to the TreeView object
    TreeView *_treeview;
    /// Pointer to the position slider widget
    QSlider *_positionSlider_0;
    /// Pointer to the position spin box widget
    QDoubleSpinBox *_positionSpinBox_0;
    /// Type of the currently selected TreeView item
    int _selectedTypeFromTree;

    // /**
    //  * \brief Gets the root transform of a Skeleton pointer passed in
    //  * \param skel Skeleton pointer of which to get the root transform
    //  * \return Eigen::Matrix6d containing the root transform of the skeleton passed in
    //  */
    // Eigen::Matrix<double, 6, 1> getRootTransform(dart::dynamics::Skeleton *robot);

    // /**
    //  * \brief Sets the root transform of a Skeleton pointer passed in
    //  * \param skel Pointer to the skeleton of which to change the root transform
    //  * \param pose New transformation of the skeletons root
    //  * \return void
    //  */
    // void setRootTransform(dart::dynamics::Skeleton *robot, const Eigen::Matrix<double, 6, 1> &pose);

    // /**
    //  * \brief Converts a transform to a xyz roll, pitch, yaw vector
    //  * \param tf Transformation to convert
    //  * \return Vector containing the xyz and roll, pitch, yaw values of the transform
    //  */
    // Eigen::Matrix<double, 6, 1> getPoseFromTransform(const Eigen::Isometry3d &tf);

}; // end class InspectorTab

#endif // INSPECTOR_TAB_H

