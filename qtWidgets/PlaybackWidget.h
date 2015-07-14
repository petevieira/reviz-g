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
 * \file PlaybackWidget.h
 * \brief Class for simulation and kinematic playback
 */

#ifndef PLAYBACK_WIDGET_H
#define PLAYBACK_WIDGET_H

// Local includes
#include "ui_PlaybackWidget.h"

/**
 * \class PlaybackWidget PlaybackWidget.h
 * \brief Class for simulation and kinematic playback
 */
class PlaybackWidget : public QWidget {

    /// MetaObject macro for using signals and slots
    Q_OBJECT

public:
    /**
     * \brief Constructs a PlaybackWidget object
     * \param parent Object that creates the PlaybackWidget object
     */
    PlaybackWidget(QWidget *parent);

    /**
     * \brief Destructs this PlaybackWidget object
     */
    ~PlaybackWidget();

    /**
     * \brief Resets the widgets
     */
    void reset();

    /**
     * \brief Sets the value of the slider object
     * \param value Value to set slider to
     * \return void
     */
    void setSliderValue(int value);

    /**
     * \brief Gets the current value of the slider
     * \return Integer value of the slider
     */
    int getSliderValue();

    /**
     * \brief returns the playback speed from the spinbox
     * \return int
     */
    size_t getPlaybackSpeed();

    /// UI object which holds all the widgets
    Ui::PlaybackWidget *ui;

public slots:

    /**
     * \brief Updates the min and max of the slider widget
     * \param min The new minimum value of the slider
     * \param max The new maximum value of the slider
     * \return void
     */
    void slotUpdateSliderMinMax(int min, int max);

    /**
     * \brief Updates the time displays of the playback widget
     * \param sim_time Current simulation time for playback
     * \param rel_time Simulation time relative to real time
     * \return void
     */
    void slotSetTimeDisplays(double sim_time, double rel_time);

private:
    /// Parent's base class to access its slots and signals
    QWidget *_parent;

}; // end class PlaybackWidget

#endif // PLAYBACK_WIDGET_H
