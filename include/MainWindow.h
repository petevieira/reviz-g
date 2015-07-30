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
 * \file MainWindow.h
 * \brief Main QWindow base class for robot visualization software
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes
#include <QtGui/QMainWindow>
#include <QtCore/QDir>
#include <QtXml/QtXml>

// C++ Standard includes
#include <iostream>
#include <cstdio>
#include "ViewerWidget.h"

// Forward declarations
class QAction;
class QActionGroup;
class QLabel;
class QMenu;

/**
 * \class MainWindow MainWindow.h
 * \brief Main window for robot simulation interface. A virtual base class
 * that subclasses QMainWindow
 */
class MainWindow : public QMainWindow
{
    /// Meta object macro to use signals and slots
    Q_OBJECT

public:
    /**
     * \brief Constructs a MainWindow object
     */
    MainWindow(QWidget *parent = 0);

    /**
     * \brief Destructs a MainWindow object
     */
    ~MainWindow();

    /**
     * \brief Creates a toolbar
     * \return void
     */
    void Toolbar();

public slots:
    /**
     * \brief Sets the status bar message
     * \param msg Message to display on the status bar
     * \return void
     */
    void slotSetStatusBarMessage(QString msg);

    /**
     * \brief Slot for setting the state and time of the world based on
     * the playback widget's slider position and the contents of the timeline
     * \param sliderTick Position of the playback widget's slider
     */
    virtual void slotSetWorldFromPlayback(int sliderTick) = 0;

    /**
     * \brief Slot for starting the playback
     */
    virtual void slotPlaybackStart() = 0;

    /**
     * \brief Slot for pausing the playback
     */
    virtual void slotPlaybackPause() = 0;

    /**
     * \brief Slot for reversing the playback
     */
    virtual void slotPlaybackReverse() = 0;

    /**
     * \brief Slot for going to the beginning of the playback timeline
     */
    virtual void slotPlaybackTimeStep(bool playForward) = 0;

    /**
     * \brief Slot that recursively calls it self to run the playback loop.
     * The recursive call allows the event loop to process other events, (eg. Stop Playback)
     * \param playForward Whether or not to play back in forward or reverse
     */
    virtual void slotPlaybackBeginning() = 0;

    /**
     * \brief Pure virtual slot that saves a video of the current playback timeline
     */
    virtual void saveVideo() = 0;

protected:
    /**
     * \brief Create an XML file for the workspace
     * contains the list of plugins, status of DockWidgets and the loaded scene
     * \return QDomDocument
     */
    virtual QDomDocument* generateWorkspaceXML() = 0;

    /**
     * \brief Parses the configuration file and manipulates the workspace to match the settings in the configuration file
     * \return void
     */
    virtual void parseConfig(QDomDocument config) = 0;

    /// QToolBar object for showing/hiding buttons
    QToolBar* _getToolBar();

    /// Path of the last loaded scene file
    const QString LAST_LOAD_FILE;

    /// Stores the path to the workspace configuration file
    QString* configFilePath;

    /**
     * \brief Saves the configuration file to the location passed
     * \return void
     */
    void saveConfigFile(QDomDocument *config, QString *filename);

    /**
     * \brief Creates actions
     * \return void
     */
    void createActions();

    /**
     * \brief Creates the menu at the top
     * \return void
     */
    void createMenus();

    /**
     * \brief Creates the rendering window
     * \return void
     */
    virtual void createRenderingWindow() = 0;

    /**
     * \brief Create the tree view
     * \return void
     */
    virtual void createTreeView() = 0;

    /**
     * \brief Create the default tabs
     * \return void
     */
    virtual void createTabs() = 0;

    /**
     * \brief Load the scene and renders it. This function resets everything
     * on each load.
     * \param fileName Name of scene file to load
     * \return void
     */
    virtual void doLoad(std::string fileName) = 0;

    QMenu *fileMenu;
        QAction *loadSceneAct;
        QAction *quickLoadAct;
        QAction *saveSceneAct;
        QAction *loadPluginFileAct;
        QAction *loadPluginDirAct;
        QAction *saveWorkspaceConfigurationAct;
        QAction *saveNewWorkspaceConfigurationAct;
        QAction *loadWorkspaceConfigurationAct;
        QAction *closeSceneAct;
        QAction *exitAct;
    QMenu *viewMenu;
        QAction *frontAct;
        QAction *topAct;
        QAction *sideAct;
    QMenu *simulationMenu;
        QAction *startSimulationAct;
        QAction *stopSimulationAct;
        QAction *simulateSingleStepAct;
    QMenu *settingsMenu;
        QAction *renderDuringSimulationAct;
        QMenu *backgroundMenu;
            QAction *whiteAct;
            QAction *grayAct;
            QAction *blackAct;
        QAction *resetCameraAct;
    QMenu *renderMenu;
        QAction *xga1024x768Act;
        QAction *vga640x480Act;
        QAction *hd1280x720Act;
    QMenu *helpMenu;
        QAction *aboutAct;

    QToolBar *toolbar;


protected slots:
    /**
     * \brief Loads a scene with a dialog box
     * \return void
     */
    void loadScene();

    /**
     * \brief Loads the last loaded scene
     * \return void
     */
    void quickLoad();

    /**
     * \brief Saves the loaded scene to file for quick load functionality
     * \return void
     */
    void saveScene();

    /**
     * \brief Loads a plugin file using a file dialog for the user to manually
     * find the plugin file
     */
    void loadPluginFileWithDialog();

    /**
     * \brief Loads all plugin files inside a directory with a dialog for the user
     * to manually find the plugin directory
     */
    void loadPluginDirWithDialog();

    /**
     * \brief Reads a QDir directory and loads all the plugins inside it
     * \param pluginsDirName Name of the QDir containing the plugins
     */
    virtual void loadPluginDirectory(QDir pluginsDirName) = 0;

    /**
     * \brief Loads a plugin file (.so) by name. When loaded, the plugin will be
     * added to the bottom tabs area.
     * \param pluginFileName String representing the path of the plugin
     */
    virtual void loadPluginFile(QString pluginFilename) = 0;

    /**
     * \brief Closes the Window
     * \return void
     */
    virtual void close();

    /**
     * \brief Exits the program
     * \return void
     */
    void exit();

    /**
     * \brief Sets the view to front view
     * \return void
     */
    virtual void front() = 0;

    /**
     * \brief Sets the view to top view
     * \return void
     */
    virtual void top() = 0;

    /**
     * \brief Sets the view to side view
     * \return void
     */
    virtual void side() = 0;

    /**
     * \brief Starts the simulation
     * \return void
     */
    virtual void startSimulation() = 0;

    /**
     * \brief Stops the simulation
     * \return void
     */
    virtual void stopSimulation() = 0;

    /**
     * \brief Simulates a single time step of the simulation
     * \return void
     */
    virtual void simulateSingleStep() = 0;

    /**
     * \brief Turns on rendering during simulation, which will simulation slower than if
     * rendering is turned off.
     */
    virtual void renderDuringSimulation() = 0;

    /**
     * \brief Sets the background color of the window to white
     * \return void
     */
    virtual void white() = 0;

    /**
     * \brief Sets the background color of the window to gray
     * \return void
     */
    virtual void gray() = 0;

    /**
     * \brief Sets the background color of the window to black
     * \return void
     */
    virtual void black() = 0;

    /**
     * \brief Puts the camera back to its home position
     * \return void
     */
    virtual void resetCamera() = 0;

    virtual void xga1024x768() = 0;

    virtual void vga640x480() = 0;

    virtual void hd1280x720() = 0;

    /**
     * \brief Takes a screenshot of the rendering widget and saves it to a specific location
     * \return void
     */
    virtual void camera() = 0;

    /**
     * \brief Takes multiple sceenshots of the rendering widget while it is playing back a simulation
     * \return void
     */
    virtual void film() = 0;

    /**
     * \brief Notifies thread that simulation has stopped
     * \return void
     */
    virtual void simulationStopped() = 0;

    /**
     * \brief Sets the time box for simulation time relative to real time
     * \param time The simulation time relative to real time
     * \return void
     */
    // virtual void setSimulationRelativeTime(double time) = 0;

    /**
     * \brief Displays information about the application
     * \return void
     */
    void about();

    /**
     * \brief Saves the workspace configuration to an existing configuration file
     * \return void
     */
    void saveWorkspace();

    /**
     * \brief Saves the workspace configuration to a new configuration file
     * \return void
     */
    void saveNewWorkspace();

    /**
     * \brief Loads workspace configuration from a configuration file
     * \return void
     */
    void loadWorkspace(std::string workspaceFile="");
}; // end class MainWindow

#endif // MAINWINDOW_H
