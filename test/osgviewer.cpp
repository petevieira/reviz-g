
// OpenSceneGraph headers
#include <osg/io_utils>
#include <osgViewer/CompositeViewer>

// osgReviz headers
#include "osgReviz/osgUtils.h"
#include "osgReviz/Shapes.h"

// osgUrdf headers
#include "osgUrdf/osgUrdf.h"

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
double totalAngle = .5; // radians
double dAngle = 0.001; // radians

void moveJoint(osgUrdf::Robot* robot, int i)
{
  double angle = dAngle;
  osg::Matrix m;
  m = robot->getJoint(i)->getMatrix();
  m.preMultRotate(osg::Quat(angle, robot->getJointAxis(i)));
  robot->getJoint(i)->setMatrix(m);
}

int main( int argc, char** argv )
{
  if (argc < 3) {
    std::cerr << "Error. Incorrect Usage. See below...\n"
              << "    Usage:   ./osgviewer <full_path_to_urdf_directory> <urdf_filename>\n"
              << "    Example: ./osgviewer \"/home/user/urdf/robots/\" \"robot.urdf\""
              << std::endl;
   exit(-1);
  }

  // get urdf path
  std::string filePath = std::string(argv[0]);
  // std::string curDir = filePath.substr(0, filePath.find_last_of("/"));
  std::string curDir = argv[1];//"/home/pevieira/Downloads/ARMURDF_v2/robots/";
  std::string urdfDir = curDir;
  std::string urdfName = argv[2];//"ARMURDF.urdf";

  // create gui
  osg::Group* root = new osg::Group();
  osgViewer::View* view = osgReviz::createView(0, 0, 800, 800, root);
  osgViewer::CompositeViewer* viewer = new osgViewer::CompositeViewer();
  viewer->addView(view);

  // add robot.urdf to visualizer
  osgUrdf::Robot* robot = new osgUrdf::Robot(urdfName, urdfDir);
  osg::MatrixTransform* tf = robot->getRootMatrixTransform();
  osg::Matrix osgPose;
  osgPose.preMultRotate(osg::Quat(M_PI, osg::Vec3(0,1,0)));
  tf->setMatrix(osgPose);

  root->addChild(robot);

  std::cout << "\nNum joints: " << robot->getNumJoints() << std::endl;
  std::cout << "Num links : " << robot->getNumLinks() << std::endl;

  // for (size_t i = 0; i < robot->getNumJoints(); ++i) {
  //   std::cout << "Joint " << robot->getJoint(i)->getName() << "\n" << osgReviz::transpose(robot->getJoint(i)->getMatrix()) << std::endl;
  //   std::cout << "  Axis " << robot->getJointAxis(i) << std::endl;
  // }

  // add box to visualizer
  // osg::MatrixTransform* boxTf = new osg::MatrixTransform();
  // osg::Matrix boxPose;
  // boxPose.makeTranslate(0, 0, 3);
  // boxTf->setMatrix(boxPose);
  // osgReviz::Sphere* sphere = new osgReviz::Sphere(osg::Vec3(0, 0, 0), .1, osg::Vec4(1,0,0,1));
  // tf->addChild(sphere);

  // root->addChild(boxTf);

  robot->printChildren();

  bool printTF = true;
  int cnt = 0;
  int joint = 0;
  std::cout << "moving joint " << robot->getJoint(joint)->getName() << " now " << std::endl;
  while(!viewer->done()) {
    viewer->frame();

    if(joint < (int)robot->getNumJoints()) {
      if(printTF) {
        std::cout << robot->getJoint(joint)->getName() << "\n" << osgReviz::transpose(robot->getJoint(joint)->getMatrix()) << std::endl;
        std::cout << "Axis: " << robot->getJointAxis(joint) << std::endl;
        printTF = false;
      }
      if(cnt < totalAngle/dAngle) {
        moveJoint(robot, joint);
        ++cnt;
      } else {
        ++joint;
        cnt = 0;
        std::cout << "moving " << robot->getJoint(joint)->getName() << " now " << std::endl;
        printTF = true;
      }
    }


  }
}
#endif
