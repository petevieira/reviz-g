reviz
=====

Qt and OpenSceneGraph user interface for reviz, but being designed with modularity in mind in order to be useful to external kinematics and dynamics libraries.
Reviz is designed to be used with user plugins. Plugins can be loaded via "File->Load Plugins" and selecting a directory with the user's plugin shared library files.

Directory Overview
==================

  1. reviz

  reviz contains everything that depends on Qt, and OpenSceneGraph, including reviz's main window, the visualization window and the simulation thread.

  2. qtWidgets

  Qt is used for the application level, including the interface, GUI event handling, etc.

  qtWidgets contains Qt widgets that only depend on Qt.

  3. osgModel

  osgModel defines the interface between OpenSceneGraph and the model package. For every object in DART a node in OpenSceneGraph is created and can be rendered to an OpenSceneGraph View.

  4. osgReviz

  osgGolem defines a set of libraries for OpenSceneGraph that only depend on OpenSceneGraph.

  5. osgUrdf

  osg import of a urdf model

Installing Dependencies
=======================

The current dependencies are the following. 

On LINUX:
  - g++
    - sudo apt-get install g++
  - CMake
    - sudo apt-get install cmake
  - OpenSceneGraph (http://trac.openscenegraph.org/downloads/developer_releases/OpenSceneGraph-3.2.1.zip)
    - unzip
    - cd OpenSceneGraph-3.2.1
    - mkdir build && cd build
    - cmake ..
    - make
    - sudo make install
  - Qt4 (libqt4-dev)
    - sudo apt-get install libqt4-dev

On WINDOWS:
  - OpenSceneGraph
    - TODO
  - Qt4
    - TODO

Compiling Reviz
===============

  - In the reviz directory, run the following
    - mkdir build && cd build
    - cmake ..
    - make
    - ./reviz

Debugging
=========

  Currently, each class that could require debugging has a private member variable, "_debug", which gets set by the parent that instantiates the class. 

  The default value should always be "false".  

Documentation
=============

  Documentation is located at http://golems.github.io/grip2/

  1. Generating Documentation

  HTML documentation can be generated using Doxygen (http://www.stack.nl/~dimitri/doxygen/).
  There is a Doxyfile configuration file in the "doc" directory. You can use doxygen to parse the file
  and generate documentation for the entire package as follows:

      cd doc
      doxygen Doxyfile

  This generates an index.html file in the newly created html directory. Open this in any browser to view
  the documentation.

  2. Documentation Style in header files. All functions should contain a "\brief" and "\return" comment and "\param" comments if applicable.

  Comment blocks

      /**
       * \brief Sets the radius of the circle to the value passed in by the user
       * \param newRadius The new radius for the circle
       * \return void
       */
      void setRadius(float newRadius);

  One-line comments

      /// The radius of the cylinder
      int _radus;

      int _height ///< Height of the cylinder

Coding Guidelines
=================

  1. Qt Coding Standard should be used for all source code in Reviz except for the exceptions stated in section 2 following this section. Refer to the following references,

  http://qt-project.org/wiki/Coding-Conventions

  http://qt-project.org/wiki/Qt_Coding_Style

  http://doc.qt.digia.com/qq/qq13-apis.html#theartofnaming

  2. Exceptions to Qt Coding Standard

  Class private and protected member variables and functions should have the prefix (_) (an underscore), like follows, to improve clarity when reading source code.

    <pre><code>int _classMember;
  void _classFunction();</code></pre>

  Case statements should be indented from switch statements with optional braces and case keywords should all line up vertically.
    
    <pre><code>switch (type) {
        case LINE: {
            line = 3;
            break;
        }
        case LINE_WITH_ARROW: {
            line = 4;
            break;
        }
        default: {
            break;
        }
  }</code></pre>

  3. If you can't find out the correct way to do something, refer to existing source code in the project.