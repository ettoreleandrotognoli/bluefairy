#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <gtest/gtest.h>
#include "Scheduler.h"
#include <iostream>


using namespace arc;


int counter = 1;


void add_and_print(Scheduler& scheduler) {
    std::cout << "add_and_print" << std::endl;
    std::cout << ++counter << std::endl;
}




TEST(Scheduler, Timeout){
    Scheduler scheduler;
    scheduler.debug(Serial);
    scheduler.timeout(1000, add_and_print);
    scheduler.debug(Serial);
    scheduler.timeout(2000, add_and_print);
    scheduler.debug(Serial);
    scheduler.timeout(3000, add_and_print);
    scheduler.debug(Serial);
    EXPECT_EQ(counter,1);
    scheduler.loop();
    EXPECT_EQ(counter,4);
}


TEST(Schedule, Every) {
    Scheduler scheduler;
    scheduler.every(100, [](Scheduler& scheduler) {
       scheduler.debug(Serial);
    });
    for(int i = 0;i<10;i+=1){
        delay(scheduler.tick());
    }
}


int main(int argc,char ** argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}