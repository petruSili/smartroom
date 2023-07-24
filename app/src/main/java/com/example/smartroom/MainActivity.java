package com.example.smartroom;

import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SwitchCompat;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Timer;
import java.util.TimerTask;
public class MainActivity extends AppCompatActivity {

    TextView temperatureText, humidityText, sleepingText;
    SwitchCompat switchMainLight, switchDeskLamp, switchArduinoFan, switchAutoMode, switchSleeping;
    SeekBar intensityDeskLamp, intensityArduinoFan;
    ScrollView scrollView;

    int temperature;
    int humidity;
    int input;

    Device mainLight, autoMode, sleeping;
    DeviceExt deskLamp, arduinoFan;
    String url = "replaceMe"; // Example:    "http://192.168.55.104:80"

    Timer timerTask;
    int period;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        /*
         *  Remove the status bar from the layout.
        */
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getSupportActionBar().hide();

        setContentView(R.layout.activity_main);

        timerTask = new Timer();
        period = 5000;
/*
 * Flag needed for the event listeners to distinguish between a user command and
 * a simple GUI update from the controller. By default it is MANUAL and changes to AUTO only
 * after a response from the controller.
*/
        input = state.MANUAL;

        /*
         *  Sensors
         */
        temperature = 0;
        humidity = 0;


        //assign values to each control on the layout
        temperatureText = findViewById(R.id.temperatureText);
        humidityText =  findViewById(R.id.humidityText);
        switchMainLight = findViewById(R.id.switchMainLight);
        switchDeskLamp = findViewById(R.id.switchDeskLamp);
        switchArduinoFan = findViewById(R.id.switchArduinoFan);
        switchAutoMode = findViewById(R.id.switchAutoMode);
        switchSleeping = findViewById(R.id.switchSleeping);
        sleepingText = findViewById(R.id.Sleeping);
        intensityDeskLamp = findViewById(R.id.intensityDeskLamp);
        intensityArduinoFan = findViewById(R.id.intensityArduinoFan);
        scrollView = findViewById(R.id.scrollView);



        mainLight = new DeviceImpl("mainLight", switchMainLight);
        deskLamp = new DeviceExtImpl("deskLamp", switchDeskLamp, intensityDeskLamp);
        arduinoFan = new DeviceExtImpl("arduinoFan", switchArduinoFan, intensityArduinoFan);
        autoMode = new DeviceImpl("autoMode", switchAutoMode);
        sleeping = new DeviceImpl("sleeping", switchSleeping);

        /*
         * The following task sends an update request to the controller periodically,
         * a response follows and so the device and sensor objects including are updated.
         * The changes affect he GUI as well.
        */
        timerTask.schedule(new TimerTask() {
                @Override
                public void run() {

                    ConnectionService connectionService = new ConnectionService(MainActivity.this);
                    connectionService.getData(url, new ConnectionService.VolleyResponseListener() {
                        @Override
                        public void onError(String message) {
                            Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                        }

                        @Override
                        public void onResponse(JSONObject data) throws JSONException {
                            input = state.AUTO;
                            JSONObject mainLightObject = data.getJSONObject(mainLight.getId());
                            JSONObject deskLampObject = data.getJSONObject(deskLamp.getId());
                            JSONObject arduinoFanObject = data.getJSONObject(arduinoFan.getId());
                            JSONObject autoModeObject = data.getJSONObject(autoMode.getId());
                            JSONObject sleepingObject = data.getJSONObject(sleeping.getId());


                            mainLight.setState(mainLightObject.getInt("POWER"));
                            mainLight.updateUiSwitch();

                            deskLamp.setState(deskLampObject.getInt("POWER"));
                            deskLamp.setIntensity(deskLampObject.getInt("Dimmer"));
                            deskLamp.updateUiSwitch();
                            deskLamp.updateUiSeekBar();

                            arduinoFan.setState(arduinoFanObject.getInt("POWER"));
                            arduinoFan.setIntensity(arduinoFanObject.getInt("Dimmer"));
                            arduinoFan.updateUiSwitch();
                            arduinoFan.updateUiSeekBar();

                            autoMode.setState(autoModeObject.getInt("POWER"));
                            autoMode.updateUiSwitch();

                            sleeping.setState(sleepingObject.getInt("POWER"));
                            sleeping.updateUiSwitch();

                            temperature = data.getInt("temperature");
                            temperatureText.setText(String.valueOf(temperature));

                            humidity = data.getInt("humidity");
                            humidityText.setText(String.valueOf(humidity));

                            input = state.MANUAL;

                        }
                    });
                }
        },0,period);

        /*
         * Event listeners.
         */

        switchMainLight.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if(input == state.MANUAL){
                JSONObject jsonCommand = new JSONObject();
                if (isChecked) {
                    try {
                        jsonCommand = mainLight.switchOn();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        jsonCommand = mainLight.switchOff();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                ConnectionService connectionService = new ConnectionService(MainActivity.this);
                connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                    @Override
                    public void onError(String message) {
                        Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onResponse(JSONObject data) {}
                });
            }
        });
        switchDeskLamp.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if(input == state.MANUAL) {
                JSONObject jsonCommand = new JSONObject();
                if (isChecked) {
                    try {
                        jsonCommand = deskLamp.switchOn();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        jsonCommand = deskLamp.switchOff();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                ConnectionService connectionService = new ConnectionService(MainActivity.this);
                connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                    @Override
                    public void onError(String message) {
                        Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onResponse(JSONObject data) {}
                });
            }
        });
        switchArduinoFan.setOnCheckedChangeListener((buttonView, isChecked) -> {
                JSONObject jsonCommand = new JSONObject();
            if(input == state.MANUAL) {
                if (isChecked) {
                    try {
                        jsonCommand = arduinoFan.switchOn();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        jsonCommand = arduinoFan.switchOff();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                ConnectionService connectionService = new ConnectionService(MainActivity.this);
                connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                    @Override
                    public void onError(String message) {
                        Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onResponse(JSONObject data) {}
                });
            }
        });
        switchAutoMode.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if(input == state.MANUAL){
                JSONObject jsonCommand = new JSONObject();
                if (isChecked) {
                    try {
                        jsonCommand = autoMode.switchOn();
                        switchSleeping.setVisibility(View.VISIBLE); //-------- when autoMode is enabled the sleeping entity is revealed
                        sleepingText.setVisibility(View.VISIBLE);
                        scrollView.post(() -> scrollView.fullScroll(ScrollView.FOCUS_DOWN));
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        jsonCommand = autoMode.switchOff();
                        switchSleeping.setVisibility(View.GONE); //-------- when autoMode is disabled the sleeping entity is hidden
                        sleepingText.setVisibility(View.GONE);
                        scrollView.post(() -> scrollView.fullScroll(ScrollView.FOCUS_DOWN));
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                ConnectionService connectionService = new ConnectionService(MainActivity.this);
                connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                    @Override
                    public void onError(String message) {
                        Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onResponse(JSONObject data) {}
                });
            }
        });
        switchSleeping.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if(input == state.MANUAL){
                JSONObject jsonCommand = new JSONObject();
                if (isChecked) {
                    try {
                        jsonCommand = sleeping.switchOn();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        jsonCommand = sleeping.switchOff();
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                ConnectionService connectionService = new ConnectionService(MainActivity.this);
                connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                    @Override
                    public void onError(String message) {
                        Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onResponse(JSONObject data) {}
                });
            }
        });
        intensityDeskLamp.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            private int intensity;
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
                //trackingFinished = true;
                if(input == state.MANUAL) {
                    JSONObject jsonCommand = new JSONObject();
                    try {
                        jsonCommand = deskLamp.changeIntensity(intensity);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    ConnectionService connectionService = new ConnectionService(MainActivity.this);
                    connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                        @Override
                        public void onError(String message) {
                            Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                        }

                        @Override
                        public void onResponse(JSONObject data) {}
                    });
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
               if(fromUser) {
                   intensity = progress;
               }
            }

        });
        intensityArduinoFan.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            private boolean trackingFinished = false;
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
                trackingFinished = true;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if(fromUser && trackingFinished){
                    trackingFinished = false;
                    JSONObject jsonCommand = new JSONObject();
                    try {
                        jsonCommand = arduinoFan.changeIntensity(progress);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }

                    ConnectionService connectionService = new ConnectionService(MainActivity.this);
                    connectionService.sendCommand(url, jsonCommand, new ConnectionService.VolleyResponseListener() {
                        @Override
                        public void onError(String message) {
                            Toast.makeText(MainActivity.this, "Something went wrong", Toast.LENGTH_SHORT).show();
                        }

                        @Override
                        public void onResponse(JSONObject data) {}
                    });
                }
            }
        });
    }

    @Override
    protected void onPause() {
        super.onPause();
        timerTask.cancel();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}

