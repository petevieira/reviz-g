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
#include "GripMainWindow.h"
#include "ViewerWidget.h"
#include "VisualizationTab.h"
#include "ui_VisualizationTab.h"
#include "InspectorTab.h"
#include "ui_InspectorTab.h"
#include "TreeView.h"
#include "ui_TreeView.h"
#include "DoubleSlider.h"
#include "Grid.h"
#include "Line.h"

// Qt includes
#include <QtGui>
#include <QPixmap>

// OpenSceneGraph includes
#include <osg/io_utils>

GripMainWindow::GripMainWindow(bool debug, std::string sceneFile, std::string configFile) :
    MainWindow(),
    pluginList(new QList<GripTab*>),
    pluginMenu(new QMenu),
    _debug(debug),
    _simulating(false),
    _playingBack(false),
    _curPlaybackTick(0),
    _playbackSpeed(5),
    _simulationDirty(false),
    _recordVideo(false)
{
    /// object initialization
    playbackWidget = new PlaybackWidget(this);
    timeline = new std::vector<GripTimeslice>(0);
    pluginPathList = new QList<QString*>;
    sceneFilePath = new QString();
    std::cerr<<sceneFilePath->toStdString()<<std::endl;

    /// create objects for widget classes
    createTreeView();
    createRenderingWindow();
    createTabs();

    /// load widgets in the user interface and manages the layout
    manageLayout();
    createPluginMenu();

    /// set the status bar for the Grip Window
    this->setStatusBar(this->statusBar());

    // Load config file passed in by user, if specified
    if (!configFile.empty()) {
        this->loadWorkspace(configFile);
    } else {
        this->loadWorkspace(configFilePath->toStdString());
    }

    // Load scene passed in by user, if specified
    if (!sceneFile.empty())
        this->doLoad(sceneFile);
    xga1024x768();

}

GripMainWindow::~GripMainWindow() {}

void GripMainWindow::doLoad(std::string sceneFileName)
{
    sceneFilePath = new QString(QString::fromStdString(sceneFileName));

    if (_simulating || _playingBack) {
        if (!stopSimulationWithDialog()) {
            if (_debug) std::cerr << "Not loading a new world" << std::endl;
            return;
        }
    }

    // viewWidget->addNodeToScene(worldNode);

    // worldNode->printInfo();

    // treeviewer->populateTreeView(world);
    visualizationTab->update();

    if (_debug) std::cout << "--(i) Saving " << sceneFileName << " to ~/.griplastload file (i)--" << std::endl;
    saveText(sceneFileName, LAST_LOAD_FILE);
    inspectorTab->initializeTab();
    this->slotSetStatusBarMessage("Successfully loaded scene " + QString::fromStdString(sceneFileName));

    // Tell all the tabs that a new scene has been loaded
    for (int i = 0; i < pluginList->size(); ++i) {
        pluginList->at(i)->GRIPEventSceneLoaded();
    }
}

void GripMainWindow::close()
{
    std::cerr << "Closing" << std::endl;
    clear();
}

bool GripMainWindow::stopSimulationWithDialog()
{
    // Ask user if they really want to end the simulation and load a new world
    QMessageBox msgBox;

    QString action = (_simulating ? "simulation" : "playback");
    msgBox.setWindowTitle(tr(qPrintable("Stop " + action + " and Open Scene?")));
    msgBox.setText(tr(qPrintable("Ending " + action + " and opening new scene!")));
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int resp = msgBox.exec();

    if (QMessageBox::Cancel == resp) {
        return false;
    }

    // Stop simulation
    // if (_simulating) {
    //     simulation->stopSimulation();
    //     // Wait for simulation to stop by letting the event loop process
    //     // events until the "simulationStopped" slot is called which set the
    //     // _simulating flag to false.
    //     while (_simulating) {
    //         QCoreApplication::processEvents();
    //     }
    //     // Swap the start and stop buttons
    //     this->swapStartStopButtons();
    // } else {
    //     this->slotPlaybackPause();
    // }

    return true;
}

void GripMainWindow::clear()
{
    // if (world) {
    //     worldNode->reset();
    //     while (world->getNumSkeletons()) {
    //         world->removeSkeleton(world->getSkeleton(0));
    //     }
    //     world->setTime(0);
    //     treeviewer->reset();
    //     simulation->reset();
    //     playbackWidget->reset();
    //     timeline->clear();
    //     sceneFilePath = NULL;
    //     for (int i = 0; i < pluginList->size(); ++i) {
    //         pluginList->at(i)->Refresh();
    //     }
    // }
}

void GripMainWindow::simulationStopped()
{
    if(_debug) std::cerr << "Got simulationStopped signal" << std::endl;
    _simulating = false;
    playbackWidget->ui->sliderMain->setEnabled(true);
    playbackWidget->slotUpdateSliderMinMax(0, timeline->size() - 1);
    playbackWidget->setSliderValue(timeline->size() - 1);
}

void GripMainWindow::slotSetWorldFromPlayback(int sliderTick)
{
    if (_simulating || timeline->size() <= 0) {
        playbackWidget->setSliderValue(0);
        return;
    }

    _curPlaybackTick = sliderTick;
    // world->setTime(timeline->at(_curPlaybackTick).getTime());
    // this->setWorldState_Issue122(timeline->at(sliderTick).getState());
    // playbackWidget->slotSetTimeDisplays(world->getTime(), 0);
    // playbackWidget->slotUpdateSliderMinMax(0, timeline->size() - 1);
}

void GripMainWindow::slotPlaybackStart()
{
    if (timeline->size() <= 0) {
        return;
    }

    if ((playbackWidget->getSliderValue() + 1) == (int) timeline->size()) {
        this->slotPlaybackBeginning();
    }

    this->slotSetStatusBarMessage(tr("Starting playback"));

    if (_playingBack) {
        slotPlaybackPause();
    }

    _curPlaybackTick = playbackWidget->getSliderValue();
    _simulationDirty = true;

    for (int i = 0; i < pluginList->size(); ++i) {
        pluginList->at(i)->GRIPEventPlaybackStart();
    }

    _playingBack = true;
    this->slotPlaybackTimeStep(true);
}

void GripMainWindow::slotPlaybackPause()
{
    if (timeline->size() <= 0 || !_playingBack) {
        return;
    }

    this->slotSetStatusBarMessage(tr(qPrintable("Pausing playback")));

    _playingBack = false;

    for (int i = 0; i < pluginList->size(); ++i) {
        pluginList->at(i)->GRIPEventPlaybackStop();
    }
}

void GripMainWindow::slotPlaybackReverse()
{
    if (timeline->size() <= 0) {
        return;
    }

    if (playbackWidget->getSliderValue() == 0) {
        _curPlaybackTick = timeline->size() - 1;
        playbackWidget->setSliderValue(_curPlaybackTick);
        // world->setTime(timeline->back().getTime());
        // this->setWorldState_Issue122(timeline->back().getState());
        // playbackWidget->slotSetTimeDisplays(world->getTime(), 0);
    }

    this->slotSetStatusBarMessage(tr("Reversing playback"));

    if (_playingBack) {
        slotPlaybackPause();
    }

    _curPlaybackTick = playbackWidget->getSliderValue();

    for (int i = 0; i < pluginList->size(); ++i) {
        pluginList->at(i)->GRIPEventPlaybackStart();
    }

    _playingBack = true;
    this->slotPlaybackTimeStep(false);
}

void GripMainWindow::slotPlaybackBeginning()
{
    if (timeline->size() <= 0) {
        return;
    }

    this->slotSetStatusBarMessage(tr("Setting playback to beginning"));

    _curPlaybackTick = 0;
    playbackWidget->setSliderValue(_curPlaybackTick);
    if (timeline->size() > 0) {
        // world->setTime(timeline->at(_curPlaybackTick).getTime());
        // this->setWorldState_Issue122(timeline->front().getState());
    }
    // playbackWidget->slotSetTimeDisplays(world->getTime(), 0);
}

void GripMainWindow::slotPlaybackTimeStep(bool playForward)
{
    if (_playingBack) {

        if (_playbackSpeed != 5 * playbackWidget->getPlaybackSpeed())
            _playbackSpeed = 5 * playbackWidget->getPlaybackSpeed();

        // Call user tab functions before time step
        for (int i = 0; i < pluginList->size(); ++i) {
            pluginList->at(i)->GRIPEventPlaybackBeforeFrame();
        }

        // Play time step
        // world->setTime(timeline->at(_curPlaybackTick).getTime());
        // this->setWorldState_Issue122(timeline->at(_curPlaybackTick).getState());
        // playbackWidget->slotSetTimeDisplays(world->getTime(), 0);

        std::cerr << "cur: " << _curPlaybackTick << ", " << _curPlaybackTick + _playbackSpeed << ", " << timeline->size()-1 << std::endl;
        if ((_curPlaybackTick == 0 && !playForward)
                || (_curPlaybackTick == (timeline->size() - 1) && playForward)) {
            _playingBack = false;
            std::cerr << "Done playing back" << std::endl;
        } else if (((_curPlaybackTick - _playbackSpeed) < 0 && !playForward)
                || ((_curPlaybackTick + _playbackSpeed) > (timeline->size() - 1) && playForward)) {
            _curPlaybackTick = (playForward ? timeline->size() - 1 : 0); 
        } else {
            playForward ? _curPlaybackTick = _curPlaybackTick + _playbackSpeed
                    : _curPlaybackTick = _curPlaybackTick - _playbackSpeed;
        }

        playbackWidget->setSliderValue(_curPlaybackTick);
        if(_recordVideo){
            recordImageList->append(recordViewWidget->takeScreenshot());
        }

        // Call user tab functions after time step
        for (int i = 0; i < pluginList->size(); ++i) {
            pluginList->at(i)->GRIPEventPlaybackAfterFrame();
        }

    } else {
        if(_recordVideo)
            QMetaObject::invokeMethod(this, "saveVideo", Qt::QueuedConnection);
            _recordVideo = false;
        return;
    }

    QMetaObject::invokeMethod(this, "slotPlaybackTimeStep",
                              Qt::QueuedConnection, Q_ARG(bool, playForward));
}

int GripMainWindow::saveText(std::string scenepath, const QString &filename)
{
    try {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return 0;
        QTextStream out(&file);
        out << QString::fromStdString(scenepath) << "\n";
    }

    catch (const std::exception& e) {
        std::cout <<  e.what() << std::endl;
        return 0;
    }
    return 1;
}

void GripMainWindow::front()
{
    viewWidget->setToFrontView();
}

void GripMainWindow::top()
{
    viewWidget->setToTopView();
}

void GripMainWindow::side()
{
    viewWidget->setToSideView();
}

void GripMainWindow::xga1024x768()
{
    if(!xga1024x768Act->isChecked())
        recordSize = QSize(1024, 760);
    else {
        if(vga640x480Act->isChecked())
            vga640x480Act->toggle();

        if(hd1280x720Act->isChecked())
            hd1280x720Act->toggle();

        recordSize = QSize(1024, 760);
    }
}

void GripMainWindow::vga640x480()
{
    if(!vga640x480Act->isChecked())
        recordSize = QSize(640, 472);
    else {
        if(xga1024x768Act->isChecked())
            xga1024x768Act->toggle();

        if(hd1280x720Act->isChecked())
            hd1280x720Act->toggle();

        recordSize = QSize(640, 472);
    }
}

void GripMainWindow::hd1280x720()
{
    if(!hd1280x720Act->isChecked())
        recordSize = QSize(1280, 712);
    else {
        if(vga640x480Act->isChecked())
            vga640x480Act->toggle();

        if(xga1024x768Act->isChecked())
            xga1024x768Act->toggle();

        recordSize = QSize(1280, 712);
    }
}

void GripMainWindow::startSimulation()
{
    if (_playingBack) {
        slotSetStatusBarMessage(tr("Stop playback first"));
        return;
    }
}

void GripMainWindow::stopSimulation()
{
    _simulating = false;
    // FIXME: Maybe use qsignalmapping or std::map for this
    swapStartStopButtons();
}

void GripMainWindow::swapStartStopButtons()
{
    if (this->_getToolBar()->actions().at(3)->isVisible()) {
        this->_getToolBar()->actions().at(3)->setVisible(false);
        this->_getToolBar()->actions().at(4)->setVisible(true);
    } else {
        this->_getToolBar()->actions().at(3)->setVisible(true);
        this->_getToolBar()->actions().at(4)->setVisible(false);
    }
}

void GripMainWindow::simulateSingleStep()
{
}

void GripMainWindow::renderDuringSimulation(){}

void GripMainWindow::white()
{
    viewWidget->setBackgroundColor(osg::Vec4(1, 1, 1, 1));
}

void GripMainWindow::gray()
{
    viewWidget->setBackgroundColor(osg::Vec4(.5, .5, .5, 1));
}

void GripMainWindow::black()
{
    viewWidget->setBackgroundColor(osg::Vec4(0, 0, 0, 1));
}

void GripMainWindow::resetCamera()
{
    viewWidget->setCameraToHomePosition();
}

void GripMainWindow::createRenderingWindow()
{
    viewWidget = new ViewerWidget();
    viewWidget->setGeometry(100, 100, 800, 600);
    viewWidget->addGrid(20, 20, 1);
}

void GripMainWindow::createTreeView()
{
    treeviewer = new TreeView(this, pluginList);
}

void GripMainWindow::loadPluginDirectory(QDir pluginsDirName)
{
    std::cerr << "Plugin Path: " << pluginsDirName.absolutePath().toStdString() << std::endl;

    foreach (QString fileName, pluginsDirName.entryList(QDir::Files)) {
        std::cerr << "Entry: " << fileName.toStdString() << std::endl;
        QFileInfo fileInfo(fileName);
        if (fileInfo.suffix() != "so") {
            slotSetStatusBarMessage(tr(qPrintable("Incorrect file extension on plug: " + fileInfo.path() + " >>> " + fileInfo.suffix())));
            continue;
        }
        if (_debug) std::cerr << "Attempting to load plugin: " << fileInfo.absoluteFilePath().toStdString() << std::endl;
        this->loadPluginFile(pluginsDirName.absolutePath() + "/" + fileName);
    }
}

void GripMainWindow::loadPluginFile(QString pluginFileName)
{
    // if (pluginList->size() == 0)
    //     pluginMenu->addSeparator();
    // std::cerr << "File: " << pluginFileName.toStdString() << std::endl;
    // QPluginLoader loader(pluginFileName);
    // QObject* plugin = loader.instance();
    // if (plugin) {
    //     GripTab* gt = qobject_cast<GripTab*>(plugin);
    //     if (gt) {
    //         gt->Load(treeviewer->getActiveItem(), viewWidget, world, timeline);

    //         QDockWidget* pluginWidget = qobject_cast<QDockWidget*>(plugin);
    //         if (pluginWidget == NULL) {
    //             if (_debug)
    //                 std::cerr << "is NULL" << std::endl;
    //         } else {
    //             this->addDockWidget(Qt::BottomDockWidgetArea, pluginWidget);
    //             QList<QDockWidget *> dockwidgetList = qFindChildren<QDockWidget *>(this);
    //             QDockWidget* bottomWidget;
    //             bool bottomWidgetPresent = false;
    //             if (dockwidgetList.size())
    //                 for (int i = 0; i < dockwidgetList.size(); ++i)
    //                     if (this->dockWidgetArea(dockwidgetList.at(i)) == 8) {
    //                         bottomWidgetPresent = true;
    //                         bottomWidget = dockwidgetList.at(i);
    //                         break;
    //                     }
    //             if (bottomWidgetPresent)
    //                 this->tabifyDockWidget(bottomWidget, pluginWidget);

    //             pluginList->append(gt);
    //             std::cerr << "Plugins: " << pluginList->size() << std::endl;
    //             pluginPathList->append(new QString(pluginFileName));
    //             if (_debug) std::cerr << "Plugin loaded " << (plugin->objectName()).toStdString() << std::endl;
    //             pluginMenu->addAction(pluginWidget->toggleViewAction());
    //         }
    //     }
    // } else {
    //     slotSetStatusBarMessage(tr(qPrintable("Couldn't load plugin. " + loader.errorString())));
    //     if (_debug) {
    //         std::cerr << "Plugin could not be loaded" << std::endl;
    //         std::cerr << "Error: " << (loader.errorString()).toStdString() << std::endl;
    //     }
    // }
}

// void GripMainWindow::setSimulationRelativeTime(double time)
// {
    // playbackWidget->slotSetTimeDisplays(world->getTime(), time);
// }

void GripMainWindow::createTabs()
{
    inspectorTab = new InspectorTab(this, treeviewer);
    visualizationTab = new VisualizationTab(treeviewer, this);
}

void GripMainWindow::createGround()
{
}

void GripMainWindow::manageLayout()
{
    QWidget* widget = new QWidget(this);
    gridLayout = new QGridLayout;

    /// viewWidget initial size: 800 x 600
    gridLayout->addWidget(viewWidget, 0, 0, 1, 2);

    gridLayout->addWidget(playbackWidget, 1, 0);

    widget->setLayout(gridLayout);
    this->setCentralWidget(widget);

    /// adding tree view
    this->addDockWidget(Qt::RightDockWidgetArea, treeviewer);

    /// adding the inspector and visualization tabs
    this->setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::North);
    this->addDockWidget(Qt::BottomDockWidgetArea, visualizationTab);
    this->addDockWidget(Qt::BottomDockWidgetArea, inspectorTab);
    tabifyDockWidget(inspectorTab, visualizationTab);
    visualizationTab->show();
    visualizationTab->raise();
}

void GripMainWindow::createPluginMenu()
{
    pluginMenu = menuBar()->addMenu(tr("&Widgets"));

    QList<QDockWidget *> dockwidgetList = qFindChildren<QDockWidget *>(this);
    if (dockwidgetList.size()) {
        for (int i = 0; i < dockwidgetList.size(); ++i) {
                pluginMenu->addAction(dockwidgetList.at(i)->toggleViewAction());
        }
    }
}

QDomDocument* GripMainWindow::generateWorkspaceXML()
{
    QDomDocument* config = new QDomDocument();
    QDomProcessingInstruction xmlDeclaration = config->createProcessingInstruction("xml", "version=\"1.0\"");
    config->appendChild(xmlDeclaration);

    QDomElement root = config->createElement("configuration");

    // add plugins
    QDomElement plugins = config->createElement("plugins");
    root.appendChild(plugins);

    if (pluginPathList != NULL)
    {
        std::cerr << "adding plugins" << std::endl;
        for (int i = 0; i < pluginPathList->count(); ++i) {
            std::cerr << (*(pluginPathList->at(i))).toStdString() << std::endl;
            QDomElement plugin = config->createElement("plugin");
            plugin.setAttribute("ppath", *(pluginPathList->at(i)));
            plugins.appendChild(plugin);
        }
    }

    // add dockwidget status
    QDomElement dockWidgetStatus = config->createElement("dockWidgetStatus");
    root.appendChild(dockWidgetStatus);

    QList<QAction*> actionList;
    if (pluginMenu != NULL)
    {
        actionList = pluginMenu->actions();
        if (!actionList.isEmpty()) {
            for(int i = 0; i < actionList.count(); i++) {
                QAction* act = actionList.at(i);
                QDomElement dockWidget = config->createElement("dockWidget");
                dockWidget.setAttribute("name", act->text());
                dockWidget.setAttribute("isChecked", QString::number(act->isChecked()));
                dockWidgetStatus.appendChild(dockWidget);
            }
        }
    }

    // add scene file information
    QDomElement scene = config->createElement("scene");
    if (!sceneFilePath->isNull()) {
        scene.setAttribute("spath", *sceneFilePath);
        std::cerr << "spath: " << sceneFilePath->toStdString() << std::endl;
    } else {
        if (_debug) std::cerr << "SceneFilePath is NULL" << std::endl;
    }
    root.appendChild(scene);

    //add the window size information
    QDomElement size = config->createElement("size");
    size.setAttribute("width", this->size().width());
    size.setAttribute("height", this->size().height());
    root.appendChild(size);

    //add the location of each DockWidget
    QDomElement dockLocation = config->createElement("Location");
    QList<QDockWidget *> dockwidgetList = qFindChildren<QDockWidget *>(this);
    if (dockwidgetList.size()) {
        for (int i = 0; i < dockwidgetList.size(); ++i) {
            QDomElement dockWidget = config->createElement("dockWidgetLocation");
            dockWidget.setAttribute("name", dockwidgetList.at(i)->windowTitle());
            dockWidget.setAttribute("isFloating", dockwidgetList.at(i)->isFloating());
            dockWidget.setAttribute("location", this->dockWidgetArea(dockwidgetList.at(i)));
            dockLocation.appendChild(dockWidget);
        }
    }
    root.appendChild(dockLocation);

    // to be added when necessary implementations are completed
    // add camera information
    // add light sources
    config->appendChild(root);
    return config;
}

void GripMainWindow::parseConfig(QDomDocument config)
{
    /// parse and load plugins
    QDomNodeList pluginList = config.elementsByTagName("plugin");
    for (int i = 0; i < pluginList.count(); i++) {
        QDomElement plugin = pluginList.at(i).toElement();
        QString pluginPath = plugin.attribute("ppath");
        loadPluginFile(pluginPath);
    }

    /// parse and set qDockWidget states
    QList<QAction*> actionList;
    actionList = pluginMenu->actions();
    QDomNodeList dockWidgetList = config.elementsByTagName("dockWidget");
    if (!actionList.isEmpty()) {
        for (int i = 0; i < dockWidgetList.count(); i++) {
            QDomElement dockWidget = dockWidgetList.at(i).toElement();
            QString dockWidgetName = dockWidget.attribute("name");
            bool isChecked = dockWidget.attribute("isChecked").toInt();

            QList<QDockWidget *> dockWidgets = qFindChildren<QDockWidget *>(this);
            if (dockWidgets.size()) {
                for (int i = 0; i < dockWidgets.size(); ++i) {
                    if ( QString(dockWidgets.at(i)->windowTitle()).compare(dockWidgetName) == 0) {
                        dockWidgets.at(i)->setHidden(!isChecked);
                    }
                }
            }

            for (int j = 0; j < actionList.count(); j++) {
                if (actionList.at(j)->text().compare(dockWidgetName) == 0)
                    actionList.at(j)->setChecked(isChecked);
            }
        }
    }

    /// parse and load scene
    QDomNodeList sceneList = config.elementsByTagName("scene");
    for (int i = 0; i < sceneList.count(); i++) {
        QDomElement scene = sceneList.at(i).toElement();
        QString scenePath = scene.attribute("spath");
        if(scenePath.isEmpty() || scenePath.isNull())
            continue;
        else
            doLoad(scenePath.toStdString());
    }

    /// resize the window
    QDomNodeList size = config.elementsByTagName("size");
    this->resize(size.at(0).toElement().attribute("width").toInt(), size.at(0).toElement().attribute("height").toInt());

    QList<QDockWidget *> dockWidgets = qFindChildren<QDockWidget *>(this);
    QDomNodeList dockLocation = config.elementsByTagName("dockWidgetLocation");
    for (int i = 0; i < dockLocation.count(); i++) {
        QDomElement dockWidget = dockLocation.at(i).toElement();
        if (dockWidgets.size()) {
            for (int i = 0; i < dockWidgets.size(); ++i) {
                if ( QString(dockWidgets.at(i)->windowTitle()).compare(dockWidget.attribute("name")) == 0) {
                    if(dockWidget.attribute("isFloating").toInt())
                        dockWidgets.at(i)->setFloating(true);
                    else {
                        switch(dockWidget.attribute("location").toInt()) {
                            case 1: this->addDockWidget(Qt::LeftDockWidgetArea ,dockWidgets.at(i)); break;
                            case 2: this->addDockWidget(Qt::RightDockWidgetArea ,dockWidgets.at(i)); break;
                            case 4: this->addDockWidget(Qt::TopDockWidgetArea ,dockWidgets.at(i)); break;
                            case 8: this->addDockWidget(Qt::BottomDockWidgetArea ,dockWidgets.at(i)); break;
                        }
                    }
                }
            }
        }
    }

    /// tabify all those dock widgets that are at the bottom of the window
    QList<QDockWidget *> widgetList = qFindChildren<QDockWidget *>(this);
    QDockWidget* bottomWidget;
    bool bottomWidgetPresent = false;
    if (widgetList.size()) {
        for (int i = 0; i < widgetList.size(); ++i) {
            if (this->dockWidgetArea(widgetList.at(i)) == 8) {
                if (!bottomWidgetPresent) {
                    bottomWidgetPresent = true;
                    bottomWidget = widgetList.at(i);
                }
                else {
                    this->tabifyDockWidget(bottomWidget, widgetList.at(i));
                }
            }
        }
    }

    /// parse and load cameras
    /// parse and load lightsources
}

void GripMainWindow::camera()
{
    QImage screenshot = viewWidget->takeScreenshot();

    QStringList fileNames; //stores the entire path of the file that it attempts to open
    QString format = "png";
    QStringList filters; //setting file filters
    filters << "PNG Image files (*.png)"
            << "Any files (*)";

    //initializing the File dialog box
    //the static QFileDialog does not seem to be working correctly in Ubuntu 12.04 with unity.
    //as per the documentation it may work correctly with gnome
    //the method used below should work correctly on all desktops and is supposedly more powerful
    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (!fileNames.isEmpty())
        screenshot.save(fileNames.front(), format.toAscii());
    else
        std::cerr << "No file was selected" << std::endl;
}

void GripMainWindow::film()
{
    // recordImageList = new QList<QImage>;

    // recordWidget = new QWidget;
    // recordWidget->resize(recordSize);

    // recordViewWidget = new ViewerWidget();
    // recordViewWidget->setGeometry(100, 100, 800, 600);
    // recordViewWidget->addGrid(20, 20, 1);
    // recordViewWidget->addNodeToScene(worldNode);
    // recordViewWidget->setViewMatrix(0, viewWidget->getViewMatrix());
    // recordViewWidget->getCameraManipulator(0)->setByMatrix(viewWidget->getCameraMatrix(0));

    // QHBoxLayout* hLayout = new QHBoxLayout;
    // hLayout->addWidget(recordViewWidget);

    // recordWidget->setLayout(hLayout);
    // recordWidget->setWindowTitle("Recording Window");
    // recordWidget->show();

    // QTime dieTime = QTime::currentTime().addMSecs(1000);
    // while(QTime::currentTime() < dieTime);

    // _recordVideo = true;
    // slotPlaybackStart();
    // recordImageList->append(recordViewWidget->takeScreenshot());

    // slotPlaybackTimeStep(true);
}

void GripMainWindow::saveVideo()
{
    _recordVideo = false;

    recordWidget->close();
    delete recordViewWidget;
    recordViewWidget = NULL;
    delete recordWidget;
    recordWidget = NULL;

    QString fileName;
    QStringList dirNames; //stores the entire path of the file that it attempts to open
    QString format = "png";
    QStringList filters; //setting file filters
    filters << "PNG Image files (*.png)"
            << "Any files (*)";

    //initializing the File dialog box
    //the static QFileDialog does not seem to be working correctly in Ubuntu 12.04 with unity.
    //as per the documentation it may work correctly with gnome
    //the method used below should work correctly on all desktops and is supposedly more powerful
    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::Directory);
    //dialog.setOption(QFileDialog::ShowDirsOnly, true);
    if (dialog.exec())
        dirNames = dialog.selectedFiles();

    if (dirNames.isEmpty()) {
        std::cerr << "No file was selected" << std::endl;
        return;
    } else {
        for(int i = 0; i < recordImageList->count(); ++i) {
            recordImageList->at(i).save(fileName.sprintf("%s/image%06d", dirNames.front().toStdString().c_str(), i), format.toAscii());
        }
    }
    delete recordImageList;
    recordImageList = NULL;
}
