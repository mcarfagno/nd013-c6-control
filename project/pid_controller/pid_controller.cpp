/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
   kp_ = Kpi;
   ki_ = Kii;
   kd_ = Kdi;
   out_low_ = output_lim_mini;
   out_high_ = output_lim_maxi;
   curr_cte_ = 0;
   prev_cte_ = 0;
   diff_cte_ = 0;
   sum_cte_ = 0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  curr_cte_ = cte;
  diff_cte_ = (cte - prev_cte_)/dt_;
  sum_cte_ += 0.5*(cte + prev_cte_)*dt_; //using trapezoid rule for integration
  prev_cte_ = curr_cte_; //update for next step
  
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control = -kp_ * curr_cte_ -ki_ * sum_cte_ -kd_ * diff_cte_;
    return std::max(out_low_, std::min(control, out_high_));
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  dt_ = new_delta_time;
}