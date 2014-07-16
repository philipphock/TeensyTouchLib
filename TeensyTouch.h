#ifndef TeensyTouch_h
#define TeensyTouch_h



class TeensyTouch{
typedef void (*TeensyTouchCallback)(int pin,int val,int isTouch); 
typedef int (*TouchReadType)(int); 

private:
	int pin = 0;
	int at = 0;
	TeensyTouchCallback callback;
	bool lastState = false;
	TouchReadType touchRead;
	

public:
	TeensyTouch(int pin, int pressThreshold, TeensyTouchCallback callback,TouchReadType t){
		this->touchRead = t;
		this->pin = pin;
		if (pressThreshold < 0){
			this->at = touchRead(pin)-pressThreshold;
		}else{
			this->at = pressThreshold;
		}
		this->callback = callback;
	}

	void loop(){
		int val = touchRead(pin);
		bool isAboveValue = val > at;
		if ( (isAboveValue && !lastState) 
		|| (!isAboveValue && lastState) ){
			callback(pin,val,isAboveValue);
		}		
		lastState = isAboveValue;
	}

	 
};

#endif
