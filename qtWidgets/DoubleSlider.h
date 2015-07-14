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
 * \file DoubleSlider.h
 * \brief Class that creates a double valued slider
 */

#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QtGui/QSlider>

/**
 * \class DoubleSlider DoubleSlider.h
 * \brief Class that creates a double valued slider
 */
class DoubleSlider : public QSlider
{
    /// MetaObject macro for using signals and slots
    Q_OBJECT

public:
         DoubleSlider(QWidget *parent = 0);
         double changeTOdouble(int intvalue);
         int changeTOinteger(double doublevalue);
         double getdsValue(); //get doubleslider value
         void setMinMaxDecimalValue(double minvalue, double maxvalue, int decimalvalue);
         double getMinValue();
         double getMaxValue();
         int getDecimalPoint();
private:
         double dsvalue; //doubleslider value
         double min_value; //min value of the doubleslider
         double max_value; //max value of the doubeslider
         int    decimal_point; //decimal poit of the doublevalue: ex. decimal point = 1 --> x.x

public slots:
         void setdsValue(double valueindouble); //set doubleslider value
         void setValueAndEmit(int slidervalue);
         void getValueAndEmit(double spinboxvalue);

signals:
         void dsvalueChanged(double newdsvalue); //emit signal "doubleslider value changed"

}; // end DoubleSlider class

#endif // DOUBLESPINBOX_H
