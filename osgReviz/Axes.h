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
 * \file Axes.h
 * \brief Class that subclasses osg::Geode to create x,y,z axes
 */

#ifndef AXES_H
#define AXES_H

// OpenSceneGraph includes
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osg/LineWidth>
#include <osg/Matrix>
#include <osg/MatrixTransform>

/**
 * \namespace osgReviz
 * \brief Namespace for all the classes that are only dependent upon OpenSceneGraph
 */
namespace osgReviz {

/**
 * \class Axes Axes.h
 * \brief Class that subclasses osg::Geode to create x,y,z axes
 */
class Axes : public osg::Geometry
{
public:

    /**
     * \brief Constructor for Axes.
     * \param scale Scale factor for length of axes
     */
    inline Axes(float scale = 0.1)
    {
        _verts = new osg::Vec3Array(4);
        _colors = new osg::Vec4Array;
        _lineWidth = new osg::LineWidth;

        this->_createAxes();
        this->setScale(scale);
        this->setLineWidth(1.0f);
    }
    
    /**
     * \brief Set the scale factor of the axes
     * \param newScale New scale factor the axes
     * \return void
     */
    inline void setScale(float newScale)
    {
        (*_verts)[0].set(0,0,0);        // origin
        (*_verts)[1].set(newScale,0,0); // x-axis endpoint
        (*_verts)[2].set(0,newScale,0); // y-axis endpoint
        (*_verts)[3].set(0,0,newScale); // z-axis endpoint
        
        // Move vertices to VertexBuffer
        this->setVertexArray(_verts);
    }

    /**
     * \brief Sets the colors of the axes
     * \param xAxis osg::Vec4 reference for the color of the x-axis, in rgba format in range (0,1)
     * \param yAxis osg::Vec4 reference for the color of the y-axis, in rgba format in range (0,1)
     * \param zAxis osg::Vec4 reference for the color of the z-axis, in rgba format in range (0,1)
     * \return void
     */
    inline void setColors(const osg::Vec4& xAxis, const osg::Vec4& yAxis, const osg::Vec4& zAxis)
    {
        (*_colors)[0] = xAxis;
        (*_colors)[1] = yAxis;
        (*_colors)[2] = zAxis;
        this->setColorArray(_colors);
    }

    /**
     * \brief Sets the width of the axes
     * \param newLineWidth The new line width to use
     * \return void
     */
    inline void setLineWidth(float newLineWidth)
    {
        _lineWidth->setWidth(newLineWidth);
        this->getOrCreateStateSet()->setAttribute(_lineWidth);
    }

protected:
    
    /**
     * \brief Define the axes elements indices. These indices correspond to
     * the vertices in the _verts array.
     * \return void
     */
    inline void _createAxes()
    {
        osg::DrawElementsUShort* x_elem =
                new osg::DrawElementsUShort(osg::PrimitiveSet::LINES, 0);
        x_elem->push_back(0); x_elem->push_back(1);
        this->addPrimitiveSet(x_elem);
        _colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
        
        osg::DrawElementsUShort* y_elem =
                new osg::DrawElementsUShort(osg::PrimitiveSet::LINES, 0);
        y_elem->push_back(0); y_elem->push_back(2);
        this->addPrimitiveSet(y_elem);
        _colors->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
        
        osg::DrawElementsUShort* z_elem =
                new osg::DrawElementsUShort(osg::PrimitiveSet::LINES, 0);
        z_elem->push_back(0); z_elem->push_back(3);
        this->addPrimitiveSet(z_elem);
        _colors->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
        
        this->setColorArray(_colors);
        this->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    }
    
    /// Array of vertices defining the endpoints of the axes
    osg::Vec3Array* _verts;

    /// Array of colors defining the color the axes
    osg::Vec4Array* _colors;

    /// Line width pointer
    osg::LineWidth* _lineWidth;
    
}; // end class Axes

} // end namespace osgReviz

#endif // AXES_H
