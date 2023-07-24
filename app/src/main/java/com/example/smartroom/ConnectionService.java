package com.example.smartroom;

import android.content.Context;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;

import org.json.JSONException;
import org.json.JSONObject;

public class ConnectionService {
    Context context;
    JSONObject data;

    public ConnectionService(Context context) {
        this.context = context;
    }

    public interface VolleyResponseListener{
            void onError(String message);
            void onResponse(JSONObject data) throws JSONException;
    }

    public void getData(String url, VolleyResponseListener volleyResponseListener){

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    data = response.getJSONObject("stats");
                    //Toast.makeText(context, data.toString(), Toast.LENGTH_SHORT).show();
                    volleyResponseListener.onResponse(data);
                } catch (JSONException e) {
                    e.printStackTrace();
                }

            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                volleyResponseListener.onError("Something went wrong!");
            }
        });
                MySingleton.getInstance(context).addToRequestQueue(request);
    }

    public void sendCommand(String url, JSONObject jsonCommand, VolleyResponseListener volleyResponseListener){

        JsonObjectRequest request = new JsonObjectRequest(Request.Method.POST, url, jsonCommand, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {

            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                error.printStackTrace();
            }
        });

        MySingleton.getInstance(context).addToRequestQueue(request);
    }
}
