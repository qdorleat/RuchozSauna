/*
 * Timer class
 * The timer class holds a timeOut functor. The timeOut functor is called at stop() function call
 * The timeOut functor is set when the timer is started  
 */
class Timer
{
  static const int COUNTER_DURATION = 5; // 30 /* MINUTES */ * 60 /* SECONDS */;
  time_t _startTimeS;

  void (*timeOutFunc)(AsyncWebServerRequest*); 

public:

  void stop() {
    if(timeOutFunc) {
      timeOutFunc(nullptr);
    }
  }
  
  void start(void (*my_function)(AsyncWebServerRequest*)) 
  {
    _startTimeS = time(nullptr);
    timeOutFunc = my_function;
  }

  void loop() {
    auto currentTimeS = time(nullptr);
    time_t durationS = currentTimeS - _startTimeS;
    Serial.print("time: ");
    Serial.print(durationS);
    Serial.print(" time2go: ");
    Serial.println(COUNTER_DURATION-durationS);

    if(static_cast<int>(durationS) > COUNTER_DURATION) {
      stop();
    }
  }
};