#include "BluetoothSerial.h" //
#include "driver/i2s.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "esp_bt.h"
#include "bt_app_core.h"
#include "bt_app_av.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"

#define CONFIG_I2S_LRCK_PIN 25
#define CONFIG_I2S_BCK_PIN  26
#define CONFIG_I2S_DATA_PIN 33
BluetoothSerial SerialBT;
// Motor A pins 
int AIN1 = 21;    //directional pin
int AIN2 = 22;    //directional pin
int PWMA = 23; //pwm (speed) pin 

// Motor B pins 
int BIN1 = 19;    //directional pin
int BIN2 = 18;    //directional pin
int PWMB = 4; //pwm (speed) pin 

// Set PWM properties for both motors
const int freq = 5000;
const int CHA = 0;
const int CHB = 1;
const int res = 8;  //256 levels for BOTH duty cycles
int dutyA = 200;  // ~80% max speed
int dutyB = 200;

#define LED_FRONT  2
#define LED_RIGHT 15
#define LED_LEFT 5
//ultrasensor
#define trigPin 13 // define trigPin
#define echoPin 14 // define echoPin.
#define MAX_DISTANCE 200 // Maximum sensor distance is rated at 400-500cm.
//timeOut= 2*MAX_DISTANCE /100 /340 *1000000 = MAX_DISTANCE*58.8
float timeOut = MAX_DISTANCE * 60;
int soundVelocity = 340; // define sound speed=340m/s

void setup() {
  Serial.begin(115200);   //initialize serial monitor
  //led front
  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  // sets the pins as outputs:
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  // configure motor PWM functionalitites
  ledcSetup(CHA, freq, res);
  ledcAttachPin(PWMA, CHA);
  ledcSetup(CHB, freq, res);
  ledcAttachPin(PWMB, CHB);
  
  pinMode(trigPin,OUTPUT);// set trigPin to output mode
  pinMode(echoPin,INPUT); // set echoPin to input mode

  SerialBT.begin("ESP32");
  Serial.println("Init seccess!");

  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  
  i2s_config_t i2s_config;
  i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  
  i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT;
  i2s_config.sample_rate = 44100;
  i2s_config.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
  i2s_config.communication_format = I2S_COMM_FORMAT_STAND_MSB;
  i2s_config.intr_alloc_flags = 0;
  i2s_config.dma_buf_count = 6;
  i2s_config.dma_buf_len = 60;
  i2s_config.tx_desc_auto_clear = true;
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  
  i2s_pin_config_t pin_config;
  pin_config.bck_io_num = CONFIG_I2S_BCK_PIN;
  pin_config.ws_io_num = CONFIG_I2S_LRCK_PIN;
  pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
  pin_config.data_in_num = -1;
  i2s_set_pin(I2S_NUM_0, &pin_config);

  bt_app_task_start_up();
  
 /* initialize A2DP sink */
  esp_a2d_register_callback(&bt_app_a2d_cb);
  esp_a2d_sink_register_data_callback(bt_app_a2d_data_cb);
  esp_a2d_sink_init();
  /* initialize AVRCP controller */
  esp_avrc_ct_init();
  esp_avrc_ct_register_callback(bt_app_rc_ct_cb);
  /* set discoverable and connectable mode, wait to be connected */
  esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
  Serial.println("ok");
}

void loop() {
  //led front
  digitalWrite(LED_FRONT, HIGH);
  delay(100); // Wait 100ms between pings (about 20 pings/sec). 
  Serial.printf("Distance: ");
  float dist = getSonar();
  Serial.print(dist); // Send ping, get distance in cm and print result
  Serial.println("cm");
  if (dist > 25 || dist == 0){
    Serial.println("Moving Forward");
    ledcWrite(CHA, dutyA);
    ledcWrite(CHB, dutyB);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(200);
  }
  // arrange motor output wires so both turn in same direction
  //speed determined by duty
  else{
    digitalWrite(LED_RIGHT, HIGH);
    digitalWrite(LED_LEFT, HIGH);

    Serial.println("Motor stopped");
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    delay(400);

    Serial.println("Moving Backward");
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);  
    delay(800);

    ledcWrite(CHA, 250);
    ledcWrite(CHB, 250);
    //random number generator
    int rand = random(0,2);

    if (rand == 0){
      Serial.println("Turning right");
      digitalWrite(LED_LEFT, LOW);
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);  
      delay(800);
    }
    else{
      Serial.println("Turning left");
      digitalWrite(LED_RIGHT, LOW);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);  
      delay(800);
    }
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);
    
  }
}
float getSonar() {
  unsigned long pingTime;
  float distance;
// make trigPin output high level lasting for 10us to trigger HC_SR04
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Wait HC-SR04 returning to the high level and measure out this waiting time
  pingTime = pulseIn(echoPin, HIGH, timeOut);
// calculate the distance according to the time
  distance = (float)pingTime * soundVelocity / 2 / 10000;
  return distance; // return the distance value
}