This app will show the Battery Data of Nexigo battery pack with the CAN Matrix-BMS CAN Matrix.xlsx.


You need to use 2 ESP32's since the battery is in command mode.
  ->One device will send a CAN command to battery such a way that battery can send the CAN frames.
  ->Other is used the read the CAN frames to do byte operations and write the data to the bluetooth such a way that a Mobile can be paired to receive the data. 

Upload CAN_write_ithin_sucessfullllllllllllll.ino in one device(sending the command).
Upload z_z_Batterydata_portrait_update_button.ino in other device(Capturing the battery response, do byte operations and write the data to bluetooth.
Battery, Device 1 and Device 2 all three has to be connected via CAN.
You can install the apk, pair ESP_Control bluetooth device(As mentioned in edge device firmware, you can change it).
Connect to the device then you will see the data that will be streaming to Mobile phone.
Battery_data_portrait_update_button.aia can be imported into MIT app inventor t see the underlying logics, if you want you can do changes for the logics and UI.

---------------------------------------------------------------------------:)))--------------------------------------------------------------------------------
