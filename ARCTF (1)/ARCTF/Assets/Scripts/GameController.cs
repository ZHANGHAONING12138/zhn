using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameController : MonoBehaviour
{
    public GameObject CapturePointPrefab;
    public GameObject FlagPrefab;

    // persistent game state
    private static GameState state = new GameState();
    // transient game state, updated twice every second
    private static TransientState transientState = new TransientState();

    void Start()
    {
        Network.LoadPermanentState(state, this.OnStateRead);
    }

    private void OnStateRead()
    {
        // TODO do not hardcode number of teams
        var flagLocations = new FlagLocation[2];
        flagLocations[0] = new FlagLocation();
        flagLocations[1] = new FlagLocation();

        transientState.FlagLocations = flagLocations;

        Array.ForEach(state.CapturePoints, cp => CreateCapturePoint(cp, flagLocations));
        Array.ForEach(flagLocations, CreateFlag);

        // start downloading the transient state
        InvokeRepeating("LoadTransient", 0.0f, 0.5f);
    }

    private void LoadTransient()
    {
        // every 0.5 seconds, update the location information
        Location.Update();
        // and download the latest state
        Network.LoadTransientState(state.Player, transientState);
    }

    private void CreateCapturePoint(CapturePoint capturePoint,
            FlagLocation[] flagLocations)
    {
        // create a capture point from a prefab
        var cpObject = Instantiate(CapturePointPrefab);
        var controller = cpObject.GetComponent<CapturePointController>();
        controller.CapturePoint = capturePoint;
        controller.FlagLocations = flagLocations;
        cpObject.tag = "CapturePoint";
        // calling this starts the controller script
        cpObject.SetActive(true);
    }

    private void CreateFlag(FlagLocation flagLocation)
    {
        // create a flag from a prefab
        var flagObject = Instantiate(FlagPrefab);
        var controller = flagObject.GetComponent<FlagController>();
        controller.FlagLocation = flagLocation;
        flagObject.tag = "Flag";
        // calling this starts the controller script
        flagObject.SetActive(true);
    }

    // helper methods to access the game state
    public static bool CarryingFlag
    {
        get { return transientState.CarryingFlag; }
    }

    public static string Player
    {
        get { return state.Player; }
    }

    public static int Team
    {
        get { return state.Team; }
    }

    public static int Score1
    {
        get { return transientState.Score[0].Score; }
    }

    public static int Score2
    {
        get { return transientState.Score[1].Score; }
    }
}
