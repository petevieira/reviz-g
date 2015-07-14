/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

#include "include/GripTimeslice.h"

GripTimeslice::GripTimeslice()
{
}

GripTimeslice::~GripTimeslice()
{

}

void GripTimeslice::setTime(double time)
{
    _time = time;
}

void GripTimeslice::setState()
{
}

double GripTimeslice::getTime() {
    return _time;
}

void GripTimeslice::getState() {

}
