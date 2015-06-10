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
#include "VisualizationTab.h"

// C++ Standard includes
#include <iostream>

VisualizationTab::VisualizationTab(TreeView* treeView, MainWindow *parent)
    : QDockWidget(parent), _parent(parent)
{
    _ui = new Ui::VisualizationTab;
    _treeView = treeView;
    _selectedTreeViewItem = 0;

    _ui->setupUi(this);

    // Signals from parent to my slots
    connect(this, SIGNAL(signalSendMessage(QString)), _parent, SLOT(slotSetStatusBarMessage(QString)));

    // Signals from my widgets to my slots
    connect(_ui->checkBoxShowJointAxes, SIGNAL(toggled(bool)), this, SLOT(slotToggleJointAxesVisibility(bool)));
    connect(_ui->checkBoxShowBodyNodeFrames, SIGNAL(toggled(bool)), this, SLOT(slotToggleBodyNodeAxesVisibility(bool)));
    connect(_ui->checkBoxShowCoM, SIGNAL(toggled(bool)), this, SLOT(slotToggleSkeletonCoMVisibility(bool)));
    connect(_ui->checkBoxShowProjCoM, SIGNAL(toggled(bool)), this, SLOT(slotToggleSkeletonProjCoMVisibility(bool)));
    connect(_ui->checkBoxRenderUsingCollsionMesh, SIGNAL(toggled(bool)), this, SLOT(slotToggleSkeletonCollisionMeshMode(bool)));
    connect(_ui->checkBoxRenderWireframe, SIGNAL(toggled(bool)), this, SLOT(slotToggleSkeletonWireFrameMode(bool)));
    connect(_ui->sliderTransparency, SIGNAL(valueChanged(int)), this, SLOT(slotSetTransparencyValue(int)));
    connect(_ui->checkBoxShowContactForces, SIGNAL(toggled(bool)), this, SLOT(slotToggleContactForcesVisibility(bool)));

    // Signals from TreeView to my slots
    connect(_treeView, SIGNAL(itemSelected(TreeViewReturn*)), this, SLOT(slotSetTransparencySliderFromSelectedItem()));
    connect(_treeView, SIGNAL(itemSelected(TreeViewReturn*)), this, SLOT(slotSetSelectedTreeViewItem()));
}

VisualizationTab::~VisualizationTab()
{
}

void VisualizationTab::update()
{
    // slotToggleJointAxesVisibility(_ui->checkBoxShowJointAxes->checkState());
    // slotToggleBodyNodeAxesVisibility(_ui->checkBoxShowBodyNodeFrames->checkState());
    // slotToggleSkeletonCoMVisibility(_ui->checkBoxShowCoM->checkState());
    // slotToggleSkeletonProjCoMVisibility(_ui->checkBoxShowProjCoM->checkState());
    // slotToggleSkeletonCollisionMeshMode(_ui->checkBoxRenderUsingCollsionMesh->checkState());
    // slotToggleSkeletonWireFrameMode(_ui->checkBoxRenderWireframe->checkState());
    // slotToggleContactForcesVisibility(_ui->checkBoxShowContactForces->checkState());
}

void VisualizationTab::slotToggleJointAxesVisibility(bool checked)
{
    // _worldNode->setJointAxesVisible(checked);
}

void VisualizationTab::slotToggleBodyNodeAxesVisibility(bool checked)
{
    // _worldNode->setBodyNodeAxesVisible(checked);
}

void VisualizationTab::slotToggleSkeletonCoMVisibility(bool checked)
{
    // _worldNode->setSkeletonCoMVisible(checked);
}

void VisualizationTab::slotToggleSkeletonProjCoMVisibility(bool checked)
{
    // _worldNode->setSkeletonCoMProjectedVisible(checked);
}

void VisualizationTab::slotToggleSkeletonCollisionMeshMode(bool checked)
{
    // _worldNode->setSkeletonCollisionMeshOn(checked);
}

void VisualizationTab::slotToggleSkeletonWireFrameMode(bool checked)
{
    // _worldNode->setSkeletonWireFrameOn(checked);
}

void VisualizationTab::slotSetTransparencyValue(int transparencyValue)
{
    // if(!_selectedTreeViewItem) {
    //     emit signalSendMessage("VisualizationTab] No item selected in TreeView");
    //     return;
    // }

    // if(Return_Type_Robot == _selectedTreeViewItem->dType) {
    //     dart::dynamics::Skeleton* skel = (dart::dynamics::Skeleton*)_selectedTreeViewItem->object;
    //     _worldNode->setSkeletonTransparency(*skel, (float)transparencyValue/100.0);
    // } else if(Return_Type_Node == _selectedTreeViewItem->dType) {
    //     dart::dynamics::BodyNode* node = (dart::dynamics::BodyNode*)_selectedTreeViewItem->object;
    //     _worldNode->setBodyNodeTransparency(*node, (float)transparencyValue/100.0);
    // } else {
    //     emit signalSendMessage("[VisualizationTab] Unknown type selected in TreeView");
    // }
}

void VisualizationTab::slotSetTransparencySliderFromSelectedItem()
{

}

void VisualizationTab::slotToggleContactForcesVisibility(bool checked)
{
    // _worldNode->setContactForcesVisible(checked);
}

void VisualizationTab::slotSetSelectedTreeViewItem()
{
    // Check if we have a world
    // if(!_worldNode->getNumSkeletons()) {
    //     return;
    // }

    // // Get the selected treeview item and check if it's valid
    // _selectedTreeViewItem = _treeView->getActiveItem();
}
