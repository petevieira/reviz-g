/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */
 
#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include "ui_myplugin.h"
#include <grip/qtWidgets/GripTab.h>
#include <grip/osgReviz/ViewerWidget.h>
#include <grip/qtWidgets/TreeViewReturn.h>


class MyPlugin : public GripTab
{
    Q_OBJECT
    Q_INTERFACES(GripTab)

public:
     MyPlugin(QWidget *parent = 0);
    ~MyPlugin();

    void GRIPEventSceneLoaded();
    void GRIPEventSimulationBeforeTimestep();
    void GRIPEventSimulationAfterTimestep();
    void GRIPEventSimulationStart();
    void GRIPEventSimulationStop();
    void GRIPEventPlaybackBeforeFrame();
    void GRIPEventPlaybackAfterFrame();
    void GRIPEventPlaybackStart();
    void GRIPEventPlaybackStop();
    void GRIPEventTreeViewSelectionChanged();
    void Refresh();

private:
    Ui::MyPluginTab *ui;

};

#endif // EXAMPLE1_H
