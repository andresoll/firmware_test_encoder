# Firmware_for_incremental_encoder_model_board

I will upload updated versions of my work on this issue here: https://github.com/icub-tech-iit/study-encoders/issues/2

The goal will be to make a model of the incremental encoder signals so that the boards connected to it can be tested. the final project will have at least the "index fault" and "normal mode" operation using the "aux-amc-test" board with microcontroller "STM32 NUCLEO-G474RE"

![image](https://github.com/andresoll/firmware_test_encoder/assets/160229887/72dd2480-77dd-456e-ae2a-9ef6da80c251)

with "incremental_encoder_corret_function_model_01.c" it's possible create a model of incremental encoder with general porpouse code like this:

**Correct scenario**

![corret_index](https://github.com/andresoll/firmware_test_encoder/assets/160229887/1c3e2826-b42b-4b59-8ea7-4ab726eaf3c7)

**Index error scenario**

![index_error](https://github.com/andresoll/firmware_test_encoder/assets/160229887/823d0a23-cc4c-4bed-b490-e1086e540aed)

