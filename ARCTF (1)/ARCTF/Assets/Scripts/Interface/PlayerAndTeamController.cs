using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerAndTeamController : MonoBehaviour
{
    void Update()
    {
        var player = GameController.Player;
        var team = GameController.Team;
        var score1 = GameController.Score1;
        var score2 = GameController.Score2;
        GetComponent<Text>().text = "Player " + player
            + (team == 1 ? " (Green)" : " (Red)") + 
            "\nGreen " + score1 + " - " + score2 + " Red";
    }
}
