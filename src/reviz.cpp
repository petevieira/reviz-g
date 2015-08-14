/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

#include <QtGui/QApplication>
#include "include/RevizMainWindow.h"
#include <QtGui/QTabWidget>
#include <X11/Xlib.h>

/**
 * \brief Shows the usgae message for grip, by display
 * the command line argument options the user can use
 * \param ostr An ostream operator like std::cout or std::cerr
 */
void showUsage(std::ostream &ostr)
{
    ostr <<
            "Usage: reviz <COMMAND> [OPTION]\n"
            "Visualization tool for robotics simulators\n"
            "Commands\n"
            "  -d|--debug                Print debug statements\n"
            "  -f|--file sceneFile       Load scene \"sceneFile\" (.urdf, .sdf)\n"
            "  -c|--config configFile    Load workspace \"configFile\" (.gripconfig)\n"
            "  -h|--help                 Show this help message\n"
            "\n"
            "Examples\n"
            "  reviz -d\n"
            "  reviz -d -f ~/sceneFiles/robot.urdf\n"
            "  reviz --help\n";
}

/**
 * \brief Parses command line arguments and starts the grip application
 * \param argc Number of arguments given by user
 * \param argv Vector of arguments given by user. argv[0] is the name of the program
 */
int main(int argc, char *argv[])
{
    // Variables for command line parsing
    bool debug = false;
    std::string sceneFilePath;
    std::string configFilePath;

    // Parse command line arguments. See "showUsage" function for description
    std::vector<std::string> args(argv, argv + argc);
    for (size_t i = 1; i < args.size(); ++i) {
        if ("-d" == args[i] || "--debug" == args[i]) {
            debug = true;
        } else if ("-f" == args[i] || "--file" == args[i]) {
            std::cerr << "got f" << std::endl;
            sceneFilePath = args[i+1];
        } else if ("-c" == args[i] || "--config" == args[i]) {
            configFilePath = args[i+1];
        } else if ("-h" == args[i] || "--help" == args[i]) {
            showUsage(std::cerr);
            exit(1);
        }
    }

    // Initialize Xlib support for concurrent threads
    // XInitThreads();

    // Start grip
	QApplication app(argc, argv);

#if 0

    printf("%d\n", debug);
    QMainWindow *gui = new QMainWindow();
    gui->setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    gui->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    RevizMainWindow *window  = new RevizMainWindow(gui, debug, sceneFilePath, configFilePath);
    QMainWindow *launchTab = new QMainWindow();
    QMainWindow *evrTab = new QMainWindow();

    QDockWidget *dw1 = new QDockWidget("Reviz", gui);
    QDockWidget *dw2 = new QDockWidget("Launch", gui);
    QDockWidget *dw3 = new QDockWidget("EVRs", gui);

    dw1->setWidget(window);
    dw2->setWidget(launchTab);
    dw3->setWidget(evrTab);

    gui->addDockWidget(Qt::TopDockWidgetArea, dw1);
    gui->addDockWidget(Qt::TopDockWidgetArea, dw2);
    gui->addDockWidget(Qt::TopDockWidgetArea, dw3);
    gui->tabifyDockWidget(dw1, dw2);
    gui->tabifyDockWidget(dw2, dw3);
    dw1->raise();

    // Add tabs to main window
    // tab->addTab(window, QString("Viz"));
    // tab->addTab(launchTab, QString("launch"));
    // tab->addTab(evrTab, QString("evr"));

    window->Toolbar();
    // window->setMinimumSize(dw1->width(), dw1->height());

    // tab->showMaximized();
    gui->showMaximized();

#else
    QTabWidget *tab = new QTabWidget();
    RevizMainWindow *window  = new RevizMainWindow(tab, debug, sceneFilePath, configFilePath);
    QMainWindow *launchTab = new QMainWindow();
    QMainWindow *evrTab = new QMainWindow();

    // Add tabs to main window
    tab->addTab(window, QString("Viz"));
    tab->addTab(launchTab, QString("launch"));
    tab->addTab(evrTab, QString("evr"));

    window->Toolbar();
    window->setMinimumSize(tab->width(), tab->height());

    tab->showMaximized();

#endif

    QFile File("resources/dark-orange.qss");
    if (!File.open(QFile::ReadOnly)) {
      std::cerr << "Error opening " << File.fileName().toStdString() << std::endl;
      exit(-1);
    }
    QString styleSheet = QLatin1String(File.readAll());
    if (styleSheet.isEmpty()) {
      std::cerr << "Failed to read " << File.fileName().toStdString() << std::endl;
      exit(-1);
    }

    app.setStyleSheet(styleSheet);

    return app.exec();
}
