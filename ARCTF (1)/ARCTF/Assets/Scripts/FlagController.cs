using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlagController : MonoBehaviour {
    public FlagLocation FlagLocation;
    private int Team;

    void Start()
    {
        tag = "Flag";
    }

    void Update()
    {
        if (Team != FlagLocation.Team)
        {
            // change color if necessary
            // this block is only executed if the server decides to return
            // the flag information in a different order than before
            var block = TeamColors.Get(FlagLocation.Team);
            GetComponent<Renderer>().SetPropertyBlock(block);
            Team = FlagLocation.Team;
        }

        // if in base, use capture point flags instead
        GetComponent<Renderer>().enabled = !FlagLocation.Base;
        if (!FlagLocation.Base)
        {
            // move yourself to the correct location constantly
            Location.Move(this, FlagLocation.Latitude, FlagLocation.Longitude);
        }
    }
}
