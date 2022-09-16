#ifndef __NONBLOCKDELAY_H__
#define __NONBLOCKDELAY_H__
static unsigned long skipped= 0;
class NonBlockDelay{
private:
  unsigned long prev_time = 0;
  bool flag = 0;
public:
  bool wait(unsigned long time_wait){
    unsigned long now_time = millis();
    if(prev_time == 0)
      prev_time = now_time;
    unsigned long diff = now_time - prev_time;
    if (skipped++ % 1000 == 0){
    //  Serial.println(time_wait);
    //  Serial.println(diff);
    }
    
    if (now_time - prev_time > time_wait){
      prev_time = now_time;
      return 1;
    }
    return 0;
  }
  bool wait_once(unsigned long time_wait){
    if(flag){
      if(prev_time == 0){
        prev_time = millis();
        return 0;
      }
      if(wait(time_wait)){
        flag = 0;
        return 1;
      }
    }
    return 0;
  }
  void Start(){
    prev_time = 0;
    flag = 1;
  }
};


#endif
