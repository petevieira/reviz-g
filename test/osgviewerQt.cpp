#include "include/ViewerWidget.h"
#include "osgReviz/Shapes.h"
#include "QApplication"
#include <osg/io_utils>
#include <QtGui/QMainWindow>
#include "osgUrdf/osgUrdf.h"

//int callbackTest()
//{
//    osg::Group* root = new osg::Group();

//    // Create cylinder
//    osg::Geode* geode = new osg::Geode;
//    osg::TessellationHints* hints = new osg::TessellationHints;
//    osg::ShapeDrawable* cylinder = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.0f, 0.0f, 0), .01, 1), hints);
//    cylinder->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
//    geode->addDrawable(cylinder);
//    osg::Geode* geode2 = new osg::Geode;
//    osg::ShapeDrawable* cylinder2 = clone(cylinder);
//    cylinder2->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
//    geode2->addDrawable(cylinder2);

//    // Create dynamics TF
//    osg::MatrixTransform* rootTF = new osg::MatrixTransform;
//    osg::MatrixTransform* tf1 = new osg::MatrixTransform;
//    osg::MatrixTransform* tf2 = new osg::MatrixTransform;
//    tf1->setDataVariance(osg::Object::DYNAMIC);
//    tf1->setUpdateCallback(new LineCallback);
//    tf2->setDataVariance(osg::Object::DYNAMIC);
////    tf2->setUpdateCallback(new LineCallback);
//    osg::Matrix m;
//    m.makeTranslate(0.6, 0, 0);
//    tf1->setMatrix(m);
//    tf1->addChild(geode);
//    tf2->addChild(geode2);

//    // Add TF to root
//    rootTF->addChild(tf1);
//    rootTF->addChild(tf2);
//    root->addChild(rootTF);

//    // switch off lighting as we haven't assigned any normals.
//    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

//    osgViewer::CompositeViewer* viewer = new osgViewer::CompositeViewer();
//    osgViewer::View* view = createView(0, 0, 640, 480, root);
//    view->setUpViewOnSingleScreen(0);
//    viewer->addView(view);

//    while(!viewer->done()) {
//        viewer->frame();
//    }

//    return 0;
//}

int main( int argc, char** argv )
{
    QApplication app(argc, argv);

#if 0

    QHBoxLayout* layout = new QHBoxLayout();
    // QHBoxLayout* mnlayout = new QHBoxLayout();
    QTabWidget* tab = new QTabWidget();
    QMainWindow* mainWindow = new QMainWindow(tab);
    // QMainWindow* launchWindow = new QMainWindow();
    ViewerWidget* viewWidget = new ViewerWidget(mainWindow);

    layout->addWidget(mainWindow);
    layout->setSizeConstraint(QLayout::SetMaximumSize);
    // mnlayout->addWidget(viewWidget);
    mainWindow->setCentralWidget(viewWidget);

    viewWidget->addNodeToScene(new osgReviz::Sphere(osg::Vec3(0,0,1), 0.5, osg::Vec4(1,0,1,1)));
    // viewWidget->addGrid(20, 20, 1);

    tab->addTab(mainWindow, QString("ASD"));
    // tab->addTab(launchWindow, QString("launch"));
    tab->show();

#else
    QWidget* window = new QWidget();

    QHBoxLayout* layout = new QHBoxLayout;
    QMainWindow* mainWindow = new QMainWindow();
    ViewerWidget* viewWidget = new ViewerWidget();

    layout->addWidget(mainWindow);

    mainWindow->setCentralWidget(viewWidget);

    osgUrdf::Robot* robot = new osgUrdf::Robot();
    robot->parseRobot("robot.urdf", "/home/pevieira/otherRepos/reviz/test");
    viewWidget->addNodeToScene(robot);
    viewWidget->addGrid(20, 20, 1);

    window->setLayout(layout);
    window->setGeometry(100, 100, 800, 600);
    window->show();
#endif

    return app.exec();
}
