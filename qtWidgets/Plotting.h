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
 * \file Plotting.h
 * \brief Fields to share information among plugins and the plotting plugin
 */

#ifndef PLOTTING_H
#define PLOTTING_H

#include <map>
#include <vector>
#include <string>
#include <pthread.h>
#include <Eigen/Dense>

#define NUM_PLOTTING_POINTS 101

/// Type of markers
enum PlotMarkerType {
	marker_point = 0,
	marker_circle,
	marker_xmark,
	marker_plus,
	marker_star
};

/// The structure that a plugin uses to represent its data
struct PluginStream {
    PluginStream(const std::string& l, double mi, double ma, Eigen::Vector3i* c = NULL, PlotMarkerType* mark = NULL)
        : label(l), index(0), minVal(mi), maxVal(ma), color(c), marker(mark)
    {
		for(size_t i = 0; i < NUM_PLOTTING_POINTS; i++) vals.push_back(0.0);
	}
	std::vector <double> vals;				///< The circular buffer for that 
    std::string label;						///< Label for the graph
    size_t index;							///< Points to the latestdata point
    double minVal, maxVal;					///< The range for the plot
    Eigen::Vector3i* color;                 ///< Color of the marker
    PlotMarkerType* marker;                 ///< Marker type
};

/// Represents a drawing plugin
struct Plotter {
	Plotter () {};
	pthread_mutex_t plottingMutex;							///< To regulate the data access
	std::vector <PluginStream*> streams;	///< The map from plots to streams
	virtual void update () = 0;
};

/// Sets of plotters available to the pluggins
extern std::vector <Plotter*> plotters;		

#endif // PLOTTING_H 

