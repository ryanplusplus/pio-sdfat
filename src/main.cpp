#include <Arduino.h>

#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

extern "C" {
#include <stddef.h>
#include "tiny_timer.h"
#include "tiny_time_source.h"
#include "tiny_heartbeat.h"
}

#define SPI_SPEED 4000000
#define NO_SS -1

static tiny_timer_group_t timer_group;
static SdFat sd;

void setup()
{
  Serial.begin(9600);

  while(!Serial) {
    SysCall::yield();
  }

  tiny_timer_group_init(&timer_group, tiny_time_source_init());
  tiny_heartbeat_init(&timer_group, 1000);

  if(!sd.begin(NO_SS, SPI_SPEED)) {
    Serial.println("Oh poop");
  }
  else {
    Serial.println("All good");
  }

  Serial.println("Files:");
  sd.ls(LS_R | LS_DATE | LS_SIZE);

  File test_write = sd.open("test.txt", FILE_WRITE);

  if(!test_write) {
    Serial.println("Failed to open file for writing :(");
  }
  else {
    test_write.println("Maybe this works?");
    test_write.close();
  }

  File test_read = sd.open("test.txt", FILE_READ);

  if(!test_read) {
    Serial.println("Failed to open file for reading :(");
  }
  else {
    while(test_read.available()) {
      Serial.write(test_read.read());
    }

    test_read.close();
  }
}

void loop()
{
  tiny_timer_group_run(&timer_group);
}
