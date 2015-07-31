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

#ifndef OSGURDF_H
#define OSGURDF_H

// Standard headers
#include <map>
#include <iostream>
#include <fstream>

// OpenSceneGraph headers
#include <osg/Geode>
#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/CullFace>
#include <osgDB/ReadFile>

// urdfdom headers
#include <urdf_parser/urdf_parser.h>
#include <urdf_world/world.h>

#include "osgReviz/osgUtils.h"

namespace osgUrdf {

/// Array of osg::Group pointers for the dart::dynamics::BodyNode visualization objects


class Robot : public osg::Group
{
public:
  Robot();

  ~Robot();

  void parseUrdfRobot(const std::string &urdfFileName, const std::string &urdfFileDirectory);

  boost::shared_ptr<urdf::ModelInterface> parseUrdfString(const std::string &urdfFileName, const std::string &urdfFileDirectory);

  void convertUrdfToOsg(boost::shared_ptr<const urdf::ModelInterface> urdfModel);

  void createRobotRecursively(boost::shared_ptr<const urdf::ModelInterface> urdfModel, boost::shared_ptr<const urdf::Link> urdfLink, osg::MatrixTransform* osgJoint);

  osg::MatrixTransform* createOsgJoint(boost::shared_ptr<const urdf::Joint> urdfJoint);

  osg::Node* createOsgLink(boost::shared_ptr<const urdf::Link> urdfLink);

  std::string getUrdfMeshFilePath(boost::shared_ptr<const urdf::Link> urdfLink);

  osg::Matrix urdfPoseToOsgMatrix(const urdf::Pose urdfPose);

private:

  std::string _robotPackageDirectory;
  std::string _pathToRobot;
  osg::MatrixTransform* _rootTF;

};

};

#endif // OSGURDF_H