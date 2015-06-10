/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */
 
#include "myplugin.h"
#include <iostream>
#include <qplugin.h>
#include <QtGui>
#include <dart/dynamics/Skeleton.h>
#include <dart/dynamics/Joint.h>
#include <dart/dynamics/BodyNode.h>

MyPlugin::MyPlugin(QWidget *parent) : ui(new Ui::MyPluginTab){
    ui->setupUi(this);
}

MyPlugin::~MyPlugin(){}

void MyPlugin::GRIPEventSceneLoaded()
{
    std::cerr << "Rotate LSP (Left Shoulder Pitch) 360 degrees and add it to the timeline" << std::endl;

    // Get GolemHubo skeleton
    dart::dynamics::Skeleton* skel = _world->getSkeleton("GolemHubo");

    if (skel) {
        // Get index of LSP (left shoulder pitch
        std::vector<int> index(1);
        index[0] = skel->getJoint("LSP")->getGenCoord(0)->getSkeletonIndex();

        // Initialize joint value for LSP
        Eigen::VectorXd jointValue(1);

        // Move joint around
        for (size_t i = 0; i < 200; ++i) {
            // Set joint value
            jointValue[0] = float(i) * 2 * M_PI / 200;
            skel->setConfig(index, jointValue);

            // Save world to timeline
            _timeline->push_back(GripTimeslice(*_world));
        }
    } else {
        std::cerr << "No skeleton named GolemHubo" << std::endl;
    }
}

void MyPlugin::GRIPEventSimulationBeforeTimestep()
{
}

void MyPlugin::GRIPEventSimulationAfterTimestep(){}
void MyPlugin::GRIPEventSimulationStart(){}
void MyPlugin::GRIPEventSimulationStop(){}
void MyPlugin::GRIPEventTreeViewSelectionChanged()
{
    if(!_activeNode) {
        std::cerr << "[MyPlugin] No item selected in TreeView" << std::endl;
        return;
    }

    std::cerr << "[MyPlugin] ActiveNodeType: " << _activeNode->dType << std::endl;
    if(Return_Type_Robot == _activeNode->dType) {
        dart::dynamics::Skeleton* skel = (dart::dynamics::Skeleton*)_activeNode->object;
        std::cerr << "[MyPlugin] Skeleton Selected: " << skel->getName() << std::endl;
    } else if(Return_Type_Node == _activeNode->dType) {
        dart::dynamics::BodyNode* node = (dart::dynamics::BodyNode*)_activeNode->object;
        std::cerr << "[MyPlugin] BodyNode Selected: " << node->getName() << std::endl;
    } else {
        std::cerr << "[MyPlugin] Unknown type selected in TreeView" << std::endl;
    }
}

void MyPlugin::GRIPEventPlaybackBeforeFrame() {}

/**
 * \brief called from the main window whenever the simulation history slider is being played
 * This method is executed after every playback time step
 */
void MyPlugin::GRIPEventPlaybackAfterFrame() {}

/**
 * \brief called from the main window whenever the simulation history slider is being played
 * This method is executed at the start of the playback
 */
void MyPlugin::GRIPEventPlaybackStart() {}

/**
 * \brief called from the main window whenever the simulation history slider is being played
 * This method is executed at the end of the playback
 */
void MyPlugin::GRIPEventPlaybackStop() {}

void MyPlugin::Refresh() {}

Q_EXPORT_PLUGIN2(MyPlugin, MyPlugin)
