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

// Qt headers
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
  /**
   * \brief Constructor
   * \param parent Parent widget
   */
  DoubleSlider(QWidget *parent = 0);

  /**
   * \brief Converts int to double
   * \param intvalue int value to convert to double
   * \return double version of the int passed in
   */
  double changeTOdouble(int intvalue);

  /**
   * \brief Converts double to int
   * \param doublevalue double value to convert to int
   * \return int version of the double passed in
   */
  int changeTOinteger(double doublevalue);

  /**
   * \brief Gets the slider value
   * \return Double version of slider value
   */
  double getdsValue();

  /**
   * \brief Sets the min, max and decimal values for the slider
   * \param minvalue Minimum value for the slider
   * \param maxvalue Maximum value for the slider
   * \param decimalvalue Number of decimal values for the slider
   * \return void
   */
  void setMinMaxDecimalValue(double minvalue, double maxvalue, int decimalvalue);

  /**
   * \brief Gets the set minimum value of the slider
   * \return Minimum value of slider
   */
  double getMinValue();

  /**
   * \brief Gets the set maximum value of the slider
   * \return Maximum value of slider
   */
  double getMaxValue();

  /**
   * \brief Gets the set number of decimals
   * \return Number of decimals in slider output
   */
  int getDecimalPoint();

private:

  double dsvalue; ///< doubleslider value
  double min_value; ///< min value of the doubleslider
  double max_value; ///< max value of the doubeslider
  int    decimal_point; ///< decimal poit of the doublevalue: ex. decimal point = 1 --> x.x

public slots:
  /**
   * \brief Sets the value of the slider
   * \param valueindouble New slider value
   * \return void
   */
  void setdsValue(double valueindouble);

  /**
   * \brief Sets the value and emits the "Value Changed" signal via
   * the signal dsvalueChanged
   * \param slidervalue New slider value
   * \return void
   */
  void setValueAndEmit(int slidervalue);

  /**
   * \brief Gets the slider value and emits a signal
   * \param spinboxvalue
   * \return void
   */
  void getValueAndEmit(double spinboxvalue);

signals:

  /**
   * \brief Emits a signal that the double slider value changed
   * \param newdsvalue New slider value
   * \return void
   */
  void dsvalueChanged(double newdsvalue);

}; // end DoubleSlider class

#endif // DOUBLESPINBOX_H
