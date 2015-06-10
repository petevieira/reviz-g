/**
 * Copyright (C) 2012, California Institute of Technology.
 * All Rights Reserved. U.S. Government Sponsorship Acknowledged.
 * Any commercial use must be negotiated with the Office of
 * Technology Transfer at the California Institute of Technology.
 *
 * Author: Peter Vieira <Peter.Vieira@jpl.nasa.gov>
 * Date: June 2015
 */

// Local includes
#include "PlaybackWidget.h"

// C++ Standard includes
#include <cmath>

PlaybackWidget::PlaybackWidget (MainWindow *parent)
 : QWidget(parent), ui(new Ui::PlaybackWidget)
{
    _parent = parent;
    ui->setupUi(this);
    connect(ui->sliderMain, SIGNAL(valueChanged(int)), _parent, SLOT(slotSetWorldFromPlayback(int)));
    connect(ui->buttonPlay, SIGNAL(released()), _parent, SLOT(slotPlaybackStart()));
    connect(ui->buttonPause, SIGNAL(released()), _parent, SLOT(slotPlaybackPause()));
    connect(ui->buttonReverse, SIGNAL(released()), _parent, SLOT(slotPlaybackReverse()));
    connect(ui->buttonBeginning, SIGNAL(released()), _parent, SLOT(slotPlaybackBeginning()));
    //connect(ui->playSpeed, SIGNAL(valueChanged(int)))
}

PlaybackWidget::~PlaybackWidget()
{
}

void PlaybackWidget::reset()
{
    this->setSliderValue(0);
    this->slotSetTimeDisplays(0, 0);
}

void PlaybackWidget::setSliderValue(int value)
{
    ui->sliderMain->setValue(value);
}

int PlaybackWidget::getSliderValue()
{
    return ui->sliderMain->value();
}

void PlaybackWidget::slotUpdateSliderMinMax(int min, int max)
{
    ui->sliderMain->setMinimum(min);
    ui->sliderMain->setMaximum(max);
}

void PlaybackWidget::slotSetTimeDisplays(double sim_time, double rel_time)
{
    ui->editSimTime->setText(QString("%1").arg(sim_time));
    ui->editSimRelTime->setText(QString("%1").arg(round(rel_time*100)/100)); // decimal point 2
}

size_t PlaybackWidget::getPlaybackSpeed()
{
    return ui->playSpeed->value();
}
