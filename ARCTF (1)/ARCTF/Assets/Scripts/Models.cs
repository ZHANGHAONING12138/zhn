using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class GameState
{
    public string Player;
    public int Team;
    public CapturePoint[] CapturePoints;
}

[System.Serializable]
public class CapturePoint
{
    public string id;
    public double lat;
    public double lng;
    public string mac;
    public int team;

    // aliases because the server uses a different notation
    public string Id { get { return id; } }
    public double Latitude { get { return lat; } }
    public double Longitude { get { return lng; } }
    public string Mac { get { return mac; } }
    public int Team { get { return team; } }
}

[System.Serializable]
public class TransientState
{
    public bool CarryingFlag;
    public FlagLocation[] FlagLocations;
    public ScoreTuple[] Score;
}

[System.Serializable]
public class FlagLocation
{
    public double Latitude;
    public double Longitude;
    public bool Base;
    public int Team;
}

[System.Serializable]
public class ScoreTuple
{
    public string Team;
    public int Score;
}
