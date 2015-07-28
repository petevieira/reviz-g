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
 * \file osgUtils.h
 * \brief Utility functions for OpenSceneGraph
 */

#ifndef OSG_UTILS_H
#define OSG_UTILS_H

// OpenSceneGraph includes
#include <osgViewer/View>
#include <osgGA/OrbitManipulator>
#include <osg/io_utils>
#include <osg/StateSet>
#include <osg/PolygonMode>
#include <osg/Material>
#include <osg/BlendFunc>
#include <osgDB/ReadFile>

#if HAVE_EIGEN
// Eigen includes
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#endif

// C++ Standard Library includes
#include <iostream>

/**
 * \namespace osgReviz
 * \brief Namespace to encompass the general OpenSceneGraph utilities
 */
namespace osgReviz {

/**
 * \brief Creates a osgViewer::View pointer with the specified location
 * of the upper-left corner of the window, width, height and scene.
 * \param x X-coordinate of the upper-left corner of the window
 * \param x Y-coordinate of the upper-left corner of the window
 * \param w Width of the window
 * \param h Height of the window
 * \param scene A osg::Node pointer to be put into the viewer window
 * \return osgViewer::View pointer
 */
osgViewer::View* createView(int x, int y, int w, int h, osg::Node* scene = NULL);

inline osg::ref_ptr<osg::Node> convertStlToOsgNode(std::string stlFile)
{
  osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(stlFile);
  return node;
}

#if HAVE_EIGEN
/**
 * \brief Convert Eigen::Isometry3d matrix to an osg::Matrix.
 * osg::Matrix is transposed.
 * \param tf Eigen::Isometry3d to be converted. Passed in by reference
 * \return osg::Matrix
 */
inline osg::Matrix eigToOsgMatrix(const Eigen::Isometry3d& tf)
{
  osg::Matrix output;
  for (ushort i=0; i<4; ++i) {
    for (ushort j=0; j<4; ++j) {
      output(i,j) = tf(j,i);
    }
  }
  return output;
}

/**
 * \brief Convert Eigen::Isometry3f matrix to an osg::Matrix.
 * osg::Matrix is transposed.
 * \param tf Eigen::Isometry3f to be converted. Passed in by reference
 * \return osg::Matrix
 */
inline osg::Matrix eigToOsgMatrix(const Eigen::Isometry3f& tf)
{
  osg::Matrix output;
  for (ushort i=0; i<4; ++i) {
    for (ushort j=0; j<4; ++j) {
      output(i,j) = tf(j,i);
    }
  }

  return output;
}

/**
 * \brief Convert Eigen::Vector3d vector to an osg::Vec3d
 * \param vec Eigen::Vector3d to be converted. Passed in by reference
 * \return osg::Vec3d
 */
inline osg::Vec3 eigToOsgVec3(const Eigen::Vector3d& vec)
{
  osg::Vec3 output;
  for (ushort i=0; i<3; ++i) {
    output[i] = vec[i];
  }
  return output;
}
#endif

/**
 * \brief Adds a wireframe mode to the node passed in
 * \param[out] node Node for which to add a wireframe mode
 * \return void
 * \todo Fix everything
 */
inline void addWireFrameMode(osg::Node* node)
{
  if (!node) {
    std::cerr << "Invalid node. Line " << __LINE__ << " of " << __FILE__ << std::endl;
    return;
  }

  osg::PolygonMode* polyModeObj;

  polyModeObj = dynamic_cast<osg::PolygonMode*>(node->getOrCreateStateSet()->
                                                getAttribute(osg::StateAttribute::POLYGONMODE));

  if (!polyModeObj) {
    polyModeObj = new osg::PolygonMode;
    node->getOrCreateStateSet()->setAttribute(polyModeObj);
  }
}

/**
 * \brief Turns on wireframe mode for the passed in node
 * If it doesn't have a wireframe mode, one is created.
 * \param node Node for which to turn on/off wireframe mode
 * \return void
 */
inline void setWireFrameEnable(osg::Node* node, bool enable)
{
  if (!node) {
    std::cerr << "Invalid node. Line " << __LINE__ << " of " << __FILE__ << std::endl;
    return;
  }

  if (!node->getStateSet()) {
    addWireFrameMode(node);
  }

  osg::PolygonMode* polyModeObj;
  polyModeObj = dynamic_cast<osg::PolygonMode*>(node->getStateSet()->
                                                getAttribute(osg::StateAttribute::POLYGONMODE));

  if (!polyModeObj) {
    polyModeObj = new osg::PolygonMode;
    node->getStateSet()->setAttribute(polyModeObj);
  }

  if (enable) {
    polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);
  } else {
    polyModeObj->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL);
  }
}

/**
 * \brief Set the transparency value of a node
 * Reference: OSG Cookbook p. 239
 * \param node Node of which to change the transparency value
 * \param transparencyValue New transparency value for the node (between 0 and 1)
 * \return void
 */
inline void setTransparency(osg::Node* node, float transparencyValue)
{
  if (!node->getOrCreateStateSet()->getAttribute(osg::StateAttribute::MATERIAL)) {
     node->getOrCreateStateSet()->setAttribute(new osg::Material);
     std::cerr << "Created new material" << std::endl;
  }
  if (!node->getOrCreateStateSet()->getAttribute(osg::StateAttribute::BLENDFUNC)) {
     node->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);
     std::cerr << "Created new blendfunc" << std::endl;
  }

  node->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
  osg::ref_ptr<osg::Material> mat = (osg::Material*)node->getOrCreateStateSet()->getAttribute(osg::StateAttribute::MATERIAL);
  osg::Vec4 diffuse = mat->getDiffuse(osg::Material::FRONT_AND_BACK);
  std::cerr << "Diffuse: " << diffuse << std::endl;
  std::cerr << "Ambient: " << mat->getAmbient(osg::Material::FRONT_AND_BACK) << std::endl;
  std::cerr << "Emissive:" << mat->getEmission(osg::Material::FRONT_AND_BACK) << std::endl;
  std::cerr << "Specular:" << mat->getSpecular(osg::Material::FRONT_AND_BACK) << std::endl;

  diffuse.set(diffuse.r(), diffuse.g(), diffuse.b(), transparencyValue);
  mat->setDiffuse(osg::Material::FRONT_AND_BACK, diffuse);
//    mat->setAlpha(osg::Material::FRONT_AND_BACK, transparencyValue);
  node->getOrCreateStateSet()->setAttributeAndModes(mat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
}

} // end of osgReviz namespace

#endif // OSG_UTILS_H
