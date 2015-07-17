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
 * \file TreeView.h
 * \brief Class for managing and displaying a tree view of the
 * objects in the world
 */

#ifndef TREE_VIEW_H
#define TREE_VIEW_H

// Qt includes
#include <QtGui/QDockWidget>

// Local includes
#include "ui_TreeView.h"
#include "TreeViewReturn.h"
#include "include/GripTab.h"

/**
 * \namespace User Interface namespace for all the widgets
 */
namespace Ui {
    /**
     * \class TreeView TreeView.h
     * \brief Class containing the widgets
     */
    class TreeView;
}

/**
 * \class TreeView TreeView.h
 * \brief Class for the tree view which displays and manages the object in the
 * simulation world
 */
class TreeView : public QDockWidget
{
    /// MetaObject macro for using signals and slots
    Q_OBJECT
    
public:
    explicit TreeView(QWidget *parent = 0, QList<GripTab*>* tabs = NULL);
    // void populateTreeView();
    void reset();
    ~TreeView();
    TreeViewReturn* getActiveItem();

signals:
    void itemSelected(TreeViewReturn *active_item);

private slots:
    void nameChangeBodyNodeJoint(int checkBoxState);
    void treeViewItemSelected(QTreeWidgetItem *item, int column);
    
private:
    Ui::TreeView *_ui;
    QTreeWidget *_ui_treeWidget;
    QCheckBox *_ui_checkBox;
    TreeViewReturn *_activeItem;
    QList<GripTab*> *_tabs;

    // QTreeWidgetItem* _addParent(dart::dynamics::Skeleton *skel, QIcon icon, int skeletonId);
    // QTreeWidgetItem* _addChildItem(dart::dynamics::BodyNode* node, QTreeWidgetItem *parent, QIcon icon, int skeletonId);
    // QTreeWidgetItem* _buildTree(dart::dynamics::BodyNode* node, QTreeWidgetItem *prev, QTreeWidgetItem *parent, bool chain, int skeletonId);
    void _nameJoint(QTreeWidgetItem* node);
    void _nameBodyNode(QTreeWidgetItem* node);

}; // end class TreeView

#endif // TREE_VIEW_H
