package com.example.smartroom;

import androidx.appcompat.widget.SwitchCompat;

import org.json.JSONException;
import org.json.JSONObject;

public class DeviceImpl implements Device {
    DeviceImpl(String deviceId, SwitchCompat deviceSwitch){
        this.deviceId = deviceId;
        this.deviceSwitch = deviceSwitch;
        isOn = state.OFF;
    }
    protected String deviceId;
    protected int isOn;
    protected SwitchCompat deviceSwitch;



    @Override
    public String getId() {
        return deviceId;
    }


    @Override
    public void setState(int s) {
            isOn = s;
    }

    @Override
    public void updateUiSwitch() {
        deviceSwitch.setChecked(isOn == state.ON);
    }

    @Override
    public JSONObject switchOn() throws JSONException {
        JSONObject jsonCommand = new JSONObject();
        jsonCommand.put("DEVICE", getId());
        jsonCommand.put("POWER", "ON");
        setState(state.ON);
        deviceSwitch.setChecked(true);
        return  jsonCommand;
    }

    @Override
    public JSONObject switchOff() throws JSONException {
        JSONObject jsonCommand = new JSONObject();
        jsonCommand.put("DEVICE", getId());
        jsonCommand.put("POWER", "OFF");
        setState(state.OFF);
        deviceSwitch.setChecked(false);
        return  jsonCommand;
    }

}
