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
 * \file osgModel.h
 * \brief Model to OpenSceneGraph conversion class
 */

#ifndef OSGMODEL_H
#define OSGMODEL_H

// Standard headers
#include <map>
#include <iostream>
#include <fstream>

// OpenSceneGraph headers
#include <osg/Geode>
#include <osg/Matrix>
#include <osg/MatrixTransform>

#include "osgReviz/osgUtils.h"

namespace osgModel {


class Robot : public osg::Group
{
public:
  Robot();

  Robot(const std::string &urdfFileName, const std::string &urdfFileDirectory);

  ~Robot();

  void parseUrdfRobot(const std::string &urdfFileName, const std::string &urdfFileDirectory);

  boost::shared_ptr<urdf::ModelInterface> parseUrdfString(const std::string &urdfFileName, const std::string &urdfFileDirectory);

  void convertUrdfToOsg(boost::shared_ptr<const urdf::ModelInterface> urdfModel);

  void createRobotRecursively(boost::shared_ptr<const urdf::ModelInterface> urdfModel, boost::shared_ptr<const urdf::Link> urdfLink, osg::MatrixTransform* osgJoint);

  osg::MatrixTransform* createOsgJoint(boost::shared_ptr<const urdf::Joint> urdfJoint);

  osg::Node* createOsgLink(boost::shared_ptr<const urdf::Link> urdfLink);

  std::string getUrdfMeshFilePath(boost::shared_ptr<const urdf::Link> urdfLink);

  osg::Matrix urdfPoseToOsgMatrix(const urdf::Pose urdfPose);

  osg::MatrixTransform* getRootMatrixTransform();

private:

  std::string _robotPackageDirectory;
  std::string _pathToRobot;
  osg::MatrixTransform* _rootTF;

};

};

#endif // OSGMODEL_H