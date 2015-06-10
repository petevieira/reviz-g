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
 * \file TreeViewReturn.h
 * \brief Class for managing the return object of the TreeView
 */

#ifndef TREEVIEWRETURN_H
#define TREEVIEWRETURN_H

#include <QMetaType>

/**
 * \enum Types of return objects for the TreeView
 */
enum DataType
{
    Return_Type_Robot,
    Return_Type_Node
};

/**
 * \class TreeViewReturn tree_view.h
 * \brief This class is used to return the object that is selected in the
 * Object Explorer or Tree View.
 */
class TreeViewReturn
{
public:
    /**
     * \brief Constructor for TreeViewReturn
     */
    TreeViewReturn(){}

    /// used to store the Skeleton object or the BodyNode object
    void *object;

    /// used to differentiate between the skeleton object and BodyNode object
    DataType dType;
    
    /// used to identify skeleton id number
    int skeletonId;

}; // end class TreeViewReturn

Q_DECLARE_METATYPE(TreeViewReturn*);

#endif // TREEVIEWRETURN_H
