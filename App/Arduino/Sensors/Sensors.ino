#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>
#include <Wire.h>

#define SERIAL_S 1

enum Sensor {
	CONTACT = 0,
	TEMP,
	MOTOR,
	LED,
	ANALOG
};

enum MOTOR_V {
	STOP = 0,
	RIGHT = 1,
	LEFT = 2
};

struct SMess {
        uint8_t sensor;
        uint8_t idx;
        uint8_t val;
    };

const int i2c_addr = 0x40;
const int button_pin[2] = {0,1};
const int analog_pin = A0;
const int motor_pin[2][2] = { {2, 3},{4, 5} };
const int led_pin[2] = {6, 7};
const int temp_pin = 8;
const uint8_t m_values[3][2] = { {0,0}, {1,0}, {0,1} };
uint8_t output;

DHT_Unified dht(temp_pin, DHT11);

void receive(int bytes);
void send();
void processData(const SMess &m);


void setup()
{
  	Serial.begin(9600);

	pinMode(button_pin[0], INPUT);
	pinMode(button_pin[1], INPUT);

	pinMode(motor_pin[0][0], OUTPUT);
	pinMode(motor_pin[0][1], OUTPUT);
	pinMode(motor_pin[1][0], OUTPUT);
	pinMode(motor_pin[1][1], OUTPUT);

	pinMode(led_pin[0], OUTPUT);
	pinMode(led_pin[1], OUTPUT);

}

void loop()
{
	//delay(100);

#ifdef SERIAL_S

if(Serial.available()){
	SMess m;
	Serial.readBytes((char*)&m, sizeof(SMess));
	processData(m);
	Serial.write((char*)&output, sizeof(uint8_t));
        Serial.flush();
}

#endif
}

void decodeMotor(uint8_t idx, uint8_t cmd)
{
	uint8_t v1 = m_values[cmd][0];
	uint8_t v2 = m_values[cmd][1];

	digitalWrite(motor_pin[idx][0], v1);
	digitalWrite(motor_pin[idx][1], v2);
}

float decodeTemp()
{
	sensors_event_t ev;
	dht.temperature().getEvent(&ev);
	if (isnan(ev.temperature)) {
		return 0.0f;
	}

	return ev.temperature;	
}

void processData(const SMess &m)
{
	int analog = 0;

	switch (m.sensor) {
	case CONTACT:
		output = digitalRead(button_pin[m.idx]);
		break;

	case TEMP:
		output = decodeTemp();
		break;

	case MOTOR:
		decodeMotor(m.idx, m.val);
		output = true;
		break;

	case LED:
		digitalWrite(led_pin[m.idx], m.val);
		output = true;
		break;

	case ANALOG:
		analog = analogRead(analog_pin);
		output = map(analog, 0, 1023, 0, 255);
    output = analog;
		break;

	default:
		output = 0;
		break;
	}
}

void receive(int bytes)
{
	SMess m;
	Wire.readBytes((char*)&m, sizeof(SMess));
	processData(m);
	
}

void send()
{
	Wire.write((uint8_t*)(&output), sizeof(uint8_t));
}
