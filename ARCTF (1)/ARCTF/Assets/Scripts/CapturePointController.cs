using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CapturePointController : MonoBehaviour
{
    public CapturePoint CapturePoint;
    public FlagLocation[] FlagLocations;

    void Start()
    {
        // color yourself
        var block = TeamColors.Get(CapturePoint.Team);
        GetComponent<Renderer>().SetPropertyBlock(block);

        // color the flag contained on this capture point
        var child = transform.GetChild(0).gameObject;
        child.GetComponent<Renderer>().SetPropertyBlock(block);

        tag = "CapturePoint";
        child.tag = "StationaryFlag";
    }

    void Update()
    {
        // move yourself to the correct location constantly
        Location.Move(this, CapturePoint.Latitude, CapturePoint.Longitude);

        // if the flag is at the base, show the child flag
        // else hide it
        foreach (var flag in FlagLocations)
        {
            if (CapturePoint.Team == flag.Team)
            {
                var child = transform.GetChild(0).gameObject;
                child.GetComponent<Renderer>().enabled = flag.Base;
            }
        }
    }

    public bool Connect()
    {
        return Bluetooth.Connect(CapturePoint.Mac);
    }
}
