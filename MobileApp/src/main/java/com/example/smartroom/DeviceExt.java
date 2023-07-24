package com.example.smartroom;

import org.json.JSONException;
import org.json.JSONObject;


public interface DeviceExt extends Device {
   void setIntensity(int i);
   void updateUiSeekBar();
   JSONObject changeIntensity(int i) throws JSONException;
}
