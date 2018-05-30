using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CarryingFlagController : MonoBehaviour
{
    void Update()
    {
        // show the icon if we are carrying the flag
        GetComponent<Image>().enabled = GameController.CarryingFlag;
    }
}
