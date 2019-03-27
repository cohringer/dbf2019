/*
 * Blocking function to return true when switch has been set
 * @param pin is the pin to get PWM readings from
 * @param greaterThan is true or false (checking if measured val has to be greater than PWM thresh val)
 * @param pwmThresh is the PWM threshold value
 * @param timeInterval_ms is the time to take readings for
 * @param N is number of readings
 * @param percent percentage of readings during timeInterval that must be met
 * @return true if switch turned on, false if switch has not been ac
 */
bool blockUntil(int pin, bool greaterThan, int pwmThresh, int timeInterval_ms, int N, int percent) {
  bool status = false;
  int val = 0;
  int dt_ms = timeInterval_ms/N; 
  int num_pass = 0;

  // Argument check
  if (percent < 0) {
    percent = 0;
  } else if (percent > 100) {
    percent = 100;
  }

  while (!status) {
    num_pass = 0;
    
    for (int i = 0; i < N; i++) {
      val = pulseIn(pin, HIGH);
      if (greaterThan) {
        if (val > pwmThresh) {
          num_pass++;
        }
      } else {
        if (val < pwmThresh) {
          num_pass++;
        }
      }
      delay(dt_ms);
    }
    
    if (((float) num_pass / (float) N) * 100 >= percent) {
      status = true;
    }
  }

  return status;
}
