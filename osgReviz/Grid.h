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
 * \file Grid.h
 * \brief Class for creating an OpenSceneGraph osg::Geometry\n
 * grid of user-specified width, depth and grid square size.
 */

#ifndef GRID_H
#define GRID_H

// OpenSceneGraph includes
#include <osg/Geometry>

/**
 * \namespace osgReviz
 * \brief Namespace for all the classes that are only dependent upon OpenSceneGraph
 */
namespace osgReviz {

/**
 * \class Grid Grid.h
 * \brief Class for creating an OpenSceneGraph osg::Geomtry grid
 * of user-specified width, depth and grid square size.
 */
class Grid : public osg::Geometry
{
public:

    /**
     * \brief Constructor for Grid class.
     * \param width Width of the grid.
     * \param depth Depth of the grid.
     * \param gridSize Length of a side of each grid square.
     * \param color Color of the grid lines
     * \return void
     */
    Grid(uint width, uint depth, uint gridSize, const osg::Vec4& color);

    /**
     * \brief Destructor for Grid classs
     */
    ~Grid();

    /**
     * \brief Sets the color of the grid lines
     * \param color Vector specifying the color using RGBA format
     * \return void
     */
    void setGridColor(const osg::Vec4& color);

protected:

    /**
     * \brief Creates vertices around the perimeter of the grid according
     * to the width, depth and grid size specified by the user.
     * \param width Width of the grid.
     * \param depth Depth of the grid.
     * \param gridSize Length of a side of each grid square.
     * \return void
     */
    void _createVertices(uint width, uint depth, uint gridSize);

    /**
     * \brief Draw the lines in between the previously created vertices.
     * \return void
     */
    void _drawGrid(const osg::Vec4& color);

    /**
     * \brief Makes input number even if odd and does nothing if number is even.
     * It modifies the input number by reference.
     * \param num Integer to make even.
     * \return void
     */
    uint _makeEven(uint num);

    /// Array of vertices corresponding to grid line endpoints
    osg::ref_ptr<osg::Vec3Array> _verts;

    /// Array of colors corresponding to grid line colors
    osg::ref_ptr<osg::Vec4Array> _colors;

    /// Maximum grid perimeter side length
    static const uint maxLength = 500;

}; // end class Grid

} // end namespace osgReviz

#endif // GRID_H
