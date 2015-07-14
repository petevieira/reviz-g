/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

// Qt includes
#include <QtGui/QtGui>

// C++ Standard includes
#include <iostream>
#include <cstdio>

// Local includes
#include "TreeView.h"

//include icons
// #include "icons/fixed.xpm"
// #include "icons/free.xpm"
// #include "icons/object.xpm"
// #include "icons/prism.xpm"
// #include "icons/revol.xpm"
// #include "icons/robot.xpm"

TreeView::TreeView(QWidget *parent, QList<GripTab*>* tabs) :QDockWidget(parent), _ui(new Ui::TreeView)
{
    _activeItem = new TreeViewReturn;
    _tabs = tabs;
    _ui->setupUi(this);
    _ui_treeWidget = _ui->treeWidget;
    _ui_treeWidget->header()->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    _ui_treeWidget->header()->setResizeMode(0, QHeaderView::ResizeToContents);
    _ui_treeWidget->header()->setStretchLastSection(true);
    connect(_ui_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(treeViewItemSelected(QTreeWidgetItem*,int)));

    _ui_checkBox = _ui->checkBox;
    connect(_ui_checkBox, SIGNAL(stateChanged(int)), this, SLOT(nameChangeBodyNodeJoint(int)));
}

TreeView::~TreeView()
{
    delete _ui;
    delete _activeItem;
}

void TreeView::treeViewItemSelected(QTreeWidgetItem * item, int column)
{
    TreeViewReturn* val = item->data(0, Qt::UserRole).value<TreeViewReturn*>();
    *_activeItem = *val;

    emit itemSelected(_activeItem);
    for (int i = 0; i < _tabs->size(); ++i) {
        _tabs->at(i)->GRIPEventTreeViewSelectionChanged();
    }
}

TreeViewReturn* TreeView::getActiveItem()
{
    return _activeItem;
}

// QTreeWidgetItem* TreeView::_addParent(dart::dynamics::Skeleton* skel, QIcon icon, int skeletonId)
// {
//     QTreeWidgetItem *itm = new QTreeWidgetItem(_ui_treeWidget);
//     itm->setText(0, QString::fromStdString(skel->getName()));
//     itm->setIcon(0, icon);

//     TreeViewReturn* ret = new TreeViewReturn();
//     ret->object = skel;
//     ret->dType = Return_Type_Robot;
//     ret->skeletonId = skeletonId;

//     QVariant var;
//     var.setValue(ret);
//     itm->setData(0, Qt::UserRole, var);

//     _ui_treeWidget->addTopLevelItem(itm);
//     return itm;
// }

// QTreeWidgetItem* TreeView::_addChildItem(dart::dynamics::BodyNode* node, QTreeWidgetItem* parent, QIcon icon, int skeletonId)
// {
//     if(parent != NULL) {
//         QTreeWidgetItem *childitm = new QTreeWidgetItem();
//         childitm->setText(0, QString::fromStdString(node->getName()));
//         childitm->setIcon(0,icon);

//         TreeViewReturn* ret = new TreeViewReturn();
//         ret->object = node;
//         ret->dType = Return_Type_Node;
//         ret->skeletonId = skeletonId;

//         QVariant var;
//         var.setValue(ret);
//         childitm->setData(0, Qt::UserRole, var);

//         parent->addChild(childitm);
//         return childitm;
//     } else {
//         std::cerr << "Parent is NULL" << std::endl;
//         return NULL;
//     }
// }

// QTreeWidgetItem* TreeView::_buildTree(dart::dynamics::BodyNode* node, QTreeWidgetItem* prev, QTreeWidgetItem* parent, bool chain, int skeletonId)
// {
//     QPixmap fixedIcon((const char**) fixed_xpm);
//     QPixmap freeIcon((const char**) free_xpm);
//     QPixmap objectIcon((const char**) object_xpm);
//     QPixmap prismIcon((const char**) prism_xpm);
//     QPixmap revolIcon((const char**) revol_xpm);
//     QIcon icon;

//     // Prismatic Joint: 1 DOF
//     dart::dynamics::Joint::JointType jointType = node->getParentJoint()->getJointType();
//     if (dart::dynamics::Joint::PRISMATIC == jointType)
//         icon = QIcon(prismIcon);

//     // Revolute Joint: 1 DOF
//     else if (dart::dynamics::Joint::REVOLUTE == jointType)
//         icon = QIcon(revolIcon);

//     // Floating Joint: 6 DOF
//     else if (dart::dynamics::Joint::FREE == jointType)
//         icon = QIcon(freeIcon);

//     //Fixed Joint: 0 DOF
//     else if (dart::dynamics::Joint::WELD == jointType)
//         icon = QIcon(fixedIcon);

//     else
//         icon = QIcon(objectIcon);


//     QTreeWidgetItem* new_parent = parent;
//     if (node->getNumChildBodyNodes() == 1)
//     {
//         if (node->getChildBodyNode(0)->getNumChildBodyNodes() == 1 && !chain)
//             prev = new_parent = _addChildItem(node, parent, QIcon(icon), skeletonId);
//         else
//         {
//             prev = _addChildItem(node, parent, QIcon(icon), skeletonId);
//         }
//         _buildTree(node->getChildBodyNode(0), prev, new_parent, true, skeletonId);
//     }
//     else
//     {
//         prev = new_parent = _addChildItem(node, parent, QIcon(icon), skeletonId);
//         for (int i=0; i<node->getNumChildBodyNodes(); i++)
//             prev = _buildTree(node->getChildBodyNode(i), prev, new_parent, false, skeletonId);
//     }
//     return prev;
// }

// void TreeView::populateTreeView(dart::simulation::World *world)
// {
//     QTreeWidgetItem* parent;
//     QPixmap robotIcon((const char**) robot_xpm);
//     for (int i = 0; i<world->getNumSkeletons(); ++i)
//     {
//         dart::dynamics::Skeleton* skel = world->getSkeleton(i);
//         if(skel) {
//             parent = _addParent(skel,  QIcon(robotIcon), i);
//             _buildTree(skel->getRootBodyNode(), parent, parent, false,i);
//         } else {
//             std::cerr << "Not a valid skeleton. Not building tree view. (Line " << __LINE__ << " of " << __FILE__ << std::endl;
//         }
//     }
//     _ui_treeWidget->setCurrentItem(parent, 0);
// }

void TreeView::reset()
{
    while(_ui_treeWidget->topLevelItemCount()) {
        delete _ui_treeWidget->takeTopLevelItem(0);
    }
}

// void TreeView::_nameJoint(QTreeWidgetItem* node)
// {
//     TreeViewReturn* val = node->data(0, Qt::UserRole).value<TreeViewReturn*>();
//     dart::dynamics::Joint* joint = ((dart::dynamics::BodyNode*)val->object)->getParentJoint();
//     node->setText(0, QString::fromStdString(joint->getName()));

//     int count = node->childCount();
//     if(count == 0)
//         return;
//     else
//         for(int i= 0; i< count; i++)
//             _nameJoint(node->child(i));
// }

// void TreeView::_nameBodyNode(QTreeWidgetItem* node)
// {
//     TreeViewReturn* val = node->data(0, Qt::UserRole).value<TreeViewReturn*>();
//     dart::dynamics::BodyNode* bodyNode = (dart::dynamics::BodyNode*)val->object;
//     node->setText(0, QString::fromStdString(bodyNode->getName()));

//     int count = node->childCount();
//     if(count == 0)
//         return;
//     else
//         for(int i= 0; i< count; i++)
//             _nameBodyNode(node->child(i));
// }

void TreeView::nameChangeBodyNodeJoint(int checkBoxState)
{
    // int count = _ui_treeWidget->topLevelItemCount();
    // for(int i = 0; i < count; i++)
    // {
    //     QTreeWidgetItem* top = _ui_treeWidget->topLevelItem(i);
    //     for(int j = 0; j<top->childCount(); j++)
    //     {
    //         QTreeWidgetItem* child = top->child(j);
    //         if(checkBoxState == Qt::Unchecked)
    //             _nameBodyNode(child);
    //         else
    //             _nameJoint(child);
    //     }
    // }
}
