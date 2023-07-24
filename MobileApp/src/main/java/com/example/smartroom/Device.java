package com.example.smartroom;

import org.json.JSONException;
import org.json.JSONObject;


public interface Device {
    String getId();
    void setState(int s);
    void updateUiSwitch();
    JSONObject switchOn() throws JSONException;
    JSONObject  switchOff() throws JSONException;

}
