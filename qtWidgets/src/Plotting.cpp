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
 * \file Plotting.cpp
 * \brief Fields to share information among plugins and the plotting plugin
 * Used to define the extern variables. The plugins cannot define these variables
 * because we don't know which plugin would be used and when.
 */

#include "Plotting.h"

std::vector <Plotter*> plotters;		

