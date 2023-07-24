package com.example.smartroom;

import android.widget.SeekBar;
import androidx.appcompat.widget.SwitchCompat;
import org.json.JSONException;
import org.json.JSONObject;

public class DeviceExtImpl extends DeviceImpl implements DeviceExt {
    DeviceExtImpl(String deviceId, SwitchCompat deviceSwitch, SeekBar bar){
        super(deviceId, deviceSwitch);
        this.intensityBar = bar;
        isOn = 0;
        intensity = 0;
    }

    private int intensity;
    private final SeekBar intensityBar;


    @Override
    public void setIntensity(int i) {
        intensity = i;
        intensityBar.setProgress(intensity);
    }

    @Override
    public void updateUiSeekBar() {
        intensityBar.setProgress(intensity);
    }

    @Override
    public JSONObject changeIntensity(int i) throws JSONException {
        setIntensity(i);
        JSONObject jsonCommand = new JSONObject();
        jsonCommand.put("DEVICE", deviceId);
        jsonCommand.put("Dimmer", intensity);
        return jsonCommand;
    }
}
