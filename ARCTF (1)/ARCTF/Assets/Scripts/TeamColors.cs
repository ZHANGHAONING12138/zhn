using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class TeamColors
{
    private static readonly MaterialPropertyBlock friendly
            = new MaterialPropertyBlock();
    private static readonly MaterialPropertyBlock enemy
            = new MaterialPropertyBlock();

    static TeamColors()
    {
        friendly.SetColor("_Color", Color.green);
        enemy.SetColor("_Color", Color.red);
    }

    // helper function to ensure the material property blocks are reused
    // instead of being recreated for every object in the game
    public static MaterialPropertyBlock Get(int team)
    {
        return (team == 1) ? friendly : enemy;
    }
}
