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
	uint8_t sensor,
			idx;
	uint8_t val;
};

union Out{
	uint8_t b;
	bool v;
	float f;
};

const int i2c_addr = 0x40;
const int button_pin[2] = {0,1};
const int analog_pin = A0;
const int motor_pin[2][2] = { {2, 3},{4, 5} };
const int led_pin[2] = {6, 7};
const int temp_pin = 8;
const uint8_t m_values[3][2] = { {0,0}, {1,0}, {0,1} };
Out output;

DHT_Unified dht(temp_pin, DHT11);

void receive(int bytes);
void send();
void processData(const SMess &m);


void setup()
{

	Wire.begin(i2c_addr);
	Wire.onReceive(receive);
	Wire.onRequest(send);

	pinMode(button_pin[0], INPUT);
	pinMode(button_pin[1], INPUT);

	pinMode(motor_pin[0][0], OUTPUT);
	pinMode(motor_pin[0][1], OUTPUT);
	pinMode(motor_pin[1][0], OUTPUT);
	pinMode(motor_pin[1][1], OUTPUT);

	pinMode(led_pin[0], OUTPUT);
	pinMode(led_pin[1], OUTPUT);

#ifdef SERIAL_S
	Serial.begin(9600);
#endif
}

void loop()
{
	delay(100);

#ifdef SERIAL_S

	SMess m;
	Serial.readBytes((uint8_t*)&m, sizeof(SMess));
	processData(m);
	Serial.println(output.f);

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
		output.b = digitalRead(button_pin[m.idx]);
		break;

	case TEMP:
		output.f = decodeTemp();
		break;

	case MOTOR:
		decodeMotor(m.idx, m.val);
		output.v = true;
		break;

	case LED:
		digitalWrite(led_pin[m.idx], m.val);
		output.v = true;
		break;

	case ANALOG:
		analog = analogRead(analog_pin);
		output.b = map(analog, 0, 1023, 0, 255);
		break;

	default:
		output.b = 0;
		break;
	}
}

void receive(int bytes)
{
	SMess m;
	Wire.readBytes((uint8_t*)&m, sizeof(SMess));
	processData(m);
	
}

void send()
{
	Wire.write((uint8_t*)(&output), sizeof(Out));
}
