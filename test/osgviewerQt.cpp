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

#if 0
int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  // get urdf path
  std::string filePath = std::string(argv[0]);
  // std::string curDir = filePath.substr(0, filePath.find_last_of("/"));
  std::string curDir = "/home/pevieira/Downloads/ARMURDF/robots/";
  std::string urdfDir = curDir;
  std::string urdfName = "ARMURDF.URDF";

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

#else
int main( int argc, char** argv )
{
  QApplication app(argc, argv);

  // get urdf path
  std::string filePath = std::string(argv[0]);
  // std::string curDir = filePath.substr(0, filePath.find_last_of("/"));
  std::string curDir = "/home/pevieira/Downloads/ARMURDF/robots/";
  std::string urdfDir = curDir;
  std::string urdfName = "ARMURDF.URDF";

  // create gui
  RevizMainWindow* mainWindow = new RevizMainWindow();

  // add robot.urdf to visualizer
  osgUrdf::Robot* robot = new osgUrdf::Robot(urdfName, urdfDir);
  osg::MatrixTransform* tf = robot->getRootMatrixTransform();
  osg::Matrix osgPose;
  osgPose.preMultRotate(osg::Quat(M_PI, osg::Vec3(0,1,0)));
  tf->setMatrix(osgPose);
  robot->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON
                                                   | osg::StateAttribute::PROTECTED);
  mainWindow->viewWidget->addNodeToScene(robot);

  // add box to visualizer
  osg::MatrixTransform* boxTf = new osg::MatrixTransform();
  osg::Matrix boxPose;
  boxPose.makeTranslate(0, 0, 3);
  boxTf->setMatrix(boxPose);
  osgReviz::Sphere* sphere = new osgReviz::Sphere(osg::Vec3(0, 0, 0), .1, osg::Vec4(1,0,0,1));
  tf->addChild(sphere);
  sphere->setName("Sphere");

  mainWindow->viewWidget->addNodeToScene(boxTf);

  // mainWindow->viewWidget->addGrid(20, 20, 1);

  // mainWindow->setMinimumSize(tab->width(), tab->height());

  mainWindow->showMaximized();

  // app.setStyleSheet(loadStyleSheet("resources/dark-orange.qss"));

  return app.exec();
}
#endif