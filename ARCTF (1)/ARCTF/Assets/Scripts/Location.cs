using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using AJObject = UnityEngine.AndroidJavaObject;

public static class Location
{
    // 1 unit = 5.5 meters
    private const int DISTANCE_SCALE = 20000;

    // current latitude/longitude
    public static double Latitude { get; private set; }
    public static double Longitude { get; private set; }

    //private static Queue<Tuple> history = new Queue<Tuple>();

    [RuntimeInitializeOnLoadMethod]
    private static void Initialize()
    {
        Input.location.Start(0.1f, 0.1f);
    }

    public static void Update()
    {
#if UNITY_EDITOR
        // fake coordinates for the editor
        Latitude = 34.020189;
        Longitude = -118.288791;
        return;
#endif
        var unityPlayer = new AJObject("com.unity3d.player.UnityPlayer");
        var activity = unityPlayer.GetStatic<AJObject>("currentActivity");
        var manager = activity.Call<AJObject>("getSystemService", "location");
        var location = manager.Call<AJObject>("getLastKnownLocation", "gps");
        Latitude = location.Call<double>("getLatitude");
        Longitude = location.Call<double>("getLongitude");
        return;
        /*
        if (history.Count >= 6) history.Dequeue();
        history.Enqueue(new Tuple
            {
                Latitude = location.Call<double>("getLatitude"),
                Longitude = location.Call<double>("getLongitude")
            }
        );
        UpdateAverages();
        */
    }

    // move a given object to the real life coordinates
    public static void Move(MonoBehaviour behaviour,
            double latitude, double longitude)
    {
        behaviour.transform.position = new Vector3(
                (float)((longitude - Longitude) * DISTANCE_SCALE),
                behaviour.transform.position.y,
                (float)((latitude - Latitude) * DISTANCE_SCALE));
    }

    /*
    private static void UpdateAverages()
    {
        double latitude = 0;
        double longitude = 0;
        var count = history.Count;
        foreach (var tuple in history)
        {
            latitude += tuple.Latitude / count;
            longitude += tuple.Longitude / count;
        }
        Latitude = latitude;
        Longitude = longitude;
    }

    private struct Tuple
    {
        public double Latitude;
        public double Longitude;
    }
    */
}
