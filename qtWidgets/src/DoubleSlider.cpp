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
#include <cmath>
#include <iostream>

// Local includes
#include "DoubleSlider.h"

// DoubleSlider is used to connect an integer valued slider to double valued doublespinbox

DoubleSlider::DoubleSlider (QWidget *parent)
  : QSlider(parent), dsvalue(0.0), min_value(-180.0), max_value(180.0), decimal_point(1)
{
 
    connect (this, SIGNAL(valueChanged(int)), this, SLOT(setValueAndEmit(int)));

}

double DoubleSlider::changeTOdouble(int intvalue)
{

    double doublevalue = ((double)intvalue)*pow(10.0,-(double)decimal_point);

    return doublevalue;
}

int DoubleSlider::changeTOinteger(double doublevalue)
{

    int integervalue = round(doublevalue*pow(10.0,(double)decimal_point)); 
    
    return integervalue;
}

void DoubleSlider::setdsValue(double valueindouble)
 {
     if (valueindouble != dsvalue) {
         dsvalue = valueindouble;
         }
     emit valueChanged(changeTOinteger(dsvalue));
}

double DoubleSlider::getdsValue()
{
    double temp = ((double)value())*pow(10.0,-(double)decimal_point);
    if (temp != dsvalue) {
        dsvalue = temp;
        }
    return dsvalue;
}

void DoubleSlider::setValueAndEmit(int slidervalue)
{
     double temp = changeTOdouble(slidervalue);
     if (temp != dsvalue) {
         dsvalue = temp;
         }

     emit dsvalueChanged(dsvalue);
}

void DoubleSlider::getValueAndEmit(double spinboxvalue)
{
     double temp = changeTOinteger(spinboxvalue);
     if (temp != value()) {
         setValue(temp);
         }

     emit valueChanged(temp);
}

void DoubleSlider::setMinMaxDecimalValue(double minvalue, double maxvalue, int decimalvalue)
{
    min_value = minvalue;
    max_value = maxvalue;
    decimal_point = decimalvalue;
    int min_value_integer = round((double)min_value*pow(10.0,(double)decimal_point));
    int max_value_integer = round((double)max_value*pow(10.0,(double)decimal_point));

    this->setRange(min_value_integer,max_value_integer);
}

double DoubleSlider::getMinValue()
{
    return min_value;
}

double DoubleSlider::getMaxValue()
{
    return max_value;
}

int DoubleSlider::getDecimalPoint()
{
    return decimal_point ;
}

