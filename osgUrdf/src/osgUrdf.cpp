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
 * \file osgUrdf.h
 * \brief URDF to OpenSceneGraph conversion class
 */

// Standard headers
#include <string>

// OpenSceneGraph headers
#include <osgDB/ReadFile>

// Local headers
#include "osgUrdf.h"
#include <fstream>

using namespace osgUrdf;

Robot::Robot()
{
}

Robot::~Robot()
{
}

void Robot::parseUrdfRobot(const std::string &urdfFileName, const std::string &urdfFileDirectory)
{
  this->robotPackageDirectory = urdfFileDirectory;

  // get main urdf object
  boost::shared_ptr<urdf::ModelInterface> model;
  model = parseUrdfString(urdfFileName, urdfFileDirectory);
  if(!model) {
    std::cerr << __LINE__ << ": Null urdf model" << std::endl;
  }

  // convert it to openscenegraph
  convertUrdfToOsg(model);
}

boost::shared_ptr<urdf::ModelInterface> Robot::parseUrdfString(const std::string &urdfFileName, const std::string &urdfFileDirectory)
{
  // Parse urdf file string
  if (urdfFileName.empty()) {
    std::cerr << __LINE__ << ": Empty urdf file name" << std::endl;
    // return nullptr;
  }

  _pathToRobot = urdfFileDirectory + "/" + urdfFileName;
  // std::replace(_pathToRobot.begin(), _pathToRobot.end(), '\\', '/');
  // _pathToRobot = _pathToRobot.substr(0, _pathToRobot.rfind("/") + 1);

  if (urdfFileDirectory.empty()) {
    std::cerr << __LINE__ << ": Empty urdf directory: " << urdfFileDirectory << std::endl;
  }

  std::string xml_model_string;
  std::fstream xml_file(_pathToRobot.c_str(), std::fstream::in);

  if(!xml_file.good()) {
    std::cerr << "Could not find file: " << _pathToRobot << std::endl;
  }

  while(xml_file.good()) {
    std::string line;
    std::getline(xml_file, line);
    xml_model_string += line + "\n";
  }

  xml_file.close();

  // Parse urdf
  boost::shared_ptr<urdf::ModelInterface> urdfModelPtr = urdf::parseURDF(xml_model_string);
  if (!urdfModelPtr) {
    std::cerr << __LINE__ << ": null urdf model ptr" << std::endl;
    // return nullptr;
  }

  return urdfModelPtr;
}

void Robot::convertUrdfToOsg(boost::shared_ptr<const urdf::ModelInterface> urdfModel)
{
  boost::shared_ptr<const urdf::Link> urdfRootLink = urdfModel->getRoot();

  urdfRootLink = urdfRootLink->child_links[0];
  boost::shared_ptr<const urdf::Joint> urdfRootJoint = urdfRootLink->parent_joint;

  _rootTF = new osg::MatrixTransform(urdfPoseToOsgMatrix(urdfRootJoint->parent_to_joint_origin_transform));
  this->addChild(_rootTF);
  _rootTF->addChild(createOsgLink(urdfModel, urdfRootJoint));

  createRobotRecursively(urdfModel, urdfRootLink, _rootTF);

  osg::Matrix mRot, mTrns;
  mRot.makeRotate(M_PI, osg::Vec3(0, 0, 1));
  mTrns.makeTranslate(osg::Vec3(0, 0, .5));
  _rootTF->setMatrix(mRot * mTrns);

    // osg::Material* mat = (osg::Material*)osgRobotRoot->getChild(0)->
    //         getOrCreateStateSet()->getAttribute(osg::StateAttribute::MATERIAL);
    // this->getOrCreateStateSet()->setAttribute(mat);
    // this->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);
}

void Robot::createRobotRecursively(boost::shared_ptr<const urdf::ModelInterface> urdfModel, boost::shared_ptr<const urdf::Link> urdfLink, osg::MatrixTransform* osgJoint)
{
  std::cerr << "Link: " << urdfLink->name << ". # Children: " << urdfLink->child_joints.size() << std::endl;

  for (size_t i = 0; i < urdfLink->child_joints.size(); ++i) {

    // get joint i of passed-in link
    boost::shared_ptr<urdf::Joint> urdfJoint = urdfLink->child_joints[i];
    osg::MatrixTransform *osgChildJoint;
    osg::Node *osgLink;
    std::cerr << "    Child[" << i << "]: " << urdfModel->getLink(urdfJoint->child_link_name)->name << std::endl;  
    // create osg child joint
    osgChildJoint = createOsgJoint(urdfJoint);
    osgJoint->addChild(osgChildJoint);

    // create osg child link
    osgLink = createOsgLink(urdfModel, urdfJoint);
    osgChildJoint->addChild(osgLink);

    createRobotRecursively(urdfModel, urdfModel->getLink(urdfJoint->child_link_name), osgJoint);
  }
}

osg::MatrixTransform* Robot::createOsgJoint(boost::shared_ptr<const urdf::Joint> urdfJoint)
{
  // create osg joint and set it's pose from the urdf link
  osg::MatrixTransform *osgJoint = new osg::MatrixTransform;

  osgJoint->setMatrix(urdfPoseToOsgMatrix(urdfJoint->parent_to_joint_origin_transform));
  std::cerr << "osgTF: \n" << osgJoint->getMatrix() << std::endl;

  return osgJoint;
}

osg::Node* Robot::createOsgLink(boost::shared_ptr<const urdf::ModelInterface> urdfModel, boost::shared_ptr<const urdf::Joint> urdfJoint)
{
  std::string meshFilePath;
  boost::shared_ptr<const urdf::Link> urdfLink;
  osg::Node* osgLink;

  // get the urdf link
  urdfLink = urdfModel->getLink(urdfJoint->child_link_name);

  // get urdf mesh file path
  if (urdfLink->visual->geometry->type == urdf::Geometry::MESH) {
    meshFilePath = getUrdfMeshFilePath(urdfLink);
  } else {
    std::cout << "No visual for the link" << std::endl;
  }

  // convert stl to osg::Node*
  osgLink = osgDB::readNodeFile(meshFilePath);

  if(!osgLink) {
    std::cerr << "Null osgLink" << std::endl;
  }

  // osgLink->getOrCreateStateSet()->setAttribute(new osg::Material);
  // osg::Material* mat = (osg::Material*)osgLink->getOrCreateStateSet()->getAttribute(osg::StateAttribute::MATERIAL);
  // mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(.5, .5, .5, 1.0));
  return osgLink;
}

std::string Robot::getUrdfMeshFilePath(boost::shared_ptr<const urdf::Link> urdfLink)
{
  size_t num = std::string::npos;

  urdf::Mesh *urdfMesh = dynamic_cast<urdf::Mesh*>(urdfLink->visual->geometry.get());
  if (urdfMesh) {
    std::string meshFilename = urdfMesh->filename;
    num = meshFilename.find("package://");
    if (num < std::string::npos) {
      meshFilename.erase(num, num+9);
    } else {
      num = meshFilename.find("file:");
      if (num < std::string::npos) {
        meshFilename.erase(num, num+5);
      } else {
        std::cerr << "Didn't find \"package://\" or \"filename:\"" << std::endl;
      }
    }

    // meshFilename = this->robotPackageDirectory + meshFilename;
    std::cerr << "Meshfile: " << meshFilename << std::endl;
    return meshFilename;
  } else {
    std::cout << "The URDF for link claims to be a mesh but cannot by dynamically casted as on!" << std::endl;
    return "No name";
  }
}

osg::Matrix Robot::urdfPoseToOsgMatrix(const urdf::Pose urdfPose)
{
  osg::Matrix osgPose;
  std::cerr << "TF: " << urdfPose.position.x << ", " << urdfPose.position.y << ", " << urdfPose.position.z << " | " << urdfPose.rotation.w << ", " << urdfPose.rotation.x << ", " << urdfPose.rotation.y << ", " << urdfPose.rotation.z << std::endl;
  osgPose.makeTranslate(urdfPose.position.x,
                        urdfPose.position.y,
                        urdfPose.position.z);
  osgPose.preMultRotate(osg::Quat(
                     urdfPose.rotation.x,
                     urdfPose.rotation.y,
                     urdfPose.rotation.z,urdfPose.rotation.w));


  return osgPose;
}