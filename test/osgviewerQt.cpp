#include "include/ViewerWidget.h"
#include "osgReviz/Shapes.h"
#include "QApplication"
#include <osg/io_utils>
#include <QtGui/QMainWindow>
#include "osgUrdf/osgUrdf.h"
#include "include/RevizMainWindow.h"

QString loadStyleSheet(QString pathToFile)
{
  QFile File(pathToFile);
  if (!File.open(QFile::ReadOnly)) {
    std::cerr << "Error opening " << File.fileName().toStdString() << std::endl;
    exit(-1);
  }

  QString styleSheet = QLatin1String(File.readAll());
  if (styleSheet.isEmpty()) {
    std::cerr << "Failed to read " << File.fileName().toStdString() << std::endl;
    exit(-1);
  }

  return styleSheet;
}

int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  // get urdf path
  std::string filePath = std::string(argv[0]);
  std::string curDir = filePath.substr(0, filePath.find_last_of("/"));
  std::string urdfDir = curDir + "/..";
  std::string urdfName = "robot.urdf";

  // create gui
  QTabWidget* tab = new QTabWidget();
  RevizMainWindow* mainWindow = new RevizMainWindow(tab);
  QMainWindow* launchWindow = new QMainWindow();
  QMainWindow* evrs = new QMainWindow();
  tab->addTab(mainWindow, QString("Reviz"));
  tab->addTab(launchWindow, QString("Launch"));
  tab->addTab(evrs, QString("EVRs"));

  // add robot.urdf to visualizer
  osgUrdf::Robot* robot = new osgUrdf::Robot(urdfName, urdfDir);
  osg::MatrixTransform* tf = robot->getRootMatrixTransform();
  osg::Matrix osgPose;
  osgPose.preMultRotate(osg::Quat(M_PI, osg::Vec3(0,1,0)));
  tf->setMatrix(osgPose);
  mainWindow->viewWidget->addNodeToScene(robot);

  mainWindow->setMinimumSize(tab->width(), tab->height());

  tab->showMaximized();

  // app.setStyleSheet(loadStyleSheet("resources/dark-orange.qss"));

  return app.exec();
}
