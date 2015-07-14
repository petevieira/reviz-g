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
 * \file GripTimeslice.h
 * \brief Class for the objects in the timeline
 */

#ifndef GRIP_TIMESLICE_H
#define GRIP_TIMESLICE_H

/**
 * \class GripTimeslice GripTimeslice.h
 * \brief Class for storing a slice of the timeline. This contains a
 * time parameter and a world state parameter.
 */
class GripTimeslice
{
public:
    /**
     * \brief Default constructor for GripTimeslice object
     */
    GripTimeslice();

    /**
     * \brief Destructs a GripTimeslice object
     */
    ~GripTimeslice();

    /**
     * \brief Sets the protected time variable of the GripTimeslice
     * \param time Time value
     */
    void setTime(double time);

    /**
     * \brief Sets the protected world state variable of the GripTimeslice
     * \param state State of the World
     */
    void setState();

    /**
     * \brief Gets the time stored in the GripTimeslice
     * \return Double value of the time
     */
    double getTime();

    /**
     * \brief Gets the state stored in the GripTimeslice
     * \return Eigen::VectorXd representing the world state
     */
    void getState();

protected:
    double _time; ///< Timestamp for the world state
    int _state; ///< State of the world at this time

}; // end class GripTimeslice

#endif // GRIP_TIMESLICE_H
